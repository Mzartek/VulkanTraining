#ifndef VT_SURFACE_INCLUDE_H
#define VT_SURFACE_INCLUDE_H

#include "VTWindow.h"
#include "VTInstance.h"

namespace VT
{
class VTSurface
{
public:
    VTSurface(const VTInstance& vtInstance, VTWindow& vtWindow);
    virtual ~VTSurface();
    VTSurface(const VTSurface& other) = delete;
    VTSurface(VTSurface&& other) = delete;
    VTSurface& operator=(const VTSurface& other) = delete;
    VTSurface& operator=(VTSurface&& other) = delete;

    VkSurfaceKHR GetSurface();
    VkSurfaceKHR GetSurface() const;

    const VTWindow& GetRelatedWindow() const;

private:
    const VTInstance& m_instance;
    const VTWindow& m_window;
    VkSurfaceKHR m_surface;
};
}

#endif
