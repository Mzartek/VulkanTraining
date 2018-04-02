#include <private/Surface.h>

#include <stdexcept>

namespace
{
#if defined(VK_USE_PLATFORM_WIN32_KHR)
VkSurfaceKHR CreateWIN32Surface(VkInstance /*instance*/, VT::winid_t /*winId*/)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;

    throw std::runtime_error("VK_USE_PLATFORM_WIN32_KHR not supported yet");

    return surface;
}
#endif

#if defined(VK_USE_PLATFORM_XLIB_KHR)
VkSurfaceKHR CreateXLIBSurface(VkInstance /*instance*/, VT::winid_t /*winId*/)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;

    throw std::runtime_error("VK_USE_PLATFORM_XLIB_KHR not supported yet");

    return surface;
}
#endif

#if defined(VK_USE_PLATFORM_XCB_KHR)
VkSurfaceKHR CreateXCBSurface(VkInstance /*instance*/, VT::winid_t /*winId*/)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;

    throw std::runtime_error("VK_USE_PLATFORM_XCB_KHR not supported yet");

    return surface;
}
#endif

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
VkSurfaceKHR CreateWAYLANDSurface(VkInstance /*instance*/, VT::winid_t /*winId*/)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;

    throw std::runtime_error("VK_USE_PLATFORM_WAYLAND_KHR not supported yet");

    return surface;
}
#endif

VkSurfaceKHR CreateSurface(VkInstance instance, VT::winid_t winId, VT::SurfacePlatform surfacePlatform)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;

    switch(surfacePlatform)
    {
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    case VT::SurfacePlatform::WIN32:
        surface = CreateWIN32Surface(instance, winId);
        break;
#endif

#if defined(VK_USE_PLATFORM_XLIB_KHR)
    case VT::SurfacePlatform::XLIB:
        surface = CreateXLIBSurface(instance, winId);
        break;
#endif

#if defined(VK_USE_PLATFORM_XCB_KHR)
    case VT::SurfacePlatform::XCB:
        surface = CreateXCBSurface(instance, winId);
        break;
#endif

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    case VT::SurfacePlatform::WAYLAND:
        surface = CreateWAYLANDSurface(instance, winId);
        break;
#endif

     default:
        throw std::runtime_error("Not supported SurfacePlatform");
    }

    return surface;
}
}

namespace VT
{
Surface::Surface(Instance& instance, winid_t winId, SurfacePlatform surfacePlatform)
    : m_instance(instance)
    , m_surface(CreateSurface(m_instance.GetInstance(), winId, surfacePlatform))
{
}

Surface::~Surface()
{
    vkDestroySurfaceKHR(m_instance.GetInstance(), m_surface, nullptr);
}

uint32_t Surface::GetWidth() const
{
    return 0;
}

uint32_t Surface::GetHeight() const
{
    return 0;
}

Instance& Surface::GetRelatedInstance() const
{
    return m_instance;
}

VkSurfaceKHR Surface::GetSurface() const
{
    return m_surface;
}
}
