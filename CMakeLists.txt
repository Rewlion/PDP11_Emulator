cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (pdp11_emulator)

include_directories(Source)

add_executable(main Test/maincpp.cpp) #remove after pipeline implemented

add_subdirectory(Source/Decoder)
add_subdirectory(Source/Memory)

target_link_libraries(main decoder)
target_link_libraries(main memory)