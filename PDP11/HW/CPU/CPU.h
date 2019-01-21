#pragma once

#include "../../Common/Instruction.h"
#include "../../Common/Types.h"
#include "Decoder.h"
#include "FlagRegister.h"
#include "Executer.h"

class Unibus;

namespace PDP11
{
    class CPU
    {
    public:
        CPU(Unibus* bus);

        void Step();
        void Reset();

    private:
        void IncPC();
        void DecPC();
    private:
        Unibus* Bus;
        FlagRegister FlagRegister;
        Decoder Decoder;
        Executer Executer;
    };
}