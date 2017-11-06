cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(memory)

include_directories(../../../)

set(SOURCE_LIST MemoryManager.cpp
                MemoryManager.h
                utils.h)

add_library(memory STATIC ${SOURCE_LIST})