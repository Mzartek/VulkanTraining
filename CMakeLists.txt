cmake_minimum_required(VERSION 3.6)

project(Viewer)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

find_package(Boost REQUIRED filesystem program_options)
find_package(Vulkan REQUIRED)
find_package(GLM REQUIRED)
find_package(Assimp REQUIRED)
find_package(FBX REQUIRED)
find_package(GLSLANG REQUIRED)
find_package(Qt5Core)
find_package(Qt5Widgets)

if(UNIX)
	find_package(ECM REQUIRED NO_MODULE)
	set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ECM_FIND_MODULE_DIR}")
	
	find_package(X11)
	find_package(XCB)
	find_package(Wayland)
endif()

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++11 -pedantic")
endif()

add_subdirectory(lib)
add_subdirectory(app)
