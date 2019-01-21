#include "Executer.h"
#include "../../Common/Exceptions/Error.h"
#include "../../Memory/Unibus.h"

#include <assert.h>

namespace PDP11
{
    namespace
    {
        
    }

    Executer::Executer(PDP11::FlagRegister& flagRegister, Unibus* bus)
        : FlagRegister(flagRegister)
        , Bus(bus)
    {
    }

    void Executer::operator()(const UnknownInstruction& instruction)
    {
        throw Common::Error("Unknown instruction", Common::Critical);
    }

    void Executer::operator()(const DoubleOperandInstruction& instruction)
    {
        switch (instruction.Meta.Type)
        {
        case InstructionType::I_MOV:
            ExecuteMOV(instruction);
            break;

        case InstructionType::I_MOVB:
            ExecuteMOVB(instruction);
            break;

        case InstructionType::I_CMP:
            break;

        case InstructionType::I_CMPB:
            break;

        case InstructionType::I_ADD:
            ExecuteADD(instruction);
            break;

        case InstructionType::I_SUB:
            ExecuteSUB(instruction);
            break;

        case InstructionType::I_BIT:
            break;

        case InstructionType::I_BITB:
            break;

        case InstructionType::I_BIC:
            ExecuteBIC(instruction);
            break;

        case InstructionType::I_BICB:
            ExecuteBICB(instruction);
            break;

        case InstructionType::I_BIS:
            break;

        case InstructionType::I_BISB:
            break;

        default:
            assert(false);
            break;
        }
    }

    void Executer::operator()(const OneAndHalfInstruction& instruction)
    {
        switch (instruction.Meta.Type)
        {
        case InstructionType::I_MUL:
            break;

        case InstructionType::I_DIV:
            break;

        case InstructionType::I_ASH:
            break;

        case InstructionType::I_ASHC:
            break;

        case InstructionType::I_XOR:
            ExecuteXOR(instruction);
            break;

        default:
            assert(false);
            break;

        }
    }

    void Executer::operator()(const SingleOperandInstruction& instruction)
    {
        switch (instruction.Meta.Type)
        {
        case InstructionType::I_CLR:
            ExecuteCLR(instruction);
            break;

        case InstructionType::I_CLRB:
            ExecuteCLRB(instruction);
            break;

        case InstructionType::I_COM:
            break;

        case InstructionType::I_COMB:
            break;

        case InstructionType::I_INC:
            ExecuteINC(instruction);
            break;

        case InstructionType::I_INCB:
            ExecuteINCB(instruction);
            break;

        case InstructionType::I_DEC:
            break;

        case InstructionType::I_DECB:
            break;

        case InstructionType::I_NEG:
            ExecuteNEG(instruction);
            break;

        case InstructionType::I_NEGB:
            ExecuteNEGB(instruction);
            break;

        case InstructionType::I_TST:
            break;

        case InstructionType::I_TSTB:
            break;

        case InstructionType::I_ASR:
            ExecuteASR(instruction);
            break;

        case InstructionType::I_ASRB:
            ExecuteASRB(instruction);
            break;

        case InstructionType::I_ASL:
            break;

        case InstructionType::I_ASLB:
            break;

        case InstructionType::I_ROR:
            ExecuteROR(instruction);
            break;

        case InstructionType::I_RORB:
            ExecuteRORB(instruction);
            break;

        case InstructionType::I_ROL:
            break;

        case InstructionType::I_ROLB:
            break;

        case InstructionType::I_SWAB:
            break;

        case InstructionType::I_ADC:
            ExecuteADC(instruction);
            break;

        case InstructionType::I_ADCB:
            ExecuteADCB(instruction);
            break;

        case InstructionType::I_SBC:
            break;

        case InstructionType::I_SBCB:
            break;

        case InstructionType::I_SXT:
            break;

        default:
            assert(false);
            break;
        }
    }

    void Executer::operator()(const BranchInstruction& instruction)
    {
        switch (instruction.Meta.Type)
        {
        case InstructionType::I_BR:
            break;

        case InstructionType::I_BNE:
            break;

        case InstructionType::I_BEQ:
            break;

        case InstructionType::I_BPL:
            break;

        case InstructionType::I_BMI:
            break;

        case InstructionType::I_BVC:
            break;

        case InstructionType::I_BVS:
            break;

        case InstructionType::I_BCC:
            break;

        case InstructionType::I_BCS:
            break;

        case InstructionType::I_BGE:
            break;

        case InstructionType::I_BLT:
            break;

        case InstructionType::I_BGT:
            break;

        case InstructionType::I_BLE:
            break;

        case InstructionType::I_BHI:
            break;

        case InstructionType::I_BLOS:
            break;

        case InstructionType::I_BHIS:
            break;

        case InstructionType::I_BLO:
            break;

        default:
            assert(false);
            break;
        }
    }

    void Executer::ExecuteMOV(const DoubleOperandInstruction& instruction)
    {
        const Word sourceValue = ReadWord(GetSourceAddress(instruction.Source, OperationSizeType::Word));

        WriteWord(GetSourceAddress(instruction.Destination, OperationSizeType::Word), sourceValue);
    }

    void Executer::ExecuteMOVB(const DoubleOperandInstruction& instruction)
    {
        const Byte sourceValue = ReadByte(GetSourceAddress(instruction.Source, OperationSizeType::Byte));

        WriteByte(GetSourceAddress(instruction.Destination, OperationSizeType::Byte), sourceValue);
    }

    void Executer::ExecuteADD(const DoubleOperandInstruction& instruction)
    {
        const Word src = GetSourceAddress(instruction.Source, OperationSizeType::Word);
        const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
        const Word srcValue = ReadWord(src);
        const Word dstValue = ReadWord(dst);

        const Word result = dstValue + srcValue;

        const Byte overflowBit = result < dstValue ? 1 : 0;
        const Byte carryBit = overflowBit;
        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);

        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, carryBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);

        WriteWord(dst, result);
    }

    void Executer::ExecuteSUB(const DoubleOperandInstruction& instruction)
    {
        const Word src = GetSourceAddress(instruction.Source, OperationSizeType::Word);
        const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
        const Word srcValue = ReadWord(src);
        const Word dstValue = ReadWord(dst);

        const Word result = dstValue - srcValue;

        const Byte overflowBit = result < dstValue ? 1 : 0;
        const Byte carryBit = srcValue > dstValue ? 1 : 0;
        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);

        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, carryBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);

        WriteWord(dst, result);
    }

    void Executer::ExecuteBIC(const DoubleOperandInstruction& instruction)
    {
        const Word src = GetSourceAddress(instruction.Source, OperationSizeType::Word);
        const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
        const Word srcValue = ReadWord(src);
        const Word dstValue = ReadWord(dst);

        const Word result = dstValue | (~srcValue);

        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);
        const Byte overflowBit = 0;

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);

        WriteWord(dst, result);
    }

    void Executer::ExecuteBICB(const DoubleOperandInstruction& instruction)
    {
        const Word src = GetSourceAddress(instruction.Source, OperationSizeType::Byte);
        const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Byte);
        const Byte srcValue = ReadByte(src);
        const Byte dstValue = ReadByte(dst);

        const Byte result = dstValue | (~srcValue);

        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetByteMSB(result);
        const Byte overflowBit = 0;

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);

        WriteByte(dst, result);
    }

    void Executer::ExecuteXOR(const OneAndHalfInstruction& instruction)
    {
        /*const Word regAddress = GetSourceAddress(instruction.Register, OperationSizeType::Word)
        const Word valueInRegister = ReadWord(regAddress);
        const Word dstAddress = GetSourceAddress(instruction.Destination, OperationSizeType::Word);

        const Word result = valueInRegister ^ dstAddress;
        WriteWord(dstAddress, result);

        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);
        const Byte overflowBit = 0;
        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        */
    }

    void Executer::ExecuteCLR(const SingleOperandInstruction& instruction)
    {
        WriteWord(GetSourceAddress(instruction.Destination, OperationSizeType::Word), 0);
        
        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, 0);
        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, 0);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, 0);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, 1);
    }

    void Executer::ExecuteCLRB(const SingleOperandInstruction& instruction)
    {
        WriteByte(GetSourceAddress(instruction.Destination, OperationSizeType::Byte), 0);
        
        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, 0);
        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, 0);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, 0);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, 1);
    }

    void Executer::ExecuteINC(const SingleOperandInstruction& instruction)
    {
        const Word valueInRegister = ReadWord(GetSourceAddress(instruction.Destination, OperationSizeType::Word));
        const Word result = valueInRegister + 1;

        const Byte overflowBit = result < valueInRegister ? 1 : 0;
        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);

        WriteWord(GetSourceAddress(instruction.Destination, OperationSizeType::Word), result);
    }

    void Executer::ExecuteINCB(const SingleOperandInstruction& instruction)
    {
        const Byte valueInRegister = ReadByte(GetSourceAddress(instruction.Destination, OperationSizeType::Byte));
        const Byte result = valueInRegister + 1; //TODO: check if CF required in next byte

        const Byte overflowBit = result < valueInRegister ? 1 : 0;
        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetByteMSB(result);

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);

        WriteByte(GetSourceAddress(instruction.Destination, OperationSizeType::Byte), result);
    }

    void Executer::ExecuteNEG(const SingleOperandInstruction& instruction)
    {
        const Word address = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
        const Word valueInRegister = ReadWord(address);
        const Word result = ~valueInRegister + 1;

        const Byte overflowBit = valueInRegister == 0100000 ? 1 : 0;
        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);
        const Byte carryBit = result != 0 ? 1 : 0;

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, carryBit);

        WriteWord(address, result);
    }

    void Executer::ExecuteNEGB(const SingleOperandInstruction& instruction)
    {
        const Word address = GetSourceAddress(instruction.Destination, OperationSizeType::Byte);
        const Byte valueInRegister = ReadByte(address);
        const Byte result = ~valueInRegister + 1;

        const Byte overflowBit = valueInRegister == 0100000 ? 1 : 0;
        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetByteMSB(result);
        const Byte carryBit = result != 0 ? 1 : 0;

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, carryBit);

        WriteByte(address, result);
    }

    void Executer::ExecuteASR(const SingleOperandInstruction& instruction)
    {
        const Word address = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
        const Word valueInRegister = ReadWord(address);
        const Word result = valueInRegister >> 1;

        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);
        const Byte carryBit = 01 & valueInRegister;
        const Byte overflowBit = 01 & (carryBit | msb);

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, carryBit);

        WriteWord(address, result);
    }

    void Executer::ExecuteASRB(const SingleOperandInstruction& instruction)
    {
        const Word address = GetSourceAddress(instruction.Destination, OperationSizeType::Byte);
        const Byte valueInRegister = ReadByte(address);
        const Byte result = valueInRegister >> 1;

        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetByteMSB(result);
        const Byte carryBit = 01 & valueInRegister;
        const Byte overflowBit = 01 & (carryBit | msb);

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, carryBit);

        WriteByte(address, result);
    }

    void Executer::ExecuteROR(const SingleOperandInstruction& instruction)
    {
        const Word address = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
        const Word valueInRegister = ReadWord(address);

        const Byte newCarryBit = valueInRegister & 01;
        const Byte oldCarryBit = FlagRegister.GetFlag(FlagRegister::FlagType::Carry);
        const Word result = (valueInRegister >> 1) | (oldCarryBit << 15);

        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);
        const Byte overflowBit = 01 & (newCarryBit | msb);

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, newCarryBit);

        WriteWord(address, result);
    }

    void Executer::ExecuteRORB(const SingleOperandInstruction& instruction)
    {
        const Word address = GetSourceAddress(instruction.Destination, OperationSizeType::Byte);
        const Byte valueInRegister = ReadByte(address);

        const Byte newCarryBit = valueInRegister & 01;
        const Byte oldCarryBit = FlagRegister.GetFlag(FlagRegister::FlagType::Carry);
        const Byte result = (valueInRegister >> 1) | (oldCarryBit << 7);

        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetByteMSB(result);
        const Byte overflowBit = 01 & (newCarryBit | msb);

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);
        FlagRegister.SetFlag(FlagRegister::FlagType::Carry, newCarryBit);

        WriteByte(address, result);
    }

    void Executer::ExecuteADC(const SingleOperandInstruction& instruction)
    {
        const Word address = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
        const Word valueInRegister = ReadWord(address);
        const Byte carryBit = FlagRegister.GetFlag(FlagRegister::FlagType::Carry);

        const Word result = valueInRegister + carryBit;
        const Byte overflowBit = result < valueInRegister ? 1 : 0;
        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetWordMSB(result);

        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);

        WriteWord(address, result);
    }

    void Executer::ExecuteADCB(const SingleOperandInstruction& instruction)
    {
        const Address address = GetSourceAddress(instruction.Destination, OperationSizeType::Byte);
        const Byte valueInRegister = ReadByte(address);
        const Byte carryBit = FlagRegister.GetFlag(FlagRegister::FlagType::Carry);

        const Byte result = valueInRegister + carryBit;
        const Byte overflowBit = result < valueInRegister ? 1 : 0;
        const Byte zeroBit = result == 0 ? 1 : 0;
        const Byte msb = GetByteMSB(result);
        
        FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, overflowBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Zero, zeroBit);
        FlagRegister.SetFlag(FlagRegister::FlagType::Sign, msb);

        WriteByte(address, result);
    }

    Executer::MemoryAddressingType Executer::GetAddressingMode(const Byte reg) const
    {
        int mode = (reg & 070) >> 3;
        switch (mode)
        {
            case static_cast<int>(MemoryAddressingType::Register) :
                return MemoryAddressingType::Register;

            case static_cast<int>(MemoryAddressingType::RegisterDeferred):
                return MemoryAddressingType::RegisterDeferred;

            case static_cast<int>(MemoryAddressingType::Autoincrement):
                return MemoryAddressingType::Autoincrement;

            case static_cast<int>(MemoryAddressingType::AutoincrementDeferred):
                return MemoryAddressingType::AutoincrementDeferred;

            case static_cast<int>(MemoryAddressingType::Index):
                return MemoryAddressingType::Index;

            case static_cast<int>(MemoryAddressingType::IndexDeferred):
                return MemoryAddressingType::IndexDeferred;

            default:
                throw Common::Error(DBG_LINE, "unknown addressing mode", Common::ErrorType::Critical);
        }
    }

    Word Executer::GetSourceAddress(const Byte source, const OperationSizeType operationSizeType) const
    {
        const MemoryAddressingType addressingMode = GetAddressingMode(source);
        const Byte                 registerNumber = GetRegisterNumber(source);
        const Address              registerAddress = ConvertRegisterNumberToAddress(registerNumber);
        const Word                 valueInRegister = Bus->Read(registerAddress);

        switch (addressingMode)
        {
        case MemoryAddressingType::Register:
            return registerAddress;

        case MemoryAddressingType::RegisterDeferred:
        {
            return valueInRegister;
        }

        case MemoryAddressingType::Autodecrement:
        {
            const Word subtrahend = operationSizeType == OperationSizeType::Byte ? sizeof(Byte) : sizeof(Word);
            Bus->Write(registerAddress, valueInRegister - subtrahend);

            return valueInRegister - subtrahend;
        }

        case MemoryAddressingType::AutodecrementDeferred:
        {
            const Word subtrahend = sizeof(Word);
            Bus->Write(registerAddress, valueInRegister - subtrahend);

            return valueInRegister - subtrahend;
        }

        case MemoryAddressingType::Autoincrement:
        {
            const Word addend = operationSizeType == OperationSizeType::Byte ? sizeof(Byte) : sizeof(Word);
            Bus->Write(registerAddress, valueInRegister + addend);

            return valueInRegister;
        }

        case MemoryAddressingType::AutoincrementDeferred:
        {
            const Word addend = sizeof(Word);
            Bus->Write(registerAddress, valueInRegister + addend);

            return valueInRegister;
        }

        case MemoryAddressingType::Index:
            CHECK(false, "addressing type is not implemented yet.");
            break;

        case MemoryAddressingType::IndexDeferred:
            CHECK(false, "addressing type is not implemented yet.");
            break;
        }
        CHECK(false, "unsupported addressing type.");
    }

    Byte Executer::ReadByte(const Address address) const
    {
        const Word word = Bus->Read(address);
        const Byte byte = *reinterpret_cast<const Byte*>(&(word));

        return byte;
    }

    Word Executer::ReadWord(const Address address) const
    {
        const Word word = Bus->Read(address);

        return word;
    }

    void Executer::WriteByte(const Address address, const Byte value)
    {
        Word word = Bus->Read(address);
        *reinterpret_cast<Byte*>(&word) = value;

        Bus->Write(address, word);
    }

    void Executer::WriteWord(const Address address, const Word value)
    {
        Bus->Write(address, value);
    }
}