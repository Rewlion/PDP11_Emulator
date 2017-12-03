#pragma once

#include <emulator/cpu/cpu.h>

#include <memory>
#include <string>

namespace PDP11
{
    typedef std::shared_ptr<EmulatorComponents::MemoryManagement::MemoryManager> MemoryManagerPtr;

    class Emulator
    {
    public:
        Emulator();

    private:
        EmulatorComponents::Cpu Cpu;
    };
}
