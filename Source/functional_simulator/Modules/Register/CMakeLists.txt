cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(register)

include_directories(../../../)

set(SOURCE_LIST RegisterManager.cpp
                RegisterManager.h)

add_library(register STATIC ${SOURCE_LIST})