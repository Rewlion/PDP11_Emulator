#pragma once

#include <emulator/common/instruction.h>
#include <emulator/common/types.h>
#include <emulator/cpu/decoder.h>
#include <emulator/cpu/RegisterManager.h>
#include <emulator/memory/MemoryManager.h>

#include <string>
#include <memory>

namespace EmulatorComponents
{
    class Cpu
    {
    public:
        Cpu();
        void Run();
    private:
        void Execute(const Common::Instruction& instruction);
    private:
        MemoryManagement::MemoryManager Memory;
        Decoding::Decoder Decoder;
        RegistersManagement::RegisterManager RegistersManager;

        bool IsExecutionOver;
    };
}
