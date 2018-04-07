#ifndef VT_GAME_MODE_INCLUDE_H
#define VT_GAME_MODE_INCLUDE_H

#include "Export.h"

#include <string>
#include <functional>
#include <mutex>
#include <atomic>

class GLFWwindow;

namespace VT
{
class Instance;
class Window;
class Surface;
class PhysicalDevice;
class Device;
class ShadersCollector;
class Swapchain;
class StaticObjectPipeline;
class StaticObjectDrawable;

struct EventCallbacks
{
    std::function<void()> onStart;
    std::function<void()> onStop;
};

class LIB_INTERFACE GameMode
{
public:
    GameMode(int width, int height, const std::string& title, const std::string& shadersPath);
    virtual ~GameMode();
    GameMode(const GameMode& other) = delete;
    GameMode(GameMode&& other) = delete;
    GameMode& operator=(const GameMode& other) = delete;
    GameMode& operator=(GameMode&& other) = delete;

    void Launch(EventCallbacks& eventCallbacks);
    void Stop();

private:
    static void WindowSizeCallback(GLFWwindow* window, int width, int height);

    void CreateSwapchain();
    void DeleteSwapchain();

    std::mutex m_launchMutex;
    std::atomic<bool> m_closeWindow;

    Instance* m_instance;
    Window* m_window;
    Surface* m_surface;
    PhysicalDevice* m_physicalDevice;
    Device* m_device;
    ShadersCollector* m_shadersCollector;
    Swapchain* m_swapchain;
    StaticObjectPipeline* m_staticObjectPipeline;
    StaticObjectDrawable* m_staticObjectDrawable;
};
}

#endif
