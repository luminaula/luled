cmake_minimum_required(VERSION 3.26)

project(luled)

enable_language(C CXX ISPC)
enable_testing()

find_package(SPIRV-Tools)
find_package(nv-codec-headers)
find_package(SDL2)
find_package(glfw3)
find_package(ffmpeg)
find_package(OpenSSL)
find_package(glad)

set(CMAKE_CXX_STANDARD 20)

if(APPLE)
    include_directories(/Library/Framework/SDL2.framework)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib)
add_subdirectory(app)