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
