#pragma once

#include <functional_simulator/Common/types.h>

#include <assert.h>

namespace RegistersManagement
{
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
}