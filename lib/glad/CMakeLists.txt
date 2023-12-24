project(glad)

include(FetchContent)
set(FETCHCONTENT_QUIET off)
set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Missing description." FORCE)

message(STATUS "Downloading ${PROJECT_NAME} using CMake's FetchContent")

FetchContent_Declare(
	${PROJECT_NAME}
	GIT_REPOSITORY	https://github.com/Dav1dde/glad.git
	GIT_TAG			v2.0.4
	GIT_SHALLOW		TRUE
	SOURCE_SUBDIR	cmake
)

FetchContent_MakeAvailable(${PROJECT_NAME})

glad_add_library(${PROJECT_NAME} STATIC API gl:core=4.5 LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-build/${TARGET})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}-build/include)
