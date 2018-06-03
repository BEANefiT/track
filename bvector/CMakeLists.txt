cmake_minimum_required(VERSION 3.10)
project(bvector)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

add_executable(bvector main.cpp ../bexcept/bexcept.hpp bvector.hpp)