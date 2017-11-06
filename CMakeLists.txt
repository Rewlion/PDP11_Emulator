cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXE SimpleProgram_littleEndian)
project (${EXE})

include_directories(Source)

add_executable(${EXE} Test/SimpleProgram_littleEndian/maincpp.cpp)
file(COPY Test/SimpleProgram_littleEndian/program.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(Source/functional_simulator)

target_link_libraries(${EXE} decoder registers memory functional_simulator)