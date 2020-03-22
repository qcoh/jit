cmake_minimum_required(VERSION 3.14)

project(jit)

include(FetchContent)
include(CTest)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2
	GIT_TAG v2.11.3
)
FetchContent_MakeAvailable(Catch2)

set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(include/)
add_subdirectory(tests/)
