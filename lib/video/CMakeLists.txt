project(video)

file(GLOB sources src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${sources})

target_link_libraries(${PROJECT_NAME} PUBLIC 
	vk-bootstrap::vk-bootstrap 
	vulkan-memory-allocator::vulkan-memory-allocator
	ffmpeg::ffmpeg
	Vulkan::Loader
	vulkan-headers::vulkan-headers
	glad::glad
	glfw)

target_include_directories(${PROJECT_NAME} PUBLIC inc)