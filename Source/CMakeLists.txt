cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (CMAKE_PREFIX_PATH "kiko")
if (${CMAKE_PREFIX_PATH} STREQUAL "kiko")
  message(FATAL_ERROR "please specify the path to the folder with QT libs")
endif()

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)

set(PROJECT emulator)
project (${PROJECT})

set(EMULATOR_SOURCE_LIST emulator/emulator.cpp 
                         emulator/emulator.h)

set(COMMON_SOURCE_LIST  emulator/common/instruction.h
                        emulator/common/types.h 
                        emulator/common/error.cpp
                        emulator/common/error.h
                        emulator/common/bitoperations.h)

set(CPU_SOURCE_LIST emulator/cpu/cpu.cpp
                    emulator/cpu/cpu.h
                    emulator/cpu/decoder.cpp
                    emulator/cpu/decoder.h
                    emulator/cpu/RegisterManager.h)

set(MEMORY_SOURCE_LIST  emulator/memory/MemoryManager.cpp
                        emulator/memory/MemoryManager.h)

set(GUI_SOURCE_LIST emulator/gui/gui.cpp
                    emulator/gui/gui.h
                    emulator/gui/registerslistmodel.cpp
                    emulator/gui/registerslistmodel.h
                    emulator/gui/flagslistmodel.cpp
                    emulator/gui/flagslistmodel.h
                    emulator/gui/memorylistmodel.cpp
                    emulator/gui/memorylistmodel.h)

source_group(emulator FILES ${EMULATOR_SOURCE_LIST})
source_group(emulator\\common FILES ${COMMON_SOURCE_LIST})
source_group(emulator\\cpu FILES ${CPU_SOURCE_LIST})
source_group(emulator\\memory FILES ${MEMORY_SOURCE_LIST})
source_group(emulator\\gui FILES ${GUI_SOURCE_LIST})

add_library(${PROJECT} ${EMULATOR_SOURCE_LIST} 
                       ${COMMON_SOURCE_LIST} 
                       ${CPU_SOURCE_LIST} 
                       ${MEMORY_SOURCE_LIST} 
                       ${GUI_SOURCE_LIST})

target_link_libraries(${PROJECT} Qt5::Core Qt5::Quick Qt5::Widgets)