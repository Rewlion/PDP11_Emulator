#pragma once

#include "../Common/Types.h"
#include "../HW/CPU/FlagRegister.h"

constexpr size_t GetSimulatedMachineMemorySize() { return 1024 * 64; }

constexpr Word GetRAMSize()                      { return 1024 * 16; }
constexpr Word GetVRAMSize()                     { return 1024 * 16; }
constexpr Word GetROMSize()                      { return 1024 * 16; }
constexpr Word GetRegistersSize()                { return 8 * 2; }
constexpr Word GetIOSize()                       { return 1024 * 16 - GetRegistersSize(); }

constexpr Word GetRAMBegining()                  { return 0; }
constexpr Word GetVRAMBegining()                 { return GetRAMSize(); }
constexpr Word GetROMBegining()                  { return GetVRAMBegining() + GetVRAMSize(); }
constexpr Word GetIOBegining()                   { return GetROMBegining() + GetROMSize(); }
constexpr Word GetRegistersBegining()            { return GetIOBegining() + GetIOSize(); }

constexpr size_t GetRegistersNumber()            { return 8; }

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

struct RawRegion
{
    Byte* Memory        = nullptr;
    Word  AllocatedSize = 0;
    Word  MemoryBegin   = 0;
};

struct RegistersInformation
{
    Word         Values[GetRegistersNumber()];
    FlagRegister Flags;
};

inline const char* GetRegisterName(const unsigned int reg)
{
    switch (reg)
    {
    case 0:  return "R0";
    case 1:  return "R1";
    case 2:  return "R2";
    case 3:  return "R3";
    case 4:  return "R4";
    case 5:  return "R5";
    case 6:  return "R6";
    case 7:  return "R7";
    default: return "UNKNOWN";
    }
}

constexpr Address GetSPAddress()
{
    return GetRegistersBegining() + static_cast<Address>(Register::SP) * sizeof(Word);
}

constexpr Address GetPCAddress()
{
    return GetRegistersBegining() + static_cast<Address>(Register::PC) * sizeof(Word);
}

constexpr Address GetRegisterAddress(const Register reg)
{
    return GetRegistersBegining() + static_cast<Address>(reg) * sizeof(Word);
}
