
project(syclib)


if(CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
	set(WITH_SYCL ON)
	add_compile_definitions(WITH_SYCL)
endif()

include(userOffloadArch.txt OPTIONAL)
if(NOT DEFINED OFFLOAD_ARCH)
	set(OFFLOAD_ARCH --offload-arch=sm_75) # Lumin GTX 2080
endif()



file(GLOB sources src/*.cpp)

file(GLOB ispc_sources src/*.ispc)
file(GLOB cuda_sources src/*.cu)

if(WITH_SYCL)
	file(GLOB sycl_sources sycl/*.cpp)
	list(APPEND sources ${sycl_sources})
	
	find_package(IntelSYCL REQUIRED)
	
	set_property(TARGET IntelSYCL::SYCL_CXX PROPERTY
	INTERFACE_COMPILE_OPTIONS -fsycl -fsycl-targets=nvptx64-nvidia-cuda -Xsycl-target-backend=nvptx64-nvidia-cuda ${OFFLOAD_ARCH})

	set_property(TARGET IntelSYCL::SYCL_CXX PROPERTY
	INTERFACE_LINK_OPTIONS -fsycl -fsycl-targets=nvptx64-nvidia-cuda -Xsycl-target-backend=nvptx64-nvidia-cuda ${OFFLOAD_ARCH})
endif()

add_library(${PROJECT_NAME} SHARED ${sources} ${ispc_sources} ${cuda_sources})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if(WITH_SYCL)
	add_sycl_to_target(TARGET ${PROJECT_NAME} SOURCES ${sycl_sources})
	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sycl)
endif()
