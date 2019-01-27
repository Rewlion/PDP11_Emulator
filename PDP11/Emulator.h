#pragma once

#include "Memory/MemoryRegionInformation.h"

#include <vector>
#include <string>
#include <optional>

class CPU;
class Unibus;
class MemoryRegion;

class Emulator
{
public:
    Emulator();

    void                 Initialize();
    bool                 UploadProgramToROMFromFile(const std::string& path);
    bool                 Step();
    void                 Run();
    void                 Stop();
    RegistersInformation GetRegisters() const;
    Word                 GetRegister(const Register reg) const;
    RawRegion            CopyROM() const;
    RawRegion            CopyVRAM() const;
    std::optional<Word>  ReadMemory(const Address at) const;

private:
    void InitializeUnibus();

    std::vector<Word> ReadProgram(const std::string& path) const;
    void              UploadProgramToROM(std::vector<Word>&& program);

private:
    Unibus*       pBus;
    CPU*          pCPU;

	bool          IsAbleToRun;

	MemoryRegion* pRAM;
	MemoryRegion* pVRAM;
	MemoryRegion* pROM;
	MemoryRegion* pIO;
	MemoryRegion* pRegisters;
};