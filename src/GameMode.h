#ifndef VT_GAME_MODE_INCLUDE_H
#define VT_GAME_MODE_INCLUDE_H

#include "VTPhysicalDevice.h"

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
    VTWindow* m_vtWindow;
    VTInstance* m_vtInstance;
    VTPhysicalDevice* m_vtPhysicalDevice;
};
}

#endif
