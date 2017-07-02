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

set(GLM_FOUND "FALSE")

find_path(GLM_INCLUDE_DIR glm/glm.hpp)

if (GLM_INCLUDE_DIR)
	set(GLM_FOUND "TRUE")
	set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLM REQUIRED_VARS
	GLM_INCLUDE_DIRS)

mark_as_advanced(GLM_INCLUDE_DIR)
