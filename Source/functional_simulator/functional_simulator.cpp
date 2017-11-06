#include "functional_simulator.h"

#include <fstream>
#include <exception>

namespace
{
    inline word GetPC(const RegistersManagement::RegisterManager& registerManager)
    {
        return registerManager.GetRegister(RegistersManagement::R7);
    }

    inline void SetPC(RegistersManagement::RegisterManager& registerManager, const word value)
    {
        registerManager.SetRegister(RegistersManagement::R7, value);
    }

    class InstructionExecutor
    {
    public:
        InstructionExecutor(RegistersManagement::RegisterManager& registerManager, MemoryManagement::MemoryManager& memoryManager)
            : MemoryManager(memoryManager)
            , RegistersManager(registerManager)
        {
        }

        void operator()(const Common::UnknownInstruction& instruction)
        {

        }

        void operator()(const Common::DoubleOperandInstruction& instruction)
        {
        }

        void operator()(const Common::OneAndHalfInstruction& instruction)
        {
        }

        void operator()(const Common::SingleOperandInstruction& instruction)
        {
            
        }

        void operator()(const Common::BranchInstruction& instruction)
        {
        }

    private:
        MemoryManagement::MemoryManager& MemoryManager;
        RegistersManagement::RegisterManager& RegistersManager;
    };
}

namespace Runtime
{
    Simulator::Simulator(const std::string fileWithProgram)
        : CurrentInstructionsNumber(0)
        , CurrentInstruction(0)
    {
        LoadProgram(fileWithProgram);
    }

    Simulator::Simulator()
        : CurrentInstructionsNumber(0)
        , CurrentInstruction(0)
    {
    }

    void Simulator::LoadProgram(const std::string fileWithProgram)
    {
        std::ifstream file(fileWithProgram, std::ifstream::ate | std::ifstream::binary);
        if (!file.is_open())
            throw std::runtime_error("unable to open the file with program");

        const auto size = file.tellg();
        if (size % sizeof(word))
            throw std::runtime_error("size of loaded program is not multiples of word");

        LoadNewContext(size);

        file.seekg(0, file.beg);
        file.read(reinterpret_cast<char*>(Program.get()), size);

        SetPC(RegistersManager, Program[0]);
    }

    void Simulator::Run()
    {
        for (int i = 0; i < CurrentInstructionsNumber; ++i)
        {
            const word rawInstruction = GetPC(RegistersManager);
            const Common::Instruction instruction = Decoder.Decode(rawInstruction);
            Execute(instruction);
        }
    }

    void Simulator::LoadNewContext(const int sizeInBytes)
    {
        CurrentInstructionsNumber = sizeInBytes / sizeof(word);
        CurrentInstruction = 0;
        Program.reset(new word[sizeInBytes /2]);
    }

    void Simulator::Execute(const Common::Instruction& instruction)
    {
        InstructionExecutor executor(RegistersManager, MemoryManager);
        std::visit(executor, instruction);
    }
}
