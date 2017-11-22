#pragma once

#include <emulator/common/instruction.h>
#include <emulator/common/types.h>
#include <emulator/cpu/decoder.h>
#include <emulator/cpu/RegisterManager.h>
#include <emulator/memory/MemoryManager.h>

#include <string>
#include <memory>

typedef std::shared_ptr<EmulatorComponents::MemoryManagement::MemoryManager> MemoryManagerPtr;

namespace EmulatorComponents
{
    class Cpu
    {
    public:
        explicit Cpu(MemoryManagerPtr memory);
        void Run();
    private:
        void Execute(const Common::Instruction& instruction);
    private:
        MemoryManagerPtr Memory;
        Decoding::Decoder Decoder;
        RegistersManagement::RegisterManager RegistersManager;

        bool IsExecutionOver;
    };
}