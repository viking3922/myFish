cmake_minimum_required(VERSION 3.28)
project(myfish)

set(CMAKE_CXX_STANDARD 20)

add_executable(myfish main.cpp
        Hex.cpp
        Hex.h
)

add_executable(my_test_fish test.cpp
        Hex.cpp
        Hex.h
)