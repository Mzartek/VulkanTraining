#ifndef VT_SURFACE_INCLUDE_H
#define VT_SURFACE_INCLUDE_H

#include "Instance.h"

namespace VT
{
class Surface : public NonCopyableObject
{
public:
    Surface(Instance& instance, int width, int height, const std::string& title, void* userPointer, GLFWwindowsizefun sizeCallback);
    ~Surface() override;

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

    Instance& GetRelatedInstance() const;

    GLFWwindow* GetWindow() const;
    VkSurfaceKHR GetSurface() const;

private:
    Instance& m_instance;

    GLFWwindow* m_window;
    VkSurfaceKHR m_surface;
};
}

#endif
