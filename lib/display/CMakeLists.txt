project(display)


find_package(glad REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2main glad::glad Threads::Threads)
target_include_directories(${PROJECT_NAME} PUBLIC inc ${glad_INCLUDE_DIRS})
