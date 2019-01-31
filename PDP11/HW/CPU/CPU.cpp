#include "CPU.h"
#include "Decoder.h"
#include "../../Common/Logs/Logs.h"
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
    catch (Common::Error& e)
    {
        Logger->Log(LogType::Critical, std::string_view(e.what()));
        DecPC();
        throw;
    }
}

void CPU::Reset()
{
    Bus->Write(GetRegisterAddress(Register::R0), 0);
    Bus->Write(GetRegisterAddress(Register::R1), 0);
    Bus->Write(GetRegisterAddress(Register::R2), 0);
    Bus->Write(GetRegisterAddress(Register::R3), 0);
    Bus->Write(GetRegisterAddress(Register::R4), 0);
    Bus->Write(GetRegisterAddress(Register::R5), 0);
    Bus->Write(GetRegisterAddress(Register::R6), GetRAMBegining() + GetRAMSize()-sizeof(Word));
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