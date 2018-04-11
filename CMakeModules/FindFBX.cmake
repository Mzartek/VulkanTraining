set(FBX_FOUND "FALSE")

find_library(FBX_RELEASE_LIBRARY NAMES libfbxsdk fbxsdk PATH_SUFFIXES release)
find_library(FBX_DEBUG_LIBRARY NAMES libfbxsdk fbxsdk PATH_SUFFIXES debug)
find_path(FBX_INCLUDE_DIR fbxsdk.h)

if (FBX_RELEASE_LIBRARY AND FBX_DEBUG_LIBRARY AND FBX_INCLUDE_DIR)
	set(FBX_FOUND "TRUE")
	set(FBX_LIBRARIES optimized ${FBX_RELEASE_LIBRARY} debug ${FBX_DEBUG_LIBRARY})
	set(FBX_INCLUDE_DIRS ${FBX_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FBX REQUIRED_VARS
	FBX_LIBRARIES
	FBX_INCLUDE_DIRS)

mark_as_advanced(FBX_RELEASE_LIBRARY FBX_DEBUG_LIBRARY FBX_INCLUDE_DIR)
