#pragma once

#include <Common/types.h>

namespace PDP11Emulator::MemoryManagement {

    class MemoryManager {
    public:
        MemoryManager() = default;
        ~MemoryManager();

        byte getByteAt(word address) const;
        word getWordAt(word address) const;

    private:
        byte* memory_;
    };

}