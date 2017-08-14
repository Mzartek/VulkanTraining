#ifdef LIB_EXPORT
#	ifdef WIN32
#		define LIB_INTERFACE __declspec(dllexport)
#	else
#		define LIB_INTERFACE
#	endif
#else
#	ifdef WIN32
#		define LIB_INTERFACE __declspec(dllimport)
#	else
#		define LIB_INTERFACE
#	endif
#endif