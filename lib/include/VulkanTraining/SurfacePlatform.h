#ifndef VT_SURFACE_PLATFORM_INCLUDE_H
#define VT_SURFACE_PLATFORM_INCLUDE_H

namespace VT
{
enum class SurfacePlatform
{
    WIN32,
    XLIB,
    XCB,
    WAYLAND
};

using winid_t = void*;
}

#endif
