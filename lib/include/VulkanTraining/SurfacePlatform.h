#ifndef VT_SURFACE_PLATFORM_INCLUDE_H
#define VT_SURFACE_PLATFORM_INCLUDE_H

namespace VT
{
enum class SurfacePlatform
{
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    WIN32,
#endif

#if defined(VK_USE_PLATFORM_XLIB_KHR)
    XLIB,
#endif

#if defined(VK_USE_PLATFORM_XCB_KHR)
    XCB,
#endif

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
    WAYLAND
#endif
};

using winid_t = void*;
}

#endif
