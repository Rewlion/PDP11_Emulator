cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (Main)

include_directories(Source)
include_directories(Source/thirdparty/Qt) #dirty hack for includes in Qt lib.

add_subdirectory(Source)
add_subdirectory(Test)
