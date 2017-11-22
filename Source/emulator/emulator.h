#pragma once

#include <emulator/cpu/cpu.h>
#include <emulator/memory/MemoryManager.h>

#include <memory>
#include <string>

namespace PDP11
{
    typedef std::shared_ptr<EmulatorComponents::MemoryManagement::MemoryManager> MemoryManagerPtr;

    class Emulator
    {
    public:
        Emulator();
        
        inline void Emulator::LoadProgram(std::string fileLocation)
        {
            Memory->loadProgram(fileLocation);
        }
    private:
        MemoryManagerPtr Memory;
        EmulatorComponents::Cpu Cpu;
    };
}
