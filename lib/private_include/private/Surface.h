#ifndef VT_SURFACE_INCLUDE_H
#define VT_SURFACE_INCLUDE_H

#include "Instance.h"
#include "Window.h"

namespace VT
{
class Surface
{
public:
    Surface(Instance& instance, Window& window);
    virtual ~Surface();
    Surface(const Surface& other) = delete;
    Surface(Surface&& other) = delete;
    Surface& operator=(const Surface& other) = delete;
    Surface& operator=(Surface&& other) = delete;

    Instance& GetRelatedInstance() const;
    Window& GetRelatedWindow() const;

    VkSurfaceKHR GetSurface() const;

private:
    Instance& m_instance;
    Window& m_window;

    VkSurfaceKHR m_surface;
};
}

#endif
