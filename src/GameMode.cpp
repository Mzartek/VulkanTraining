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
    : m_vtWindow(nullptr)
    , m_vtInstance(nullptr)
    , m_vtPhysicalDevice(nullptr)
{
    glfwInit();

    m_vtWindow = new VTWindow(width, height, title);
    assert(m_vtWindow);

    m_vtInstance = new VTInstance(*m_vtWindow, enableValidationLayers);
    assert(m_vtInstance);

    m_vtPhysicalDevice = new VTPhysicalDevice(*m_vtInstance);
    assert(m_vtPhysicalDevice);
}

GameMode::~GameMode()
{
    delete m_vtPhysicalDevice;
    delete m_vtInstance;
    delete m_vtWindow;

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
