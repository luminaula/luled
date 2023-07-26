project(display)

find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC inc)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2)