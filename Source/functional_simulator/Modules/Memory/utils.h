#pragma once

namespace MemoryManagement
{
    enum AddressingMode
    {
        Register              = 0,
        RegisterDeferred      = 1,
        Autoincrement         = 2,
        AutoincrementDeferred = 3,
        Autodecrement         = 4,
        AutodecrementDeferred = 5,
        Index                 = 6,
        IndexDeferred         = 7
    };
}