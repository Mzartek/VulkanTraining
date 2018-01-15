set(GLSLANG_FOUND "FALSE")

find_library(SPIRV_LIBRARY NAMES SPIRV libSPIRV)
find_library(glslang_LIBRARY NAMES glslang libglslang)
find_library(OGLCompiler_LIBRARY NAMES OGLCompiler libOGLCompiler)
find_library(OSDependent_LIBRARY NAMES OSDependent libOSDependent)
find_library(HLSL_LIBRARY NAMES HLSL libHLSL)

find_path(SPIRV_INCLUDE_DIR SPIRV/GlslangToSpv.h)

if (SPIRV_LIBRARY AND glslang_LIBRARY AND OGLCompiler_LIBRARY AND OSDependent_LIBRARY AND HLSL_LIBRARY AND SPIRV_INCLUDE_DIR)
	set(GLSLANG_FOUND "TRUE")
	set(GLSLANG_LIBRARIES ${SPIRV_LIBRARY} ${glslang_LIBRARY} ${OGLCompiler_LIBRARY} ${OSDependent_LIBRARY} ${HLSL_LIBRARY})
	set(GLSLANG_INCLUDE_DIRS ${SPIRV_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SPIRV REQUIRED_VARS
	GLSLANG_LIBRARIES
	GLSLANG_INCLUDE_DIRS)

mark_as_advanced(SPIRV_LIBRARY glslang_LIBRARY OGLCompiler_LIBRARY OSDependent_LIBRARY HLSL_LIBRARY SPIRV_INCLUDE_DIR)
