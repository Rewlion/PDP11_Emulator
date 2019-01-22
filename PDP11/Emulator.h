#pragma once

#include "HW/CPU/CPU.h"
#include "Memory/Unibus.h"
#include "Memory/MemoryRegionInformation.h"
#include "Memory/RawRegion.h"

#include <vector>
#include <string>

class Emulator
{
public:
    Emulator();

    void                 UploadProgramToROMFromFile(const std::string& path);
    void                 Step();
    void                 Run();
    void                 Stop();
    RegistersInformation GetRegisters() const;
    RawRegion            CopyROM() const;

private:
    void InitializeUnibus();

    std::vector<Word> ReadProgram(const std::string& path) const;
    void              UploadProgramToROM(std::vector<Word>&& program);

private:
    Unibus        Bus;
    CPU           CPU;

	bool          IsAbleToRun;

	MemoryRegion* RAM;
	MemoryRegion* VRAM;
	MemoryRegion* ROM;
	MemoryRegion* IO;
	MemoryRegion* Registers;
};