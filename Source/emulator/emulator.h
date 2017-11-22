#pragma once

#include <emulator/cpu/cpu.h>
#include <emulator/memory/MemoryManager.h>

#include <memory>

namespace PDP11
{
    typedef std::shared_ptr<EmulatorComponents::MemoryManagement::MemoryManager> MemoryManagerPtr;

    class Emulator
    {
    public:
        Emulator();
    private:
        MemoryManagerPtr Memory;
        EmulatorComponents::Cpu Cpu;
    };
}