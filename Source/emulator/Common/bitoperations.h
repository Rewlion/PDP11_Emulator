#pragma once

#include "types.h"
#include <assert.h>

namespace Common
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
        return (from >> position) & 1;
    }
}