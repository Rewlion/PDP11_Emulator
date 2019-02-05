#include "Emulator.h"
#include "Common/Exceptions/Error.h"
#include "Common/Logs/Logs.h"
#include "HW/CPU/CPU.h"
#include "Memory/Unibus.h"
#include "Memory/DirectMemoryRegion.h"
#include "Memory/MemoryRegionInformation.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

Emulator::Emulator()
    : pBus(nullptr)
    , pCPU(nullptr)
    , IsAbleToRun(false)
    , pRAM(nullptr)
    , pVRAM(nullptr)
    , pROM(nullptr)
    , pIO(nullptr)
    , pRegisters(nullptr)
{
}

void Emulator::Initialize()
{
    pBus = new Unibus;
    pCPU = new CPU(pBus);
    InitializeUnibus();

    Logger->Log(LogType::Log, "Emulator is ready.\nLoad a program to the ROM.");
}

void Emulator::InitializeUnibus()
{
    pRAM = new DirectMemoryRegion(GetRAMBegining(), GetRAMSize());
    pBus->AddMemoryRegion(pRAM);
    std::string msg = std::string("Added RAM to unibus. Begins:") + std::to_string(GetRAMBegining()) + std::string(" size:") + std::to_string(GetRAMSize());
    Logger->Log(LogType::Log, msg);

    pVRAM = new DirectMemoryRegion(GetVRAMBegining(), GetVRAMSize());
    pBus->AddMemoryRegion(pVRAM);
    msg = std::string("Added VRAM to unibus. Begins:") + std::to_string(GetVRAMBegining()) + std::string(" size:") + std::to_string(GetVRAMSize());
    Logger->Log(LogType::Log, msg);

    pROM = new DirectMemoryRegion(GetROMBegining(), GetROMSize());
    pBus->AddMemoryRegion(pROM);
    msg = std::string("Added ROM to unibus. Begins:") + std::to_string(GetROMBegining()) + std::string(" size:") + std::to_string(GetROMSize());
    Logger->Log(LogType::Log, msg);

    pRegisters = new DirectMemoryRegion(GetRegistersBegining(), GetRegistersSize());
    pBus->AddMemoryRegion(pRegisters);
    msg = std::string("Added Registers to unibus. Begins:") + std::to_string(GetRegistersBegining()) + std::string(" size:") + std::to_string(GetRegistersSize());
    Logger->Log(LogType::Log, msg);
}

bool Emulator::UploadProgramToROMFromFile(const std::string& path)
{
    std::vector<Word> program = ReadProgram(path);
    if (program.empty() == false)
    {
        UploadProgramToROM(std::move(program));
        pCPU->Reset();

        return true;
    }
    else
        return false;
    
}

std::vector<Word> Emulator::ReadProgram(const std::string& path) const
{
    std::ifstream file{ path };
    if (file.is_open() == false)
    {
        Logger->Log(LogType::Critical, "Can't read a program from the file : Unable to open the file.");
        return std::vector<Word>{};
    }

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
        pROM->Write(ROMAddress, instruction);
        ROMAddress += sizeof(Word);
    }
}

bool Emulator::Step()
{
    try
    {
        pCPU->Step();
        return true;
    }
    catch (...)
    {
        return false;
    }
}

void Emulator::Run()
{
    IsAbleToRun = true;
    while (IsAbleToRun)
    {
        if (Step() == false)
            IsAbleToRun = false;
    }
}

void Emulator::Stop()
{
    IsAbleToRun = false;

}

RegistersInformation Emulator::GetRegisters() const
{
    RegistersInformation info;

    info.Values[0] = pRegisters->Read(GetRegisterAddress(Register::R0));
    info.Values[1] = pRegisters->Read(GetRegisterAddress(Register::R1));
    info.Values[2] = pRegisters->Read(GetRegisterAddress(Register::R2));
    info.Values[3] = pRegisters->Read(GetRegisterAddress(Register::R3));
    info.Values[4] = pRegisters->Read(GetRegisterAddress(Register::R4));
    info.Values[5] = pRegisters->Read(GetRegisterAddress(Register::R5));
    info.Values[6] = pRegisters->Read(GetRegisterAddress(Register::R6));
    info.Values[7] = pRegisters->Read(GetRegisterAddress(Register::R7));

    info.Flags = pCPU->GetFlagRegister();

    return info;
}

Word Emulator::GetRegister(const Register reg) const
{
    const Word value = pRegisters->Read(GetRegisterAddress(reg));
    return value;
}

RawRegion Emulator::CopyROM() const
{
    auto* rom = dynamic_cast<DirectMemoryRegion*>(pROM);
    CHECK(rom != nullptr, "can't copy ROM.");

    RawRegion raw = rom->CopyMemory();
    CHECK(raw.Memory != nullptr, "can't copy ROM.");

    return raw;
}

RawRegion Emulator::CopyVRAM() const
{
    auto* vram = dynamic_cast<DirectMemoryRegion*>(pVRAM);
    CHECK(vram != nullptr, "can't copy ROM.");

    RawRegion raw = vram->CopyMemory();
    CHECK(raw.Memory != nullptr, "can't copy ROM.");

    return raw;
}

std::optional<Word> Emulator::ReadMemory(const Address at) const
{
    try
    {
        const Word value = pBus->Read(at);
        return value;
    }
    catch (Common::Error& e)
    {
        Logger->Log(LogType::Critical, e.what());
        return std::nullopt;
    }
}