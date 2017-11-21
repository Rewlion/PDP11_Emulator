cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXE SimpleProgram_littleEndian)
project (${EXE})

include_directories(Source)

add_executable(${EXE} SimpleProgram_littleEndian/maincpp.cpp)
file(COPY SimpleProgram_littleEndian/program.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${EXE} cpu)