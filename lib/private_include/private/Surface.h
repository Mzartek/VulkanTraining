#ifndef VT_SURFACE_INCLUDE_H
#define VT_SURFACE_INCLUDE_H

#include "Instance.h"
#include "Window.h"

namespace VT
{
class Surface : public NonCopyableObject
{
public:
    Surface(Instance& instance, Window& window);
    ~Surface() override;

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
