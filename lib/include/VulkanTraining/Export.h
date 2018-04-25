#ifndef VT_EXPORT_INCLUDE_H
#define VT_EXPORT_INCLUDE_H

#if defined(_WIN32) && !defined(__MINGW32__)
#   ifdef ViewerLib_EXPORTS
#       define LIB_INTERFACE __declspec(dllexport)
#   else
#       define LIB_INTERFACE __declspec(dllimport)
#   endif
#else
#    define LIB_INTERFACE
#endif

#endif
