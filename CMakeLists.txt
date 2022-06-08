cmake_minimum_required(VERSION 3.0)
project(rhDiff)
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")
set(RH_DIFF_LIB "${CMAKE_CURRENT_BINARY_DIR}/rhDiff")
set(RH_DIFF_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/rhDiff/include")

enable_testing()

add_subdirectory(rhDiff)
add_subdirectory (tests)


