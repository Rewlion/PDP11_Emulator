#pragma once

#include "../Common/Types.h"

constexpr Word GetSimulatedMachineMemorySize() { return 1024 * 64; }

constexpr Word GetRAMSize()                    { return 1024 * 16; }
constexpr Word GetVRAMSize()                   { return 1024 * 16; }
constexpr Word GetROMSize()                    { return 1024 * 16; }
constexpr Word GetRegistersSize()              { return 8 * 2; }
constexpr Word GetIOSize()                     { return 1024 * 16 - GetRegistersSize(); }

constexpr Word GetRAMBegining()                { return 0; }
constexpr Word GetVRAMBegining()               { return GetRAMSize(); }
constexpr Word GetROMBegining()                { return GetVRAMBegining() + GetVRAMSize(); }
constexpr Word GetIOBegining()                 { return GetROMBegining() + GetROMSize(); }
constexpr Word GetRegistersBegining()          { return GetIOBegining() + GetIOSize(); }

enum class MemoryRegionType
{
    RAM,
    VRAM,
    ROM,
    IO,
    Registers
};

enum class Register : Address
{
    R0 = 0,
    R1 = 1,
    R2 = 2,
    R3 = 3,
    R4 = 4, 
    R5 = 5,
    R6 = 6, SP = 6,
    R7 = 7, PC = 7,
};

struct RegistersInformation
{
    Word R0;
    Word R1;
    Word R2;
    Word R3;
    Word R4;
    Word R5;
    Word R6;
    Word R7;
};

constexpr Address GetPCAddress()
{
    return GetRegistersBegining() + static_cast<Address>(Register::PC) * sizeof(Word);
}

constexpr Address GetRegisterAddress(const Register reg)
{
    return GetRegistersBegining() + static_cast<Address>(reg) * sizeof(Word);
}