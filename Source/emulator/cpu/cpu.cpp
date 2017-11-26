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
            return (1 << 15) & value;
        }

        inline byte GetByteMSB(const byte value)
        {
            return (1 << 7) & value;
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
                    ExecuteADD(instruction);
                    break;

                case Common::I_SUB:
                    ExecuteSUB(instruction);
                    break;

                case Common::I_BIT:
                    break;

                case Common::I_BITB:
                    break;

                case Common::I_BIC:
                    ExecuteBIC(instruction);
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
                    ExecuteXOR(instruction);
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
                    ExecuteCLRB(instruction);
                    break;

                case Common::I_COM:
                    break;

                case Common::I_COMB:
                    break;

                case Common::I_INC:
                    ExecuteINC(instruction);
                    break;

                case Common::I_INCB:
                    ExecuteINCB(instruction);
                    break;

                case Common::I_DEC:
                    break;

                case Common::I_DECB:
                    break;

                case Common::I_NEG:
                    ExecuteNEG(instruction);
                    break;

                case Common::I_NEGB:
                    ExecuteNEGB(instruction);
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
                    ExecuteROR(instruction);
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
                    ExecuteADC(instruction);
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

            void ExecuteADD(const Common::DoubleOperandInstruction& instruction)
            {
                const word src = GetSourceAddress(instruction.Source, false);
                const word dst = GetSourceAddress(instruction.Destination, false);
                const word srcValue = ReadWord(src);
                const word dstValue = ReadWord(dst);

                const word result = dstValue + srcValue;
                SetWord(dst, result);

                const byte overflowBit = result < dstValue ? 1 : 0;
                const byte carryBit = overflowBit;
                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);

                RegistersManager.SetFlag(RegistersManagement::Carry, carryBit);
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);

                RegistersManager.IncPC();
            }

            void ExecuteSUB(const Common::DoubleOperandInstruction& instruction)
            {
                const word src = GetSourceAddress(instruction.Source, false);
                const word dst = GetSourceAddress(instruction.Destination, false);
                const word srcValue = ReadWord(src);
                const word dstValue = ReadWord(dst);

                const word result = dstValue - srcValue;
                SetWord(dst, result);

                const byte overflowBit = result < dstValue ? 1 : 0;
                const byte carryBit = srcValue > dstValue ? 1 : 0;
                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);

                RegistersManager.SetFlag(RegistersManagement::Carry, carryBit);
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);

                RegistersManager.IncPC();
            }

            void ExecuteBIC(const Common::DoubleOperandInstruction& instruction)
            {
                const word src = GetSourceAddress(instruction.Source, false);
                const word dst = GetSourceAddress(instruction.Destination, false);
                const word srcValue = ReadWord(src);
                const word dstValue = ReadWord(dst);

                const word result = dstValue | (~srcValue);
                SetWord(dst, result);

                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);
                const byte overflowBit = 0;
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);

                RegistersManager.IncPC();
            }

            void ExecuteXOR(const Common::OneAndHalfInstruction& instruction)
            {
                const auto regNumber = static_cast<RegistersManagement::Register>(instruction.Register);
                const word valueInRegister = RegistersManager.GetRegister(regNumber);
                const word dstAddress = GetSourceAddress(instruction.Destination, false);

                const word result = valueInRegister ^ dstAddress;
                SetWord(dstAddress, result);

                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);
                const byte overflowBit = 0;
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);

                RegistersManager.IncPC();
            }

            void ExecuteCLR(const Common::SingleOperandInstruction& instruction)
            {
                SetWord(GetSourceAddress(instruction.Destination, false), 0);
                RegistersManager.SetFlag(RegistersManagement::Carry, 0);
                RegistersManager.SetFlag(RegistersManagement::Overflow, 0);
                RegistersManager.SetFlag(RegistersManagement::Sign, 0);
                RegistersManager.SetFlag(RegistersManagement::Zero, 1);

                RegistersManager.IncPC();
            }

            void ExecuteCLRB(const Common::SingleOperandInstruction& instruction)
            {
                SetByte(GetSourceAddress(instruction.Destination, false), 0);
                RegistersManager.SetFlag(RegistersManagement::Carry, 0);
                RegistersManager.SetFlag(RegistersManagement::Overflow, 0);
                RegistersManager.SetFlag(RegistersManagement::Sign, 0);
                RegistersManager.SetFlag(RegistersManagement::Zero, 1);

                RegistersManager.IncPC();
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

                RegistersManager.IncPC();
            }

            void ExecuteINCB(const Common::SingleOperandInstruction& instruction)
            {
                const byte valueInRegister = ReadByte(GetSourceAddress(instruction.Destination, false));
                const byte result = valueInRegister + 1; //TODO: check if CF required in next byte

                SetByte(GetSourceAddress(instruction.Destination, false), result);

                const byte overflowBit = result < valueInRegister ? 1 : 0;
                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetByteMSB(result);
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);

                RegistersManager.IncPC();
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

                RegistersManager.IncPC();
            }

            void ExecuteNEGB(const Common::SingleOperandInstruction& instruction)
            {
                const word address = GetSourceAddress(instruction.Destination, false);
                const byte valueInRegister = ReadByte(address);
                const byte result = ~valueInRegister + 1;
                SetByte(address, result);

                const byte overflowBit = valueInRegister == 0100000 ? 1 : 0;
                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetByteMSB(result);
                const byte carryBit = result != 0 ? 1 : 0;
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);
                RegistersManager.SetFlag(RegistersManagement::Carry, carryBit);

                RegistersManager.IncPC();
            }

            void ExecuteASR(const Common::SingleOperandInstruction& instruction)
            {
                const word address = GetSourceAddress(instruction.Destination, false);
                const word valueInRegister = ReadWord(address);
                const word result = valueInRegister >> 1;
                SetWord(address, result);

                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);
                const byte carryBit = 01 & valueInRegister;
                const byte overflowBit = 01 & (carryBit | msb);
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);
                RegistersManager.SetFlag(RegistersManagement::Carry, carryBit);

                RegistersManager.IncPC();
            }

            void ExecuteROR(const Common::SingleOperandInstruction& instruction)
            {
                const word address = GetSourceAddress(instruction.Destination, false);
                const word valueInRegister = ReadWord(address);

                const byte newCarryBit = valueInRegister & 01;
                const byte oldCarryBit = RegistersManager.GetFlag(RegistersManagement::Carry);
                const word result = (valueInRegister >> 1) | (oldCarryBit << 15);

                SetWord(address, result);

                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);
                const byte overflowBit = 01 & (newCarryBit | msb);
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);
                RegistersManager.SetFlag(RegistersManagement::Carry, newCarryBit);

                RegistersManager.IncPC();
            }

            void ExecuteADC(const Common::SingleOperandInstruction& instruction)
            {
                const word address = GetSourceAddress(instruction.Destination, false);
                const word valueInRegister = ReadWord(address);
                const byte carryBit = RegistersManager.GetFlag(RegistersManagement::Carry);

                const word result = valueInRegister + carryBit;
                const byte overflowBit = result < valueInRegister ? 1 : 0;
                const byte zeroBit = result == 0 ? 1 : 0;
                const byte msb = GetWordMSB(result);
                RegistersManager.SetFlag(RegistersManagement::Overflow, overflowBit);
                RegistersManager.SetFlag(RegistersManagement::Zero, zeroBit);
                RegistersManager.SetFlag(RegistersManagement::Sign, msb);

                SetWord(address, result);
                RegistersManager.IncPC();
            }

            void SetByte(const word address, const byte value)
            {
                if (IsRegisterAddress(address))
                {
                    const RegistersManagement::Register regNumber = ConvertRegisterAddressToRegisterNumber(address);
                    const word valueInReguster = (RegistersManager.GetRegister(regNumber) & 0177000) | value;
                    RegistersManager.SetRegister(regNumber, valueInReguster);
                }
                else
                    Memory->setByteAt(address, value);
            }

            void SetWord(const word address, const word value)
            {
                if (IsRegisterAddress(address))
                    RegistersManager.SetRegister(ConvertRegisterAddressToRegisterNumber(address), value);
                else
                    Memory->setWordAt(address, value);
            }

            byte ReadByte(const word address)
            {
                if (IsRegisterAddress(address))
                {
                    const byte valueInRegister = static_cast<byte>(RegistersManager.GetRegister(ConvertRegisterAddressToRegisterNumber(address)));
                    return valueInRegister;
                }

                return Memory->getByteAt(address);
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
