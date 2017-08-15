set(LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB LIB_HEADER_FILES "${LIB_INCLUDE_DIR}/VulkanTraining/*.h")
file(GLOB LIB_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(VulkanTrainingEngine SHARED ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES})
target_link_libraries(VulkanTrainingEngine PRIVATE ${Vulkan_LIBRARIES} ${GLFW_LIBRARIES})
target_include_directories(VulkanTrainingEngine PUBLIC ${LIB_INCLUDE_DIR} ${Vulkan_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
target_compile_definitions(VulkanTrainingEngine PRIVATE ENGINE_EXPORT)
