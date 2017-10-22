cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(decoder)

set(SOURCE_LIST decoder.cpp
                decoder.h
                utils.h
                ../Common/types.h
                ../Common/instruction.h)

add_library(decoder STATIC ${SOURCE_LIST})