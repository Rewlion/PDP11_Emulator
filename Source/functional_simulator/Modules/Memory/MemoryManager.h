#pragma once

#include <functional_simulator/Common/types.h>

namespace MemoryManagement {

    class MemoryManager {
    public:
        MemoryManager();
        ~MemoryManager();

        byte getByteAt(word address) const;
        word getWordAt(word address) const;
        void setByteAt(const word relativeAddress, const byte value) const;
        void setWordAt(const word relativeAddress, const word value) const;
    private:
        byte* memory_;
    };

}