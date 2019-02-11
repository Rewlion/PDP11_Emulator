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
    std::optional<InterruptVector> v = PIC.GetInterrupt(FlagRegister.InterruptPriority);
    if (v.has_value())
        ProcessInterrupt(v.value());

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
    Bus->Write(GetRegisterAddress(Register::R6), GetRAMBegining() + GetRAMSize());
    Bus->Write(GetPCAddress(), GetROMBegining());

    FlagRegister.Raw = 0;
    FlagRegister.InterruptPriority = 7;

    PIC.Reset();
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

void CPU::ProcessInterrupt(const InterruptVector v)
{
    const Word pc = Bus->Read(GetPCAddress());
    PushWord(FlagRegister.Raw);
    PushWord(pc);

    const Word newPC = Bus->Read(v.Handler);
    const Byte newPS = static_cast<Byte>(Bus->Read(v.Handler + sizeof(Word)));

    Bus->Write(GetPCAddress(), newPC);
    FlagRegister.Raw = newPS;
}

void CPU::PushWord(const Word value)
{
    const Word currentHead = Bus->Read(GetSPAddress());
    const Word newHead = currentHead - sizeof(Word);
    Bus->Write(GetSPAddress(), newHead);
    Bus->Write(newHead, value);
}

Word CPU::PopWord()
{
    const Word currentHead = Bus->Read(GetSPAddress());
    const Word headValue = Bus->Read(currentHead);
    const Word newHead = currentHead + sizeof(Word);
    Bus->Write(GetSPAddress(), newHead);

    return headValue;
}
