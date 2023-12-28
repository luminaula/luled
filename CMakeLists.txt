cmake_minimum_required(VERSION 3.26)

project(luled)

enable_language(C CXX ISPC)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV)
find_package(SPIRV-Tools)
find_package(SPIRV-Headers)
find_package(nv-codec-headers)
find_package(SDL2)
find_package(glfw3)
find_package(vk-bootstrap)
find_package(vulkan-memory-allocator)
find_package(ffmpeg)
find_package(VulkanLoader)
find_package(VulkanHeaders)
find_package(glad)
find_package(Threads)

if(APPLE)
    include_directories(/Library/Framework/SDL2.framework)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib)
add_subdirectory(app)