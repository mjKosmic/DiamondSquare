cmake_minimum_required(VERSION 3.10)
project(DiamondSquare)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(DiamondSquare
        DiamondSquare.cpp
        DiamondSquare.hpp
        main.cpp)
