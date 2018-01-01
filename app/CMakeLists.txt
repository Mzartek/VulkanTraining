file(GLOB_RECURSE APP_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE APP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(VulkanTraining ${APP_HEADER_FILES} ${APP_SOURCE_FILES})

target_link_libraries(VulkanTraining PRIVATE VulkanTrainingEngine)
