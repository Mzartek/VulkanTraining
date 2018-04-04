#include <VulkanTraining/GameMode.h>

#include <private/Drawables/StaticObjectDrawable.h>

#include <cassert>

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

void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) return;

    VT::GameMode* gameMode = static_cast<VT::GameMode*>(glfwGetWindowUserPointer(window));
    gameMode->UpdateSwapchain();
}
}

namespace VT
{
GameMode::GameMode(int width, int height, const std::string& title, const std::string& shadersPath)
    : m_instance(nullptr)
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

    glfwTerminate();
}

void GameMode::Launch()
{
    while (!glfwWindowShouldClose(m_surface->GetWindow()))
    {
        glfwPollEvents();

        try
        {
            m_swapchain->LoadNextImage();
        }
        catch (SwapchainOutOfDateException& ex)
        {
            continue;
        }

        m_staticObjectDrawable->Draw();

        m_swapchain->PresentImage();
    }
}

void GameMode::UpdateSwapchain()
{
    DeleteSwapchain();
    CreateSwapchain();
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
