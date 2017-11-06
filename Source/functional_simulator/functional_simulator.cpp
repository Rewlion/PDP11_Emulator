#include "functional_simulator.h"

#include <functional_simulator\Modules\Memory\utils.h>

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

    inline byte GetAddressingMode(const byte reg)
    {
        return (reg & 070) >> 3;
    }

    inline RegistersManagement::Register GetRegisterNumber(const byte reg)
    {
        return RegistersManagement::Register(reg & 07);
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
        word GetSourceFromRegister(const byte reg, const bool isByteOperation)
        {
            const byte mode = GetAddressingMode(reg);
            const RegistersManagement::Register regNumber = GetRegisterNumber(reg);
            const word valueInRegister = RegistersManager.GetRegister(regNumber);

            switch (mode)
            {
            case MemoryManagement::Register:
                return RegistersManager.GetRegister(regNumber);

            case MemoryManagement::RegisterDeferred:
            {
                const word address = RegistersManager.GetRegister(regNumber);
                const word source = MemoryManager.getWordAt(address);
                return source;
            }

            case MemoryManagement::Autodecrement:
            {
                if (isByteOperation)
                {
                    RegistersManager.SetRegister(regNumber, valueInRegister - sizeof(byte));
                    const word source = MemoryManager.getWordAt(valueInRegister);
                    return source;
                }
                else
                {
                    RegistersManager.SetRegister(regNumber, valueInRegister - sizeof(word));
                    const word source = MemoryManager.getWordAt(valueInRegister);
                    return source;
                }
            }

            case MemoryManagement::AutodecrementDeferred:
            {
                if (isByteOperation)
                {
                    RegistersManager.SetRegister(regNumber, valueInRegister - sizeof(byte));
                    const word source = MemoryManager.getWordAt(valueInRegister);
                    return source;
                }
                else
                {
                    RegistersManager.SetRegister(regNumber, valueInRegister - sizeof(word));
                    const word source = MemoryManager.getWordAt(valueInRegister);
                    return source;
                }
            }

            case MemoryManagement::Autoincrement:
            {
                if (isByteOperation)
                {
                    const word source = MemoryManager.getWordAt(valueInRegister);
                    RegistersManager.SetRegister(regNumber, valueInRegister + sizeof(byte));
                    return source;
                }
                else
                {
                    const word source = MemoryManager.getWordAt(valueInRegister);
                    RegistersManager.SetRegister(regNumber, valueInRegister + sizeof(word));
                    return source;
                }
            }

            case MemoryManagement::AutoincrementDeferred:
            {
                const word sourceAddress = MemoryManager.getWordAt(valueInRegister);
                const word source = MemoryManager.getWordAt(sourceAddress);
                RegistersManager.SetRegister(regNumber, valueInRegister + sizeof(word));
                return source;
            }

            case MemoryManagement::Index:
                assert(!"not implemented");
                break;

            case MemoryManagement::IndexDeferred:
                assert(!"not implemented");
                break;
            }

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
        , IsExecutionOver(true)
    {
        LoadProgram(fileWithProgram);
    }

    Simulator::Simulator()
        : CurrentInstructionsNumber(0)
        , CurrentInstruction(0)
        , IsExecutionOver(true)
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
        while(!IsExecutionOver)
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
        IsExecutionOver = false;
        Program.reset(new word[sizeInBytes /2]);
    }

    void Simulator::Execute(const Common::Instruction& instruction)
    {
        InstructionExecutor executor(RegistersManager, MemoryManager);
        std::visit(executor, instruction);
    }
}
