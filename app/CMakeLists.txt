file(GLOB_RECURSE APP_UI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui")
file(GLOB_RECURSE APP_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE APP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(ViewerApp
	${APP_UI_FILES}
	${APP_HEADER_FILES}
	${APP_SOURCE_FILES})

target_link_libraries(ViewerApp
	ViewerLib
	Qt5::Core
	Qt5::Widgets
	${CMAKE_THREAD_LIBS_INIT})

set(COPY_SHADERS_COMMAND
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/lib/shaders
	$<TARGET_FILE_DIR:ViewerApp>/shaders)

add_custom_target(CopyShaders ${COPY_SHADERS_COMMAND})

add_custom_command(TARGET ViewerApp POST_BUILD ${COPY_SHADERS_COMMAND})
