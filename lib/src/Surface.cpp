#include <VulkanTraining/Surface.h>

#include <stdexcept>

namespace VT
{
Surface::Surface(const Instance& instance, Window& window)
    : m_instance(instance)
    , m_window(window)
    , m_surface(VK_NULL_HANDLE)
{
    VkResult result = glfwCreateWindowSurface(m_instance.GetInstance(), window.GetWindow(), nullptr, &m_surface);
    if (result != VK_SUCCESS)
        throw std::runtime_error("Failed to create surface");
}

Surface::~Surface()
{
    vkDestroySurfaceKHR(m_instance.GetInstance(), m_surface, nullptr);
}

VkSurfaceKHR Surface::GetSurface()
{
    return m_surface;
}

VkSurfaceKHR Surface::GetSurface() const
{
    return m_surface;
}

const Window& Surface::GetRelatedWindow() const
{
    return m_window;
}
}
