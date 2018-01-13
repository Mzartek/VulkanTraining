#ifndef VT_SURFACE_INCLUDE_H
#define VT_SURFACE_INCLUDE_H

#include "Instance.h"
#include "Window.h"

namespace VT
{
class Surface
{
public:
    Surface(const Instance& instance, Window& window);
    virtual ~Surface();
    Surface(const Surface& other) = delete;
    Surface(Surface&& other) = delete;
    Surface& operator=(const Surface& other) = delete;
    Surface& operator=(Surface&& other) = delete;

    const Instance& GetRelatedInstance() const;
    const Window& GetRelatedWindow() const;

    VkSurfaceKHR GetSurface() const;

private:
    const Instance& m_instance;
    const Window& m_window;

    VkSurfaceKHR m_surface;
};
}

#endif
