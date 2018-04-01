cmake_minimum_required(VERSION 3.9)
project(barray)

set(CMAKE_CXX_STANDARD 11)

add_executable(barray main.cpp barray.h barray.hpp straight.hpp bezier_2.hpp bezier_3.hpp catmull-rom.hpp)