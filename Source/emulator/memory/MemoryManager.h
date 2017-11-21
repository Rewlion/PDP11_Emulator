#pragma once

#include <emulator/common/types.h>

namespace EmulatorComponents::MemoryManagement {

    enum AddressingMode
    {
        Register = 0,
        RegisterDeferred = 1,
        Autoincrement = 2,
        AutoincrementDeferred = 3,
        Autodecrement = 4,
        AutodecrementDeferred = 5,
        Index = 6,
        IndexDeferred = 7
    };

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