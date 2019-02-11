#pragma once

#include "../../Common/Instruction.h"
#include "../../Common/Types.h"
#include "Decoder.h"
#include "FlagRegister.h"
#include "Executer.h"
#include "../PIC/PriorityInterruptController.h"
#include "../PIC/IRQ_Line.h"

class Unibus;

class CPU
{
public:
    CPU(Unibus* bus);

    void                        Step();
    void                        Reset();
    inline FlagRegister         GetFlagRegister();
    inline IRQ_Line             GetIRQLine(const unsigned int priority);

private:
    void                        IncPC();
    void                        DecPC();
    void                        PushWord(const Word value);
    Word                        PopWord();
    void                        ProcessInterrupt(const InterruptVector v);
private:
    Unibus*                     Bus;
    FlagRegister                FlagRegister;
    Decoder                     Decoder;
    Executer                    Executer;
    PriorityInterruptController PIC;
};

FlagRegister CPU::GetFlagRegister()
{
    return FlagRegister;
}

IRQ_Line CPU::GetIRQLine(const unsigned int priority)
{
    return PIC.GetIRQLine(priority);
}