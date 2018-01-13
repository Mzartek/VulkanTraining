#include <VulkanTraining/GameMode.h>

#include <private/Pipelines/SimplePipeline.h>
#include <private/CommandPool.h>

#include <cassert>

namespace
{
#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif
}

namespace VT
{
GameMode::GameMode(int width, int height, const std::string& title, const std::string& shadersPath)
    : m_instance(nullptr)
    , m_window(nullptr)
    , m_surface(nullptr)
    , m_physicalDevice(nullptr)
    , m_device(nullptr)
    , m_swapchain(nullptr)
    , m_simplePipeline(nullptr)
    , m_commandPool(nullptr)
{
    glfwInit();

    m_instance = new Instance(title, enableValidationLayers);
    assert(m_instance);

    m_window = new Window(width, height, title);
    assert(m_window);

    m_surface = new Surface(*m_instance, *m_window);
    assert(m_surface);

    m_physicalDevice = new PhysicalDevice(*m_instance);
    assert(m_physicalDevice);

    m_device = new Device(*m_physicalDevice, *m_surface, enableValidationLayers);
    assert(m_device);

    m_swapchain = new Swapchain(*m_device);
    assert(m_swapchain);

    m_simplePipeline = new SimplePipeline(*m_swapchain, shadersPath);
    assert(m_simplePipeline);

    m_commandPool = new CommandPool(*m_device, *m_simplePipeline);
    assert(m_commandPool);
}

GameMode::~GameMode()
{
    delete m_commandPool;
    delete m_simplePipeline;
    delete m_swapchain;
    delete m_device;
    delete m_physicalDevice;
    delete m_surface;
    delete m_window;
    delete m_instance;

    glfwTerminate();
}

void GameMode::Launch()
{
    Init();

    while (!glfwWindowShouldClose(m_window->GetWindow()))
    {
        glfwPollEvents();
        MainLoop();
    }

    CleanUp();
}
}
