set(LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private_include")

file(GLOB_RECURSE LIB_HEADER_FILES "${LIB_INCLUDE_DIR}/VulkanTraining/*.h")
file(GLOB_RECURSE LIB_PRIVATE_HEADER_FILES "${LIB_PRIVATE_INCLUDE_DIR}/private/*.h")

file(GLOB_RECURSE LIB_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(ViewerLib SHARED
	${LIB_HEADER_FILES}
	${LIB_PRIVATE_HEADER_FILES}
	${LIB_SOURCE_FILES})

target_include_directories(ViewerLib PUBLIC
	${LIB_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS})
target_include_directories(ViewerLib PRIVATE
	${LIB_PRIVATE_INCLUDE_DIR}
	${Vulkan_INCLUDE_DIRS}
	${Assimp_INCLUDE_DIRS}
	${FBX_INCLUDE_DIRS}
	${GLSLANG_INCLUDE_DIRS})

target_link_libraries(ViewerLib PUBLIC
	${Boost_LIBRARIES})
target_link_libraries(ViewerLib PRIVATE
	${Vulkan_LIBRARIES}
	${Assimp_LIBRARIES}
	${FBX_LIBRARIES}
	${GLSLANG_LIBRARIES})

if(WIN32)
	target_compile_definitions(ViewerLib PRIVATE VK_USE_PLATFORM_WIN32_KHR)
elseif(UNIX)
	if(X11_FOUND)
		target_include_directories(ViewerLib PRIVATE ${X11_INCLUDE_DIR})
		target_link_libraries(ViewerLib PRIVATE ${X11_LIBRARIES})
		target_compile_definitions(ViewerLib PRIVATE VK_USE_PLATFORM_XLIB_KHR=1)
	endif()

	if(XCB_FOUND)
		target_include_directories(ViewerLib PRIVATE ${XCB_INCLUDE_DIRS})
		target_link_libraries(ViewerLib PRIVATE ${XCB_LIBRARIES})
		target_compile_definitions(ViewerLib PRIVATE VK_USE_PLATFORM_XCB_KHR=1)
	endif()

	if(Wayland_FOUND)
		target_include_directories(ViewerLib PRIVATE ${Wayland_INCLUDE_DIRS})
		target_link_libraries(ViewerLib PRIVATE ${Wayland_LIBRARIES})
		target_compile_definitions(ViewerLib PRIVATE VK_USE_PLATFORM_WAYLAND_KHR=1)
	endif()
endif()
