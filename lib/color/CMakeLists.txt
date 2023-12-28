project(color)

file(GLOB_RECURSE color_srcs *.cpp)

set(ISPC_HEADER_DIRECTORY ispc/include/color)

add_library(${PROJECT_NAME} SHARED ${color_srcs})

target_include_directories(${PROJECT_NAME} PUBLIC inc)

add_subdirectory(tests)