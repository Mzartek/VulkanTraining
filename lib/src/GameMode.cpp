#include <VulkanTraining/GameMode.h>

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
GameMode::GameMode(int width, int height, const std::string& title)
    : m_instance(nullptr)
    , m_window(nullptr)
    , m_surface(nullptr)
    , m_physicalDevice(nullptr)
    , m_device(nullptr)
    , m_swapchain(nullptr)
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
}

GameMode::~GameMode()
{
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
