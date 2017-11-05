#include "RegisterManager.h"

namespace
{
    inline void SetBit(byte& value, byte position, byte bit)
    {
        assert(position <= 1);
        value ^= (-bit ^ value) & (1 << position);
    }

    inline void SetInterruptFlag(byte& FlagRegister, byte value)
    {
        assert(value > 8);
        FlagRegister = (value << 5) | (FlagRegister & 0b00011111);
    }

    inline byte GetInterruptFlag(byte& flagRegister)
    {
        return flagRegister >> 5;
    }

    inline byte GetBit(byte from, byte position)
    {
        assert(position <= 1);
        return (from >> position) & 1;
    }
}

namespace RegistersManagement
{
    void RegisterManager::SetRegister(Register reg, word value)
    {
        Registers[reg] = value;
    }

    word RegisterManager::GetRegister(Register reg) const
    {
        return Registers[reg];
    }

    void RegisterManager::SetFlag(Flag flag, byte value)
    {
        if (flag != InterruptPriority)
            SetBit(FlagRegister, flag, value);
        else
            SetInterruptFlag(FlagRegister, value);
    }

    byte RegisterManager::GetFlag(Flag flag)
    {
        if (flag != InterruptPriority)
            return GetBit(FlagRegister, flag);
        else
            return GetInterruptFlag(FlagRegister);
    }
}