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

    void MemoryManager::setByteAt(const word relativeAddress, const byte value) const
    {
        byte* const address = memory_ + relativeAddress;
        *address = value;
    }

    void MemoryManager::setWordAt(const word relativeAddress, const word value) const
    {
        byte* const address = memory_ + relativeAddress;
        *(reinterpret_cast<word*>(address)) = value;
    }

}