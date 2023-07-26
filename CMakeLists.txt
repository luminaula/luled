cmake_minimum_required(VERSION 3.26)

project(luled)

enable_language(C CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(app)