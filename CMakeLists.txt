cmake_minimum_required(VERSION 3.15)
project(prog)

set(CMAKE_CXX_STANDARD 11)

add_library(naiveVin naiveVin.cpp)
add_library(parallelVin parallelVin.cpp)

add_executable(prog main.cpp Matrix.cpp)
target_link_libraries(prog naiveVin parallelVin pthread)