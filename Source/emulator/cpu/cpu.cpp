#include "cpu.h"

#include <assert.h>
#include <fstream>
#include <exception>

namespace EmulatorComponents
{
    namespace
    {
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
            InstructionExecutor(RegistersManagement::RegisterManager& registerManager, MemoryManagerPtr memoryManager)
                : Memory(memoryManager)
                , RegistersManager(registerManager)
            {
            }

            void operator()(const Common::UnknownInstruction& instruction)
            {

            }

            void operator()(const Common::DoubleOperandInstruction& instruction)
            {
                switch (instruction.Meta.Type)
                {
                case Common::I_MOV:
                    break;

                case Common::I_MOVB:
                    break;

                case Common::I_CMP:
                    break;

                case Common::I_CMPB:
                    break;

                case Common::I_ADD:
                    break;

                case Common::I_SUB:
                    break;

                case Common::I_BIT:
                    break;

                case Common::I_BITB:
                    break;

                case Common::I_BIC:
                    break;

                case Common::I_BICB:
                    break;

                case Common::I_BIS:
                    break;

                case Common::I_BISB:
                    break;

                }
            }

            void operator()(const Common::OneAndHalfInstruction& instruction)
            {
                switch (instruction.Meta.Type)
                {
                case Common::I_MUL:
                    break;

                case Common::I_DIV:
                    break;

                case Common::I_ASH:
                    break;

                case Common::I_ASHC:
                    break;

                case Common::I_XOR:
                    break;

                default:
                    assert(false);
                    break;

                }
            }

            void operator()(const Common::SingleOperandInstruction& instruction)
            {
                switch (instruction.Meta.Type)
                {
                case Common::I_CLR:
                    break;

                case Common::I_CLRB:
                    break;

                case Common::I_COM:
                    break;

                case Common::I_COMB:
                    break;

                case Common::I_INC:
                    break;

                case Common::I_INCB:
                    break;

                case Common::I_DEC:
                    break;

                case Common::I_DECB:
                    break;

                case Common::I_NEG:
                    break;

                case Common::I_NEGB:
                    break;

                case Common::I_TST:
                    break;

                case Common::I_TSTB:
                    break;

                case Common::I_ASR:
                    break;

                case Common::I_ASRB:
                    break;

                case Common::I_ASL:
                    break;

                case Common::I_ASLB:
                    break;

                case Common::I_ROR:
                    break;

                case Common::I_RORB:
                    break;

                case Common::I_ROL:
                    break;

                case Common::I_ROLB:
                    break;

                case Common::I_SWAB:
                    break;

                case Common::I_ADC:
                    break;

                case Common::I_ADCB:
                    break;

                case Common::I_SBC:
                    break;

                case Common::I_SBCB:
                    break;

                case Common::I_SXT:
                    break;

                default:
                    assert(false);
                    break;
                }
            }

            void operator()(const Common::BranchInstruction& instruction)
            {
                switch (instruction.Meta.Type)
                {
                case Common::I_BR:
                    break;

                case Common::I_BNE:
                    break;

                case Common::I_BEQ:
                    break;

                case Common::I_BPL:
                    break;

                case Common::I_BMI:
                    break;

                case Common::I_BVC:
                    break;

                case Common::I_BVS:
                    break;

                case Common::I_BCC:
                    break;

                case Common::I_BCS:
                    break;

                case Common::I_BGE:
                    break;

                case Common::I_BLT:
                    break;

                case Common::I_BGT:
                    break;

                case Common::I_BLE:
                    break;

                case Common::I_BHI:
                    break;

                case Common::I_BLOS:
                    break;

                case Common::I_BHIS:
                    break;

                case Common::I_BLO:
                    break;

                default:
                    assert(false);
                    break;
                }
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
                    const word source = Memory->getWordAt(address);
                    return source;
                }

                case MemoryManagement::Autodecrement:
                {
                    if (isByteOperation)
                    {
                        RegistersManager.SetRegister(regNumber, valueInRegister - sizeof(byte));
                        const word source = Memory->getWordAt(valueInRegister);
                        return source;
                    }
                    else
                    {
                        RegistersManager.SetRegister(regNumber, valueInRegister - sizeof(word));
                        const word source = Memory->getWordAt(valueInRegister);
                        return source;
                    }
                }

                case MemoryManagement::AutodecrementDeferred:
                {
                    if (isByteOperation)
                    {
                        RegistersManager.SetRegister(regNumber, valueInRegister - sizeof(byte));
                        const word source = Memory->getWordAt(valueInRegister);
                        return source;
                    }
                    else
                    {
                        RegistersManager.SetRegister(regNumber, valueInRegister - sizeof(word));
                        const word source = Memory->getWordAt(valueInRegister);
                        return source;
                    }
                }

                case MemoryManagement::Autoincrement:
                {
                    if (isByteOperation)
                    {
                        const word source = Memory->getWordAt(valueInRegister);
                        RegistersManager.SetRegister(regNumber, valueInRegister + sizeof(byte));
                        return source;
                    }
                    else
                    {
                        const word source = Memory->getWordAt(valueInRegister);
                        RegistersManager.SetRegister(regNumber, valueInRegister + sizeof(word));
                        return source;
                    }
                }

                case MemoryManagement::AutoincrementDeferred:
                {
                    const word sourceAddress = Memory->getWordAt(valueInRegister);
                    const word source = Memory->getWordAt(sourceAddress);
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
            MemoryManagerPtr Memory;
            RegistersManagement::RegisterManager& RegistersManager;
        };
    }

    Cpu::Cpu(MemoryManagerPtr memory)
        : Memory(memory)
        , IsExecutionOver(true)
    {
    }

    void Cpu::Run()
    {
        const word firstInstruction = Memory->getFirstInstruction();
        RegistersManager.SetPC(firstInstruction);

        while(!IsExecutionOver)
        {
            const word rawInstruction = RegistersManager.GetPC();
            const Common::Instruction instruction = Decoder.Decode(rawInstruction);
            Execute(instruction);
        }
    }

    void Cpu::Execute(const Common::Instruction& instruction)
    {
        InstructionExecutor executor(RegistersManager, Memory);
        std::visit(executor, instruction);
    }
}
