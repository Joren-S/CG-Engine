cmake_minimum_required(VERSION 3.9)
project(Engine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-fstack-protector-all")
set(CMAKE_CXX_FLAGS "-g3")

add_executable(Engine engine.cc
        vector3d/vector3d.h vector3d/vector3d.cc
        l_parser/l_parser.h l_parser/l_parser.cc
        easy_image/easy_image.h easy_image/easy_image.cc
        ini_configuration/ini_configuration.h ini_configuration/ini_configuration.cc

        headers/types.h
        headers/input.h headers/2DLSystems.h headers/3DLineDrawings.h
        src/input.cpp src/2DLSystems.cpp src/3DLineDrawings.cpp headers/3DLSystems.h src/3DLSystems.cpp headers/2DLineDrawings.h src/2DLineDrawings.cpp)