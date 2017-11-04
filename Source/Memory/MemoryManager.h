#pragma once

#include <Common/types.h>

namespace MemoryManagement {

    class MemoryManager {
    public:
        MemoryManager();
        ~MemoryManager();

        byte getByteAt(word address) const;
        word getWordAt(word address) const;

    private:
        byte* memory_;
    };

}