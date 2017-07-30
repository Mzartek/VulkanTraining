#include "VTSurface.h"

#include <stdexcept>

namespace VT
{
VTSurface::VTSurface(const VTInstance& vtInstance, VTWindow& vtWindow)
    : m_instance(vtInstance)
    , m_window(vtWindow)
    , m_surface(VK_NULL_HANDLE)
{
    VkResult result = glfwCreateWindowSurface(m_instance.GetInstance(), vtWindow.GetWindow(), nullptr, &m_surface);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create surface");
}

VTSurface::~VTSurface()
{
    vkDestroySurfaceKHR(m_instance.GetInstance(), m_surface, nullptr);
}

VkSurfaceKHR VTSurface::GetSurface()
{
    return m_surface;
}

VkSurfaceKHR VTSurface::GetSurface() const
{
    return m_surface;
}

const VTWindow& VTSurface::GetRelatedWindow() const
{
    return m_window;
}
}
