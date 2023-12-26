project(video)

file(GLOB sources src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${sources})

target_link_libraries(${PROJECT_NAME} PUBLIC ffmpeg::ffmpeg volk::volk vk-bootstrap::vk-bootstrap vulkan-memory-allocator::vulkan-memory-allocator)

target_include_directories(${PROJECT_NAME} PUBLIC inc)