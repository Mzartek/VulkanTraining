#ifndef VT_SURFACE_INCLUDE_H
#define VT_SURFACE_INCLUDE_H

#include <VulkanTraining/SurfacePlatform.h>

#include "Instance.h"

namespace VT
{
class Surface : public NonCopyableObject
{
public:
    Surface(Instance& instance, winid_t winId, SurfacePlatform surfacePlatform);
    ~Surface() override;

    virtual uint32_t GetWidth() const;
    virtual uint32_t GetHeight() const;

    Instance& GetRelatedInstance() const;

    VkSurfaceKHR GetSurface() const;

private:
    Instance& m_instance;

    VkSurfaceKHR m_surface;
};
}

#endif
