#include "emulator.h"

namespace PDP11
{
    Emulator::Emulator()
        : Memory(new EmulatorComponents::MemoryManagement::MemoryManager())
        , Cpu(Memory)
    {
    }
}