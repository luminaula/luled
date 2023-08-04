cmake_minimum_required(VERSION 3.26)

project(luled)

enable_language(C CXX ISPC)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

if(APPLE)
    include_directories(/Library/Framework/SDL2.framework)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib)
add_subdirectory(app)