cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXE simple_start)
project (${EXE})

add_executable(${EXE} simple_start/maincpp.cpp)

target_link_libraries(${EXE} emulator)
