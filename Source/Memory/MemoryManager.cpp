#include "MemoryManager.h"

#include <limits>

namespace
{
    static dword memorySize = 1024 * 64;
}

namespace PDP11Emulator::MemoryManagement
{
    MemoryManager::MemoryManager() {
        memory_ = new byte [memorySize];
    }

    MemoryManager::~MemoryManager() {
        delete[] memory_;
    }

    byte MemoryManager::getByteAt(word address) const {
        byte* mem = memory_ + address;

        return *mem;
    }


    word MemoryManager::getWordAt(word address) const {
        byte* mem = memory_ + address;

        return *(reinterpret_cast<word*>(mem));
    }

}