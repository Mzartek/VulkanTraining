#ifndef VT_GAME_MODE_INCLUDE_H
#define VT_GAME_MODE_INCLUDE_H

#include "Export.h"

#include <string>

namespace VT
{
class Instance;
class Window;
class Surface;
class PhysicalDevice;
class Device;
class Swapchain;
class StaticObjectPipeline;
class StaticObjectDrawable;

class LIB_INTERFACE GameMode
{
public:
    GameMode(int width, int height, const std::string& title, const std::string& shadersPath);
    virtual ~GameMode();
    GameMode(const GameMode& other) = delete;
    GameMode(GameMode&& other) = delete;
    GameMode& operator=(const GameMode& other) = delete;
    GameMode& operator=(GameMode&& other) = delete;

    void Launch();

    void OnWindowResized(int width, int height);

    void MainLoop();

private:
    void RecreateSwapchain();

    std::string m_shadersPath;

    Instance* m_instance;
    Window* m_window;
    Surface* m_surface;
    PhysicalDevice* m_physicalDevice;
    Device* m_device;
    Swapchain* m_swapchain;
    StaticObjectPipeline* m_staticObjectPipeline;
    StaticObjectDrawable* m_staticObjectDrawable;
};
}

#endif
