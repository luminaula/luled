project(ledarray)

file(GLOB_RECURSE SOURCES *.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC inc)