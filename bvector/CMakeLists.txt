cmake_minimum_required(VERSION 3.10)
project(bvector)

set(CMAKE_CXX_STANDARD 11)

add_executable(bvector main.cpp ../bexcept/bexcept.hpp bvector.hpp)