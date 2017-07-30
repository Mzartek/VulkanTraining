#include "GameMode.h"

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
    : m_vtInstance(nullptr)
    , m_vtWindow(nullptr)
    , m_vtSurface(nullptr)
    , m_vtPhysicalDevice(nullptr)
    , m_vtDevice(nullptr)
    , m_vtSwapchain(nullptr)
{
    glfwInit();

    m_vtInstance = new VTInstance(title, enableValidationLayers);
    assert(m_vtInstance);

    m_vtWindow = new VTWindow(width, height, title);
    assert(m_vtWindow);

    m_vtSurface = new VTSurface(*m_vtInstance, *m_vtWindow);
    assert(m_vtSurface);

    m_vtPhysicalDevice = new VTPhysicalDevice(*m_vtInstance);
    assert(m_vtPhysicalDevice);

    m_vtDevice = new VTDevice(*m_vtPhysicalDevice, *m_vtSurface, enableValidationLayers);
    assert(m_vtDevice);

    m_vtSwapchain = new VTSwapchain(*m_vtDevice);
    assert(m_vtSwapchain);
}

GameMode::~GameMode()
{
    delete m_vtSwapchain;
    delete m_vtDevice;
    delete m_vtPhysicalDevice;
    delete m_vtSurface;
    delete m_vtWindow;
    delete m_vtInstance;

    glfwTerminate();
}

void GameMode::Launch()
{
    Init();

    while (!glfwWindowShouldClose(m_vtWindow->GetWindow()))
    {
        glfwPollEvents();
        MainLoop();
    }

    CleanUp();
}
}
