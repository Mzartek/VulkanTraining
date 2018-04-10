set(Assimp_FOUND "FALSE")

find_library(Assimp_LIBRARY NAMES assimp libassimp)
find_path(Assimp_INCLUDE_DIR assimp/version.h)

if (Assimp_LIBRARY AND Assimp_INCLUDE_DIR)
	set(Assimp_FOUND "TRUE")
	set(Assimp_LIBRARIES ${Assimp_LIBRARY})
	set(Assimp_INCLUDE_DIRS ${Assimp_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Assimp REQUIRED_VARS
	Assimp_LIBRARIES
	Assimp_INCLUDE_DIRS)

mark_as_advanced(Assimp_LIBRARY Assimp_INCLUDE_DIR)
