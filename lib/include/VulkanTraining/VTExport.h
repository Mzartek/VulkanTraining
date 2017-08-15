#if defined(WIN32) && !defined(__MINGW32__)
#   ifdef ENGINE_EXPORT
#       define LIB_INTERFACE __declspec(dllexport)
#   else
#       define LIB_INTERFACE __declspec(dllimport)
#   endif
#else
#   define LIB_INTERFACE
#endif
