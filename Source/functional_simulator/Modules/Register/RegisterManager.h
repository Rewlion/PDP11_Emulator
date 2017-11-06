#pragma once

#include "utils.h"

#include <functional_simulator/Common/types.h>

#include <array>

namespace RegistersManagement
{
    class RegisterManager
    {
    public:
        void SetRegister(Register reg, word value);
        word GetRegister(Register reg) const;
        void SetFlag(Flag flag, byte value);
        byte GetFlag(Flag flag);
    private:
        std::array<dword, GetRegistersNumber()> Registers;
        byte FlagRegister;
    };
}