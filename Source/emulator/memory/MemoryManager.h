#pragma once

#include <emulator/common/types.h>

#include <string>

namespace EmulatorComponents::MemoryManagement {

    constexpr word getRAMSize() { return word(1024 * 16); }
    constexpr word getVRAMSize(){ return word(1024 * 16); }
    constexpr word getROMSize() { return word(1024 * 16); }
    constexpr word getIOSize()  { return word(1024 * 16); }
    constexpr word getSimulatedMachineMemorySize() { return word(1024 * 64); }
    constexpr word getROMBegining() { return getRAMSize() + getVRAMSize(); }

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

        void loadProgram(const std::string& fileLocation);
        inline qword getLoadedProgramSize() const
        {
            return programSize;
        }

        inline byte* getProgramBegin() const
        {
            return memory_ + getROMBegining();
        }

        inline word getFirstInstruction() const
        {
            return getWordAt(getROMBegining());
        }

        byte getByteAt(word address) const;
        word getWordAt(word address) const;
        void setByteAt(const word relativeAddress, const byte value) const;
        void setWordAt(const word relativeAddress, const word value) const;
    private:
        byte* memory_;
        qword programSize;;
    };
}
