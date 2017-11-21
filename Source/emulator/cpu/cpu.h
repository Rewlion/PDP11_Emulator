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
        explicit Cpu(const std::string fileWithProgram);
        Cpu();

        void LoadProgram(const std::string fileWithProgram);
        void Run();

    private:
        void LoadNewContext(const int size);
        void Execute(const Common::Instruction& instruction);
    private:
        MemoryManagement::MemoryManager Memory;
        Decoding::Decoder Decoder;
        RegistersManagement::RegisterManager RegistersManager;

        std::unique_ptr<word[]> Program;
        qword CurrentInstructionsNumber;
        qword CurrentInstruction;
        bool IsExecutionOver;
    };
}