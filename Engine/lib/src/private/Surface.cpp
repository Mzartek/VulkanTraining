#include <private/Surface.h>

#include <stdexcept>

namespace VT
{
Surface::Surface(Instance& instance, Window& window)
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

Instance& Surface::GetRelatedInstance() const
{
    return m_instance;
}

Window& Surface::GetRelatedWindow() const
{
    return m_window;
}

VkSurfaceKHR Surface::GetSurface() const
{
    return m_surface;
}
}
