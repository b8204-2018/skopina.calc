cmake_minimum_required(VERSION 3.13)
project(calc)

set(CMAKE_CXX_STANDARD 17)

add_executable(calc main.cpp src/calc.cpp src/calc.h)