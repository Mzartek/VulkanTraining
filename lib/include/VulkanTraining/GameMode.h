#ifndef VT_GAME_MODE_INCLUDE_H
#define VT_GAME_MODE_INCLUDE_H

#include "Export.h"

namespace VT
{
struct GameModePrivate;

class LIB_INTERFACE GameMode
{
public:
    GameMode(int width, int height, const char* title, const char* shadersPath);
    ~GameMode();
    GameMode(const GameMode& other) = delete;
    GameMode(GameMode&& other) = delete;
    GameMode& operator=(const GameMode& other) = delete;
    GameMode& operator=(GameMode&& other) = delete;

    void Start();
    void Stop();

protected:
    virtual void OnStart() = 0;
    virtual void OnStop() = 0;

private:
    void CreateSwapchain();
    void DeleteSwapchain();

    void Launch();

    friend struct GameModePrivate;
    GameModePrivate* m_private;
};
}

#endif
