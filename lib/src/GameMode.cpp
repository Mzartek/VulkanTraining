#include <VulkanTraining/GameMode.h>

#include <private/Drawable/SimpleDrawable.h>

#include <cassert>

namespace
{
#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

void InternalOnWindowResized(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0) return;

    VT::GameMode* gameMode = static_cast<VT::GameMode*>(glfwGetWindowUserPointer(window));
    gameMode->OnWindowResized(width, height);
}
}

namespace VT
{
GameMode::GameMode(int width, int height, const std::string& title, const std::string& shadersPath)
    : m_shadersPath(shadersPath)
    , m_instance(nullptr)
    , m_window(nullptr)
    , m_surface(nullptr)
    , m_physicalDevice(nullptr)
    , m_device(nullptr)
    , m_commandPool(nullptr)
    , m_swapchain(nullptr)
    , m_simplePipeline(nullptr)
{
    glfwInit();

    m_instance = new Instance(title, enableValidationLayers);
    assert(m_instance);

    m_window = new Window(width, height, title, this, InternalOnWindowResized);
    assert(m_window);

    m_surface = new Surface(*m_instance, *m_window);
    assert(m_surface);

    m_physicalDevice = new PhysicalDevice(*m_instance);
    assert(m_physicalDevice);

    m_device = new Device(*m_physicalDevice, *m_surface, enableValidationLayers);
    assert(m_device);

    m_commandPool = new CommandPool(*m_device);
    assert(m_commandPool);

    m_swapchain = new Swapchain(*m_device);
    assert(m_swapchain);

    m_simplePipeline = new SimplePipeline(*m_swapchain, m_shadersPath);
    assert(m_simplePipeline);

    m_simpleDrawable = new SimpleDrawable(*m_commandPool, *m_simplePipeline);
    assert(m_simpleDrawable);
}

GameMode::~GameMode()
{
    delete m_simpleDrawable;
    delete m_simplePipeline;
    delete m_swapchain;
    delete m_commandPool;
    delete m_device;
    delete m_physicalDevice;
    delete m_surface;
    delete m_window;
    delete m_instance;

    glfwTerminate();
}

void GameMode::Launch()
{
    while (!glfwWindowShouldClose(m_window->GetWindow()))
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

        m_simpleDrawable->Draw();

        m_swapchain->PresentImage();
    }

    vkDeviceWaitIdle(m_device->GetDevice());
}

void GameMode::OnWindowResized(int /*width*/, int /*height*/)
{
    RecreateSwapchain();
}

void GameMode::RecreateSwapchain()
{
    for (VkQueue graphicsQueue : m_device->GetGraphicsQueues())
        vkQueueWaitIdle(graphicsQueue);
    for (VkQueue presentQueue : m_device->GetPresentQueues())
        vkQueueWaitIdle(presentQueue);

    delete m_simpleDrawable;
    delete m_simplePipeline;
    delete m_swapchain;

    m_swapchain = new Swapchain(*m_device);
    assert(m_swapchain);

    m_simplePipeline = new SimplePipeline(*m_swapchain, m_shadersPath);
    assert(m_simplePipeline);

    m_simpleDrawable = new SimpleDrawable(*m_commandPool, *m_simplePipeline);
    assert(m_simpleDrawable);
}
}
