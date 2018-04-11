#include <VulkanTraining/GameMode.h>

#include <private/Drawables/StaticObjectDrawable.h>

#include <cassert>
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
GameMode::GameMode(int width, int height, const std::string& title, const std::string& shadersPath)
    : m_launchMutex(nullptr)
	, m_closeWindow(nullptr)
    , m_instance(nullptr)
    , m_window(nullptr)
    , m_surface(nullptr)
    , m_physicalDevice(nullptr)
    , m_device(nullptr)
    , m_shadersCollector(nullptr)
    , m_swapchain(nullptr)
    , m_staticObjectPipeline(nullptr)
    , m_staticObjectDrawable(nullptr)
{
    glfwInit();

	m_launchMutex = new std::mutex;
	assert(m_instance);

	m_closeWindow = new std::atomic<bool>;
	assert(m_closeWindow);

    m_instance = new Instance(title, enableValidationLayers);
    assert(m_instance);

    m_surface = new Surface(*m_instance, width, height, title, this, WindowSizeCallback);
    assert(m_surface);

    m_physicalDevice = new PhysicalDevice(*m_instance);
    assert(m_physicalDevice);

    m_device = new Device(*m_physicalDevice, *m_surface, enableValidationLayers);
    assert(m_device);

    m_shadersCollector = new ShadersCollector(*m_device, shadersPath);
    assert(m_shadersCollector);

    CreateSwapchain();
}

GameMode::~GameMode()
{
    DeleteSwapchain();

    delete m_shadersCollector;
    delete m_device;
    delete m_physicalDevice;
    delete m_surface;
    delete m_instance;
	delete m_launchMutex;
	delete m_closeWindow;
	delete m_launchMutex;

    glfwTerminate();
}

void GameMode::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) return;

    GameMode* gameMode = static_cast<GameMode*>(glfwGetWindowUserPointer(window));
    gameMode->DeleteSwapchain();
    gameMode->CreateSwapchain();
}

void GameMode::Launch(EventCallbacks& eventCallbacks)
{
    if (!m_launchMutex->try_lock()) return;

    *m_closeWindow = false;

    if (eventCallbacks.onStart)
        eventCallbacks.onStart();

    while (!glfwWindowShouldClose(m_surface->GetWindow()) && !*m_closeWindow)
    {
        glfwPollEvents();

        try
        {
            m_swapchain->LoadNextImage();
        }
        catch (SwapchainOutOfDateException&)
        {
            continue;
        }

        m_staticObjectDrawable->Draw();

        m_swapchain->PresentImage();
    }

    if (eventCallbacks.onStop)
        eventCallbacks.onStop();

    m_launchMutex->unlock();
}

void GameMode::Stop()
{
    *m_closeWindow = true;
}

void GameMode::CreateSwapchain()
{
    m_swapchain = new Swapchain(*m_device);
    assert(m_swapchain);

    m_staticObjectPipeline = new StaticObjectPipeline(*m_swapchain, *m_shadersCollector);
    assert(m_staticObjectPipeline);

    m_staticObjectDrawable = new StaticObjectDrawable(*m_staticObjectPipeline, vertices, indices);
    assert(m_staticObjectDrawable);
}

void GameMode::DeleteSwapchain()
{
    for (VkQueue transferQueue : m_device->GetTransferQueues())
        vkQueueWaitIdle(transferQueue);
    for (VkQueue graphicsQueue : m_device->GetGraphicsQueues())
        vkQueueWaitIdle(graphicsQueue);
    for (VkQueue computeQueue : m_device->GetComputeQueues())
        vkQueueWaitIdle(computeQueue);
    for (VkQueue presentQueue : m_device->GetPresentQueues())
        vkQueueWaitIdle(presentQueue);

    delete m_staticObjectDrawable;
    delete m_staticObjectPipeline;
    delete m_swapchain;
}
}
