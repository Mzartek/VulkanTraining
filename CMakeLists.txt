cmake_minimum_required(VERSION 3.6)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()

find_package(GLFW REQUIRED)
find_package(Vulkan REQUIRED)
find_package(GLM REQUIRED)

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(VulkanTest ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(VulkanTest ${Vulkan_LIBRARIES} ${GLFW_LIBRARIES})
