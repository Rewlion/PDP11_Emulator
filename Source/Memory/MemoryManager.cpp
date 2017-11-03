#include "MemoryManager.h"

#include <limits>

namespace
{
    static uint32 memorySize = 1024 * 64;
}

namespace PDP11Emulator::MemoryManagement
{
    MemoryManager::MemoryManager() {
        memory_ = new byte [memorySize];
    }

    MemoryManager::~MemoryManager() {
        delete[] memory_;
    }

    byte MemoryManager::getByteAt(uint16 address) const {
        byte* mem = memory_ + address;

        return *mem;
    }


    word MemoryManager::getWordAt(uint16 address) const {
        byte* mem = memory_ + address;

        return *(reinterpret_cast<word*>(mem));
    }

}