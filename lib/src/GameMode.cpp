#include <VulkanTraining/GameMode.h>

#include <private/Drawables/StaticObjectDrawable.h>

#include <cassert>
#include <thread>
#include <mutex>
#include <atomic>

namespace
{
#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

const std::vector<VT::StaticObjectPipeline::Vertex> vertices =
{
    {{ -0.25f, -0.25f, 0.25f }, { 0.0f, 0.0f }},
    {{ 0.25f, -0.25f, 0.25f }, { 0.0f, 1.0f }},
    {{ -0.25f, 0.25f, 0.25f }, { 1.0f, 0.0f }},
    {{ 0.25f, 0.25f, 0.25f }, { 1.0f, 1.0f }}
};

const std::vector<VT::StaticObjectPipeline::Index> indices = { 0, 1, 2, 2, 1, 3 };
}

namespace VT
{
struct GameModePrivate
{
    static void WindowSizeCallback(GLFWwindow* window, int width, int height);

    std::thread gameModeThread;
    std::mutex launchMutex;
    std::atomic<bool> closeWindow;

    Instance* instance = nullptr;
    Surface* surface = nullptr;
    PhysicalDevice* physicalDevice = nullptr;
    Device* device = nullptr;
    ShadersCollector* shadersCollector = nullptr;
    Swapchain* swapchain = nullptr;
    StaticObjectPipeline* staticObjectPipeline = nullptr;
    StaticObjectDrawable* staticObjectDrawable = nullptr;
};

void GameModePrivate::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) return;

    GameMode* gameMode = static_cast<GameMode*>(glfwGetWindowUserPointer(window));
    gameMode->DeleteSwapchain();
    gameMode->CreateSwapchain();
}

GameMode::GameMode(int width, int height, const char* title, const char* shadersPath)
    : m_private(new GameModePrivate)
{
    glfwInit();

    m_private->instance = new Instance(title, enableValidationLayers);
    assert(m_private->instance);

    m_private->surface = new Surface(*m_private->instance, width, height, title, this, m_private->WindowSizeCallback);
    assert(m_private->surface);

    m_private->physicalDevice = new PhysicalDevice(*m_private->instance);
    assert(m_private->physicalDevice);

    m_private->device = new Device(*m_private->physicalDevice, *m_private->surface, enableValidationLayers);
    assert(m_private->device);

    m_private->shadersCollector = new ShadersCollector(*m_private->device, shadersPath);
    assert(m_private->shadersCollector);

    CreateSwapchain();
}

GameMode::~GameMode()
{
    DeleteSwapchain();

    delete m_private->shadersCollector;
    delete m_private->device;
    delete m_private->physicalDevice;
    delete m_private->surface;
    delete m_private->instance;

    glfwTerminate();

    delete m_private;
}

void GameMode::Start()
{
    m_private->gameModeThread = std::thread([this]()
    {
        this->Launch();
    });
}

void GameMode::Stop()
{
    m_private->closeWindow = true;
    m_private->gameModeThread.join();
}

void GameMode::CreateSwapchain()
{
    m_private->swapchain = new Swapchain(*m_private->device);
    assert(m_private->swapchain);

    m_private->staticObjectPipeline = new StaticObjectPipeline(*m_private->swapchain, *m_private->shadersCollector);
    assert(m_private->staticObjectPipeline);

    m_private->staticObjectDrawable = new StaticObjectDrawable(*m_private->staticObjectPipeline, vertices, indices);
    assert(m_private->staticObjectDrawable);
}

void GameMode::DeleteSwapchain()
{
    for (VkQueue transferQueue : m_private->device->GetTransferQueues())
        vkQueueWaitIdle(transferQueue);
    for (VkQueue graphicsQueue : m_private->device->GetGraphicsQueues())
        vkQueueWaitIdle(graphicsQueue);
    for (VkQueue computeQueue : m_private->device->GetComputeQueues())
        vkQueueWaitIdle(computeQueue);
    for (VkQueue presentQueue : m_private->device->GetPresentQueues())
        vkQueueWaitIdle(presentQueue);

    delete m_private->staticObjectDrawable;
    delete m_private->staticObjectPipeline;
    delete m_private->swapchain;
}

void GameMode::Launch()
{
    if (!m_private->launchMutex.try_lock()) return;

    m_private->closeWindow = false;

    OnStart();

    while (!glfwWindowShouldClose(m_private->surface->GetWindow()) && !m_private->closeWindow)
    {
        glfwPollEvents();

        try
        {
            m_private->swapchain->LoadNextImage();
        }
        catch (SwapchainOutOfDateException&)
        {
            continue;
        }

        m_private->staticObjectDrawable->Draw();

        m_private->swapchain->PresentImage();
    }

    OnStop();

    m_private->launchMutex.unlock();
}
}
