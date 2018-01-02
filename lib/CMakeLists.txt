set(LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private_include")

file(GLOB_RECURSE LIB_HEADER_FILES "${LIB_INCLUDE_DIR}/VulkanTraining/*.h")
file(GLOB_RECURSE LIB_PRIVATE_HEADER_FILES "${LIB_PRIVATE_INCLUDE_DIR}/private/*.h")

file(GLOB_RECURSE LIB_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(VulkanTrainingEngine SHARED ${LIB_HEADER_FILES} ${LIB_PRIVATE_HEADER_FILES} ${LIB_SOURCE_FILES})

target_link_libraries(VulkanTrainingEngine PUBLIC ${Boost_LIBRARIES})
target_link_libraries(VulkanTrainingEngine PRIVATE ${Vulkan_LIBRARIES} ${GLFW_LIBRARIES} ${Assimp_LIBRARIES} ${FBX_LIBRARIES})

target_include_directories(VulkanTrainingEngine PUBLIC ${LIB_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
target_include_directories(VulkanTrainingEngine PRIVATE ${LIB_PRIVATE_INCLUDE_DIR} ${Vulkan_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${Assimp_INCLUDE_DIRS} ${FBX_INCLUDE_DIRS})
