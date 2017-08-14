#ifndef VT_SURFACE_INCLUDE_H
#define VT_SURFACE_INCLUDE_H

#include "VTInstance.h"
#include "VTWindow.h"

namespace VT
{
class LIB_INTERFACE Surface
{
public:
    Surface(const Instance& instance, Window& window);
    virtual ~Surface();
    Surface(const Surface& other) = delete;
    Surface(Surface&& other) = delete;
    Surface& operator=(const Surface& other) = delete;
    Surface& operator=(Surface&& other) = delete;

    VkSurfaceKHR GetSurface();
    VkSurfaceKHR GetSurface() const;

    const Window& GetRelatedWindow() const;

private:
    const Instance& m_instance;
    const Window& m_window;
    VkSurfaceKHR m_surface;
};
}

#endif
