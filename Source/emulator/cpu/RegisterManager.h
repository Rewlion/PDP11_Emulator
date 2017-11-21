#pragma once

#include <emulator/common/types.h>

#include <array>
#include <assert.h>

namespace EmulatorComponents::RegistersManagement
{
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

    enum Register
    {
        R1 = 0,
        R2,
        R3,
        R4,
        R5,
        R6,
        R7
    };

    enum Flag
    {
        Carry = 0,
        Overflow,
        Zero,
        Sign,
        Trap,
        InterruptPriority
    };

    constexpr int GetRegistersNumber()
    {
        return 7;
    }

    class RegisterManager
    {
    public:
        
        inline word GetPC()
        {
            return GetRegister(R7);
        }

        inline void SetPC(const word value)
        {
            SetRegister(R7, value);
        }

        inline void SetRegister(Register reg, word value)
        {
            Registers[reg] = value;
        }

        inline word GetRegister(Register reg) const
        {
            return Registers[reg];
        }

        inline void SetFlag(Flag flag, byte value)
        {
            if (flag != InterruptPriority)
                SetBit(FlagRegister, flag, value);
            else
                SetInterruptFlag(FlagRegister, value);
        }

        inline byte GetFlag(Flag flag)
        {
            if (flag != InterruptPriority)
                return GetBit(FlagRegister, flag);
            else
                return GetInterruptFlag(FlagRegister);
        }

    private:
        std::array<dword, GetRegistersNumber()> Registers;
        byte FlagRegister;
    };
}