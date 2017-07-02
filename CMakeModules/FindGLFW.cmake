#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# This will define:
#   GLFW_FOUND
#   GLFW_LIBRARIES
#   GLFW_INCLUDE_DIRS

set(GLFW_FOUND "FALSE")

find_library(GLFW_LIBRARY NAMES glfw libglfw)
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h)

if (GLFW_LIBRARY AND GLFW_INCLUDE_DIR)
	set(GLFW_FOUND "TRUE")
	set(GLFW_LIBRARIES ${GLFW_LIBRARY})
	set(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW REQUIRED_VARS
	GLFW_LIBRARIES
	GLFW_INCLUDE_DIRS)

mark_as_advanced(GLFW_LIBRARY GLFW_INCLUDE_DIR)
