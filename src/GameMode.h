#ifndef VT_GAME_MODE_INCLUDE_H
#define VT_GAME_MODE_INCLUDE_H

#include "VTSwapchain.h"

namespace VT
{
class GameMode
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
    VTInstance* m_vtInstance;
    VTWindow* m_vtWindow;
    VTSurface* m_vtSurface;
    VTPhysicalDevice* m_vtPhysicalDevice;
    VTDevice* m_vtDevice;
    VTSwapchain* m_vtSwapchain;

};
}

#endif
