cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(functional_simulator)

set(SOURCE_LIST functional_simulator.cpp
                functional_simulator.h)

include_directories(Common Utils)

add_subdirectory(Modules/Decoder)
add_subdirectory(Modules/Memory)
add_subdirectory(Modules/Register)

add_library(functional_simulator STATIC ${SOURCE_LIST})