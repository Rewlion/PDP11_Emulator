#pragma once

#include "../../Common/Exceptions/Error.h"
#include "../../Common/Types.h"

#include <array>

class FlagRegister
{
public:
    enum class FlagType : int
    {
        Carry = 0,
        Overflow,
        Zero,
        Sign,
        Trap,
        InterruptPriority,
        TYPES_NUMBER,
    };

public:
    inline void SetFlag(const FlagType flag, const Byte value);
    inline bool GetFlag(const FlagType flag) const;

private:
    std::array<bool, static_cast<size_t>(FlagType::TYPES_NUMBER)> Flags;
};

void FlagRegister::SetFlag(const FlagType flag, const Byte value)
{
    CHECK((value == 0) || (value == 1), "wrong value for flag.");
    Flags[static_cast<int>(flag)] = value;
}

bool FlagRegister::GetFlag(const FlagType flag) const
{
    return Flags[static_cast<int>(flag)];
}