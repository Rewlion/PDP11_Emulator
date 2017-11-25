#include "cpu.h"

#include <emulator/common/error.h>

#include <assert.h>
#include <fstream>

namespace EmulatorComponents
{
    namespace
    {

        inline byte GetWordMSB(const word value)
        {
            return (1 < 15) & value;
        }

        inline bool IsRegisterAddress(const word address)
        {
            if ((address & 0170007) != 0)
                return true;
            else
                return false;
        }

        inline byte GetAddressingMode(const byte reg)
        {
            return (reg & 070) >> 3;
        }

        inline RegistersManagement::Register ConvertRegisterAddressToRegisterNumber(const word address)
        {
            return RegistersManagement::Register(address & 07);
        }

        inline word ConvertRegisterNumberToAddress(const byte reg)
        {
            assert((reg & 0770) == 0);//check that addressing mode is Register

            return 0170000 | (reg & 07);
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
                throw Common::Error("Unknown instruction", Common::Critical);
            }

            void operator()(const Common::DoubleOperandInstruction& instruction)
            {
                switch (instruction.Meta.Type)
                {
                case Common::I_MOV:
                    ExecuteMOV(instruction);
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
                    ExecuteCLR(instruction);
                    break;

                case Common::I_CLRB:
                    break;

                case Common::I_COM:
                    break;

                case Common::I_COMB:
                    break;

                case Common::I_INC:
                    ExecuteINC(instruction);
                    break;

                case Common::I_INCB:
                    break;

                case Common::I_DEC:
                    break;

                case Common::I_DECB:
                    break;

                case Common::I_NEG:
                    ExecuteNEG(instruction);
                    break;

                case Common::I_NEGB:
                    break;

                case Common::I_TST:
                    break;

                case Common::I_TSTB:
                    break;

                case Common::I_ASR:
                    ExecuteASR(instruction);
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
            void ExecuteMOV(const Common::DoubleOperandInstruction& instruction)
            {
                const word sourceValue = ReadWord(GetSourceAddress(instruction.Source, false));
                SetWord(GetSourceAddress(instruction.Destination, false), sourceValue);

                RegistersManager.IncPC();
            }

            void ExecuteCLR(const Common::SingleOperandInstruction& instruction)
            {
                SetWord(GetSourceAddress(instruction.Destination, false), 0);
                RegistersManager.SetFlag(RegistersManagement::Carry, 0);
                RegistersManager.SetFlag(RegistersManagement::Overflow, 0);
                RegistersManager.SetFlag(RegistersManagement::Sign, 0);
                RegistersManager.SetFlag(RegistersManagement::Zero, 1);
            }

            void ExecuteINC(const Common::SingleOperandInstruction& instruction)
            {
                const word valueInRegister = ReadWord(GetSourceAddress(instruction.Destination, false));
                const word result = valueInRegister + 1;

                SetWord(GetSourceAddress(instruction.Destination, false), result);

                const byte overflowBit = result < valueInRegister ? 1 : 0;
                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);
            }

            void ExecuteNEG(const Common::SingleOperandInstruction& instruction)
            {
                const word address = GetSourceAddress(instruction.Destination, false);
                const word valueInRegister = ReadWord(address);
                const word result = ~valueInRegister + 1;
                SetWord(address, result);

                const byte overflowBit = valueInRegister == 0100000 ? 1 : 0;
                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);
                const byte carryBit = result != 0 ? 1 : 0;
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);
                RegistersManager.SetFlag(RegistersManagement::Carry, carryBit);
            }

            void ExecuteASR(const Common::SingleOperandInstruction& instruction)
            {
                const word address = GetSourceAddress(instruction.Destination, false);
                const word valueInRegister = ReadWord(address);
                const word result = valueInRegister > 1;
                SetWord(address, result);

                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);
                const byte carryBit = 01 & valueInRegister;
                const byte overflowBit = 01 & (carryBit | msb);
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);
                RegistersManager.SetFlag(RegistersManagement::Carry, carryBit);
            }

            void SetWord(const word address, const word value)
            {
                if (IsRegisterAddress(address))
                    RegistersManager.SetRegister(ConvertRegisterAddressToRegisterNumber(address), value);
                else
                    Memory->setWordAt(address, value);
            }

            word ReadWord(const word address)
            {
                if (IsRegisterAddress(address))
                {
                    const word valueInRegister = RegistersManager.GetRegister(ConvertRegisterAddressToRegisterNumber(address));
                    return valueInRegister;
                }

                return Memory->getWordAt(address);
            }

            // Get a source's address accounting an addressing mode.
            // Returns register address(0170000-0170007) if dst - register.
            word GetSourceAddress(const byte reg, [[maybe_unused]] const bool isByteOperation)
            {
                const byte addressingMode = GetAddressingMode(reg);
                const RegistersManagement::Register registerNumber = GetRegisterNumber(reg);
                const word valueInRegister = RegistersManager.GetRegister(registerNumber);

                switch (addressingMode)
                {
                case MemoryManagement::Register:
                    return ConvertRegisterNumberToAddress(registerNumber);

                case MemoryManagement::RegisterDeferred:
                {
                    const word address = RegistersManager.GetRegister(registerNumber);
                    return address;
                }

                case MemoryManagement::Autodecrement:
                {
                    const word subtrahend = isByteOperation ? sizeof(byte) : sizeof(word);
                    RegistersManager.SetRegister(registerNumber, valueInRegister - subtrahend);

                    return ConvertRegisterNumberToAddress(registerNumber);
                }

                case MemoryManagement::AutodecrementDeferred:
                {
                    const word subtrahend = sizeof(word);
                    RegistersManager.SetRegister(registerNumber, valueInRegister - subtrahend);

                    return valueInRegister;
                }

                case MemoryManagement::Autoincrement:
                {
                    const word addend = isByteOperation ? sizeof(byte) : sizeof(word);
                    RegistersManager.SetRegister(registerNumber, valueInRegister + addend);

                    return ConvertRegisterNumberToAddress(registerNumber);
                }

                case MemoryManagement::AutoincrementDeferred:
                {
                    const word addend = sizeof(word);
                    RegistersManager.SetRegister(registerNumber, valueInRegister + addend);

                    return valueInRegister;
                }

                case MemoryManagement::Index:
                    assert(!"not implemented");
                    break;

                case MemoryManagement::IndexDeferred:
                    assert(!"not implemented");
                    break;
                }
                assert(!"unsupported addressing type");
                return -1; //to stfu compiler's warning
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
