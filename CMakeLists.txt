cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (test_functional_simulator)

include_directories(Source)

add_executable(main Test/maincpp.cpp) #remove after pipeline implemented

add_subdirectory(Source/functional_simulator)

target_link_libraries(main decoder memory functional_simulator)