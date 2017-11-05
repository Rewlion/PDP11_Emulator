#pragma once

#include "utils.h"

#include <functional_simulator/Common/types.h>

#include <array>

namespace RegistersManagement
{
    class RegisterManager
    {
    public:
        inline void SetRegister(Register reg, word value);
        inline word GetRegister(Register reg) const;
        inline void SetFlag(Flag flag, byte value);
        inline byte GetFlag(Flag flag);
    private:
        std::array<dword, GetRegistersNumber()> Registers;
        byte FlagRegister;
    };
}