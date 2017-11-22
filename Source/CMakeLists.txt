cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT emulator)
project (${PROJECT})

set(EMULATOR_SOURCE_LIST emulator/emulator.cpp 
                         emulator/emulator.h)

set(COMMON_SOURCE_LIST  emulator/common/instruction.h
                        emulator/common/types.h )


set(CPU_SOURCE_LIST emulator/cpu/cpu.cpp
                    emulator/cpu/cpu.h
                    emulator/cpu/decoder.cpp
                    emulator/cpu/decoder.h
                    emulator/cpu/RegisterManager.h)

set(MEMORY_SOURCE_LIST  emulator/memory/MemoryManager.cpp
                        emulator/memory/MemoryManager.h)

source_group(emulator FILES ${EMULATOR_SOURCE_LIST})
source_group(emulator\\common FILES ${COMMON_SOURCE_LIST})
source_group(emulator\\cpu FILES ${CPU_SOURCE_LIST})
source_group(emulator\\memory FILES ${MEMORY_SOURCE_LIST})

add_library(${PROJECT} ${EMULATOR_SOURCE_LIST} ${COMMON_SOURCE_LIST} ${CPU_SOURCE_LIST} ${MEMORY_SOURCE_LIST} )