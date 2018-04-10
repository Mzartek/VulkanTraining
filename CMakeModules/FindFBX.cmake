set(FBX_FOUND "FALSE")

find_library(FBX_LIBRARY NAMES fbxsdk)
find_path(FBX_INCLUDE_DIR fbxsdk.h)

if (FBX_LIBRARY AND FBX_INCLUDE_DIR)
	set(FBX_FOUND "TRUE")
	set(FBX_LIBRARIES ${FBX_LIBRARY})
	set(FBX_INCLUDE_DIRS ${FBX_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FBX REQUIRED_VARS
	FBX_LIBRARIES
	FBX_INCLUDE_DIRS)

mark_as_advanced(FBX_LIBRARY FBX_INCLUDE_DIR)
