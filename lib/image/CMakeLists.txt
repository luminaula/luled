project(image)

file(GLOB_RECURSE srcs *.cpp)

add_library(${PROJECT_NAME} ${srcs})

target_include_directories(${PROJECT_NAME} PUBLIC inc)