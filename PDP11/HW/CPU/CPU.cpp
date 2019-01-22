#include "CPU.h"
#include "Decoder.h"
#include "../../Memory/Unibus.h"
#include "../../Memory/MemoryRegionInformation.h"

CPU::CPU(Unibus* bus)
    : Bus(bus)
    , Executer(FlagRegister, Bus)
{
}

void CPU::Step()
{
    const Address     instructionAddress = Bus->Read(GetPCAddress());
    IncPC();
    const Word        rawInstruction = Bus->Read(instructionAddress);
    const Instruction decodedInstruction = Decoder.Decode(rawInstruction);

    try
    {
        std::visit(Executer, decodedInstruction);
    }
    catch (...)
    {
        DecPC();
        throw;
    }
}

void CPU::Reset()
{
    Bus->Write(GetPCAddress(), GetROMBegining());
}

void CPU::IncPC()
{
    const Word pc = Bus->Read(GetPCAddress());
    Bus->Write(GetPCAddress(), pc + sizeof(Word));
}

void CPU::DecPC()
{
    const Word pc = Bus->Read(GetPCAddress());
    Bus->Write(GetPCAddress(), pc - sizeof(Word));
}