#ifndef VT_GAME_MODE_INCLUDE_H
#define VT_GAME_MODE_INCLUDE_H

#include "Swapchain.h"

namespace VT
{
class LIB_INTERFACE GameMode
{
public:
    GameMode(int width, int height, const std::string& title);
    virtual ~GameMode();
    GameMode(const GameMode& other) = delete;
    GameMode(GameMode&& other) = delete;
    GameMode& operator=(const GameMode& other) = delete;
    GameMode& operator=(GameMode&& other) = delete;

    void Launch();

    virtual void Init() = 0;
    virtual void MainLoop() = 0;
    virtual void CleanUp() = 0;

private:
    Instance* m_instance;
    Window* m_window;
    Surface* m_surface;
    PhysicalDevice* m_physicalDevice;
    Device* m_device;
    Swapchain* m_swapchain;

};
}

#endif
