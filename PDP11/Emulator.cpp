#include "Emulator.h"
#include "Common/Exceptions/Error.h"

#include "Memory/DirectMemoryRegion.h"
#include "Memory/MemoryRegionInformation.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

namespace PDP11
{
    Emulator::Emulator()
        : CPU(&Bus)
        , IsAbleToRun(false)
        , RAM(nullptr)
        , VRAM(nullptr)
        , ROM(nullptr)
        , IO(nullptr)
    {
        InitializeUnibus();
    }

    void Emulator::InitializeUnibus()
    {
        RAM = new DirectMemoryRegion(GetRAMBegining(), GetRAMSize());
        VRAM = new DirectMemoryRegion(GetVRAMBegining(), GetVRAMSize());
        ROM = new DirectMemoryRegion(GetROMBegining(), GetROMSize());
        Registers = new DirectMemoryRegion(GetRegistersBegining(), GetRegistersSize());

        Bus.AddMemoryRegion(RAM);
        Bus.AddMemoryRegion(VRAM);
        Bus.AddMemoryRegion(ROM);
        Bus.AddMemoryRegion(Registers);
    }

    void Emulator::UploadProgramToROMFromFile(const std::string& path)
    {
        std::vector<Word> program = ReadProgram(path);
        UploadProgramToROM(std::move(program));
        CPU.Reset();
    }

    std::vector<Word> Emulator::ReadProgram(const std::string& path) const
    {
        std::ifstream file{ path };
        CHECK(file.is_open(), "Can't read a program from the file : Unable to open the file.");

        std::vector<Word> program;
        std::string line;
        while (file.eof() == false)
        {
            std::getline(file, line);
            const Word instruction = std::strtol(line.c_str(), nullptr, 8);
            program.push_back(instruction);
        }

        return program;
    }

    void Emulator::UploadProgramToROM(std::vector<Word>&& program)
    {
        Word ROMAddress = GetROMBegining();
        for (Word instruction : program)
        {
            ROM->Write(ROMAddress, instruction);
            ROMAddress += sizeof(Word);
        }
    }

    void Emulator::Step()
    {
        CPU.Step();
    }

    void Emulator::Run()
    {
        IsAbleToRun = true;
        while (IsAbleToRun)
        {
            try
            {
                Step();
            }
            catch (...)
            {
                IsAbleToRun = false;
            }
            
        }
    }

    void Emulator::Stop()
    {
        IsAbleToRun = false;
        
    }

    RegistersInformation Emulator::GetRegisters() const
    {
        RegistersInformation info;
        info.R0 = Registers->Read(GetRegisterAddress(Register::R0));
        info.R1 = Registers->Read(GetRegisterAddress(Register::R1));
        info.R2 = Registers->Read(GetRegisterAddress(Register::R2));
        info.R3 = Registers->Read(GetRegisterAddress(Register::R3));
        info.R4 = Registers->Read(GetRegisterAddress(Register::R4));
        info.R5 = Registers->Read(GetRegisterAddress(Register::R5));
        info.R6 = Registers->Read(GetRegisterAddress(Register::R6));
        info.R7 = Registers->Read(GetRegisterAddress(Register::R7));

        return info;
    }

    RawRegion Emulator::CopyROM() const
    {
        auto* rom = dynamic_cast<DirectMemoryRegion*>(ROM);
        CHECK(rom != nullptr, "can't copy ROM.");

        RawRegion raw = rom->CopyMemory();
        CHECK(raw.Memory != nullptr, "can't copy ROM.");

        return raw;
    }
}