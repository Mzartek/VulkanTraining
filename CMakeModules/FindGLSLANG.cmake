set(GLSLANG_FOUND "FALSE")

find_library(SPIRV_RELEASE_LIBRARY NAMES SPIRV libSPIRV)
find_library(glslang_RELEASE_LIBRARY NAMES glslang libglslang)
find_library(OGLCompiler_RELEASE_LIBRARY NAMES OGLCompiler libOGLCompiler)
find_library(OSDependent_RELEASE_LIBRARY NAMES OSDependent libOSDependent)
find_library(HLSL_RELEASE_LIBRARY NAMES HLSL libHLSL)

if(MSVC)
	find_library(SPIRV_DEBUG_LIBRARY NAMES SPIRVd)
	find_library(glslang_DEBUG_LIBRARY NAMES glslangd)
	find_library(OGLCompiler_DEBUG_LIBRARY NAMES OGLCompilerd)
	find_library(OSDependent_DEBUG_LIBRARY NAMES OSDependentd)
	find_library(HLSL_DEBUG_LIBRARY NAMES HLSLd)
else()
	set(SPIRV_DEBUG_LIBRARY SPIRV_RELEASE_LIBRARY)
	set(glslang_DEBUG_LIBRARY glslang_RELEASE_LIBRARY)
	set(OGLCompiler_DEBUG_LIBRARY OGLCompiler_RELEASE_LIBRARY)
	set(OSDependent_DEBUG_LIBRARY OSDependent_RELEASE_LIBRARY)
	set(HLSL_DEBUG_LIBRARY HLSL_RELEASE_LIBRARY)
endif()

find_path(SPIRV_INCLUDE_DIR SPIRV/GlslangToSpv.h)

if (SPIRV_RELEASE_LIBRARY AND glslang_RELEASE_LIBRARY AND OGLCompiler_RELEASE_LIBRARY AND OSDependent_RELEASE_LIBRARY AND HLSL_RELEASE_LIBRARY AND
	SPIRV_DEBUG_LIBRARY AND glslang_DEBUG_LIBRARY AND OGLCompiler_DEBUG_LIBRARY AND OSDependent_DEBUG_LIBRARY AND HLSL_DEBUG_LIBRARY AND
	SPIRV_INCLUDE_DIR)
	set(GLSLANG_FOUND "TRUE")
	set(GLSLANG_RELEASE_LIBRARIES ${SPIRV_RELEASE_LIBRARY} ${glslang_RELEASE_LIBRARY} ${OGLCompiler_RELEASE_LIBRARY} ${OSDependent_RELEASE_LIBRARY} ${HLSL_RELEASE_LIBRARY})
	set(GLSLANG_DEBUG_LIBRARIES ${SPIRV_DEBUG_LIBRARY} ${glslang_DEBUG_LIBRARY} ${OGLCompiler_DEBUG_LIBRARY} ${OSDependent_DEBUG_LIBRARY} ${HLSL_DEBUG_LIBRARY})
	set(GLSLANG_INCLUDE_DIRS ${SPIRV_INCLUDE_DIR})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SPIRV REQUIRED_VARS
	GLSLANG_RELEASE_LIBRARIES
	GLSLANG_DEBUG_LIBRARIES
	GLSLANG_INCLUDE_DIRS)

mark_as_advanced(SPIRV_RELEASE_LIBRARY glslang_RELEASE_LIBRARY OGLCompiler_RELEASE_LIBRARY OSDependent_RELEASE_LIBRARY HLSL_RELEASE_LIBRARY
	SPIRV_DEBUG_LIBRARY glslang_DEBUG_LIBRARY OGLCompiler_DEBUG_LIBRARY OSDependent_DEBUG_LIBRARY HLSL_DEBUG_LIBRARY
	SPIRV_INCLUDE_DIR)
