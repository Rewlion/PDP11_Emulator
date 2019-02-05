#pragma once

#include "../../Common/Types.h"

struct FlagRegister
{
    union
    {
        Byte Raw;
        struct
        {
            Byte Carry             : 1;
            Byte Overflow          : 1;
            Byte Zero              : 1;
            Byte Sign              : 1;
            Byte Trap              : 1;
            Byte InterruptPriority : 3;
        };
    };
};
