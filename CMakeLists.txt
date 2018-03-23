cmake_minimum_required(VERSION 3.9)
project(Engine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-fstack-protector-all")
set(CMAKE_CXX_FLAGS "-g3")

add_executable(Engine engine.cc
        easy_image/easy_image.h easy_image/easy_image.cc
        ini_configuration/ini_configuration.h ini_configuration/ini_configuration.cc
        headers/input.h
        src/input.cpp)