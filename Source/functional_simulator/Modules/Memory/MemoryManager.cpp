#include "MemoryManager.h"

#include <limits>

namespace
{
    constexpr dword getSimulatedMachineMemorySize() {return 1024 * 64;}
}

namespace MemoryManagement
{
    MemoryManager::MemoryManager()
        : memory_(new byte[getSimulatedMachineMemorySize()])
    {
    }

    MemoryManager::~MemoryManager() {
        delete[] memory_;
    }

    byte MemoryManager::getByteAt(const word address) const {
        const byte* mem = memory_ + address;

        return *mem;
    }


    word MemoryManager::getWordAt(const word address) const {
        byte* mem = memory_ + address;

        return *(reinterpret_cast<word*>(mem));
    }

}