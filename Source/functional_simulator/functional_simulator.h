#pragma once

#include <functional_simulator/Common/instruction.h>
#include <functional_simulator/Common/types.h>
#include <functional_simulator/Modules/Decoder/decoder.h>
#include <functional_simulator/Modules/Memory/MemoryManager.h>
#include <functional_simulator/Modules/Register/RegisterManager.h>

#include <string>
#include <memory>

namespace Runtime
{
    class Simulator
    {
    public:
        explicit Simulator(const std::string fileWithProgram);
        Simulator();

        void LoadProgram(const std::string fileWithProgram);
        void Run();

    private:
        void LoadNewContext(const int size);
        void Execute(const Common::Instruction& instruction);
    private:
        MemoryManagement::MemoryManager MemoryManager;
        Decoding::Decoder Decoder;
        RegistersManagement::RegisterManager RegistersManager;

        std::unique_ptr<word[]> Program;
        qword CurrentInstructionsNumber;
        qword CurrentInstruction;
    };
}