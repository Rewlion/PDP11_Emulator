#include "Executer.h"
#include "../../Common/Exceptions/Error.h"
#include "../../Common/Logs/Logs.h"
#include "../../Memory/Unibus.h"

#include <assert.h>

namespace
{
    template<typename T>
    inline int Sign(const T value)
    {
        if (value > 0)
            return 1;
        else if (value < 0)
            return -1;
        else
            return 0;
    }

    template<typename T>
    inline T Abs(const T value)
    {
        if (value >= 0)
            return value;
        else
            return -value;
    }

    inline void NOT_IMPLEMENTED()
    {
        throw Common::Error(DBG_LINE, "not Implemented.", Common::ErrorType::Critical);
    }
}

Executer::Executer(::FlagRegister& flagRegister, Unibus* bus)
    : FlagRegister(flagRegister)
    , Bus(bus)
{
}

void Executer::operator()(const UnknownInstruction& instruction)
{
    throw Common::Error("Unknown instruction", Common::Critical);
}

void Executer::operator()(const NoOperandInstruction& instruction)
{
    switch (instruction.Meta.Type)
    {
    case InstructionType::I_NOP:
        ExecuteNOP(instruction);
        break;

    default:
        NOT_IMPLEMENTED();
    }
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
        ExecuteCMP(instruction);
        break;

    case InstructionType::I_CMPB:
        ExecuteCMPB(instruction);
        break;

    case InstructionType::I_ADD:
        ExecuteADD(instruction);
        break;

    case InstructionType::I_SUB:
        ExecuteSUB(instruction);
        break;

    case InstructionType::I_BIT:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BITB:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BIC:
        ExecuteBIC(instruction);
        break;

    case InstructionType::I_BICB:
        ExecuteBICB(instruction);
        break;

    case InstructionType::I_BIS:
        ExecuteBIS(instruction);
        break;

    case InstructionType::I_BISB:
        NOT_IMPLEMENTED();
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
        ExecuteMUL(instruction);
        break;

    case InstructionType::I_DIV:
        ExecuteDIV(instruction);
        break;

    case InstructionType::I_ASH:
        ExecuteASH(instruction);
        break;

    case InstructionType::I_ASHC:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_XOR:
        ExecuteXOR(instruction);
        break;

    case InstructionType::I_JSR:
        ExecuteJSR(instruction);
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
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_COMB:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_INC:
        ExecuteINC(instruction);
        break;

    case InstructionType::I_INCB:
        ExecuteINCB(instruction);
        break;

    case InstructionType::I_DEC:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_DECB:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_NEG:
        ExecuteNEG(instruction);
        break;

    case InstructionType::I_NEGB:
        ExecuteNEGB(instruction);
        break;

    case InstructionType::I_TST:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_TSTB:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_ASR:
        ExecuteASR(instruction);
        break;

    case InstructionType::I_ASRB:
        ExecuteASRB(instruction);
        break;

    case InstructionType::I_ASL:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_ASLB:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_ROR:
        ExecuteROR(instruction);
        break;

    case InstructionType::I_RORB:
        ExecuteRORB(instruction);
        break;

    case InstructionType::I_ROL:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_ROLB:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_RTS:
        ExecuteRTS(instruction);
        break;

    case InstructionType::I_SWAB:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_ADC:
        ExecuteADC(instruction);
        break;

    case InstructionType::I_ADCB:
        ExecuteADCB(instruction);
        break;

    case InstructionType::I_SBC:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_SBCB:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_SXT:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_JMP:
        ExecuteJMP(instruction);
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
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BNE:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BEQ:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BPL:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BMI:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BVC:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BVS:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BCC:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BCS:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BGE:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BLT:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BGT:
        ExecuteBGT(instruction);
        break;

    case InstructionType::I_BLE:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BHI:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BLOS:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BHIS:
        NOT_IMPLEMENTED();
        break;

    case InstructionType::I_BLO:
        NOT_IMPLEMENTED();
        break;

    default:
        assert(false);
        break;
    }
}

void Executer::ExecuteNOP(const NoOperandInstruction& instruction)
{
    //DO NOTHING
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

void Executer::ExecuteCMP(const DoubleOperandInstruction& instruction)
{
    const Word src = GetSourceAddress(instruction.Source, OperationSizeType::Word);
    const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
    const int srcValue = ReadWord(src);
    const int dstValue = ReadWord(dst);

    const int result = srcValue - dstValue;

    const Byte N = result < 0 ? 1 : 0;
    const Byte Z = result == 0 ? 1 : 0;
    const bool bOverflow = (Sign(srcValue) != Sign(dstValue)) && (Sign(dstValue) == Sign(result));
    const Byte V = bOverflow ? 1 : 0;

    FlagRegister.SetFlag(FlagRegister::FlagType::Sign, N);
    FlagRegister.SetFlag(FlagRegister::FlagType::Zero, Z);
    FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, V);
}

void Executer::ExecuteCMPB(const DoubleOperandInstruction& instruction)
{
    const Word src = GetSourceAddress(instruction.Source, OperationSizeType::Byte);
    const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Byte);
    const int srcValue = ReadByte(src);
    const int dstValue = ReadByte(dst);

    const int result = srcValue - dstValue;

    const Byte N = result < 0 ? 1 : 0;
    const Byte Z = result == 0 ? 1 : 0;
    const bool bOverflow = (Sign(srcValue) != Sign(dstValue)) && (Sign(dstValue) == Sign(result));
    const Byte V = bOverflow ? 1 : 0;

    FlagRegister.SetFlag(FlagRegister::FlagType::Sign, N);
    FlagRegister.SetFlag(FlagRegister::FlagType::Zero, Z);
    FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, V);
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

void Executer::ExecuteBIS(const DoubleOperandInstruction& instruction)
{
    const Word src = GetSourceAddress(instruction.Source, OperationSizeType::Word);
    const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
    const Word srcValue = ReadWord(src);
    const Word dstValue = ReadWord(dst);

    const Word result = dstValue | srcValue;

    const Byte N = GetWordMSB(result);
    const Byte Z = result == 0 ? 1 : 0;
    const Byte V = 0;

    FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, V);
    FlagRegister.SetFlag(FlagRegister::FlagType::Sign, N);
    FlagRegister.SetFlag(FlagRegister::FlagType::Zero, Z);

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

void Executer::ExecuteMUL(const OneAndHalfInstruction& instruction)
{
    const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
    const Word reg = GetSourceAddress(instruction.Register, OperationSizeType::Word);
    const short regValue = ReadWord(reg);
    const short dstValue = ReadWord(dst);

    union
    {
        int Raw;
        struct
        {
            short Low;
            short High;
        };
    } product;

    product.Raw = regValue * dstValue;

    const Byte N = product.Raw < 0 ? 1 : 0;
    const Byte Z = product.Raw == 0 ? 1 : 0;
    const Byte V = 0;
    const Byte C = product.Raw < (-(1 << 15)) || product.Raw >= ((1 << 15) - 1) ? 1 : 0;

    FlagRegister.SetFlag(FlagRegister::FlagType::Carry, C);
    FlagRegister.SetFlag(FlagRegister::FlagType::Overflow, V);
    FlagRegister.SetFlag(FlagRegister::FlagType::Sign, N);
    FlagRegister.SetFlag(FlagRegister::FlagType::Zero, Z);

    WriteWord(ConvertRegisterNumberToAddress(instruction.Register), product.Low);
    if (instruction.Register % 2 == 0)
        WriteWord(ConvertRegisterNumberToAddress(instruction.Register + 1), product.High);
}

void Executer::ExecuteDIV(const OneAndHalfInstruction& instruction)
{
    const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
    const Word reg = GetSourceAddress(instruction.Register, OperationSizeType::Word);
    const short regValue = ReadWord(reg);
    const short dstValue = ReadWord(dst);

    if (dstValue == 0)
        throw Common::Error(DBG_LINE, "Attempt to divide by 0.", Common::ErrorType::Warning);

    const short quotient = regValue / dstValue;
    const short remainder = Abs(regValue) % dstValue;

    const Byte N = quotient < 0 ? 1 : 0;
    const Byte Z = quotient == 0 ? 1 : 0;
    
    FlagRegister.SetFlag(FlagRegister::FlagType::Sign, N);
    FlagRegister.SetFlag(FlagRegister::FlagType::Zero, Z);

    WriteWord(reg, quotient);
    if (instruction.Register < static_cast<int>(Register::R7))
        WriteWord(ConvertRegisterNumberToAddress(instruction.Register + 1), remainder);
}

void Executer::ExecuteJSR(const OneAndHalfInstruction& instruction)
{
    const Word dst = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
    const Word reg = GetSourceAddress(instruction.Register, OperationSizeType::Word);
    const Word regValue = ReadWord(reg);
    const Word dstValue = ReadWord(dst);
    const Word pc = ReadWord(GetPCAddress());

    PushWord(regValue);
    WriteWord(reg, pc);
    WriteWord(GetPCAddress(), dstValue);
}

void Executer::ExecuteASH(const OneAndHalfInstruction& instruction)
{

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

void Executer::ExecuteRTS(const SingleOperandInstruction& instruction)
{
    const Word address = GetSourceAddress(instruction.Destination & 07, OperationSizeType::Byte);
    const Word valueInRegister = ReadWord(address);

    WriteWord(GetPCAddress(), valueInRegister);
    const Word sp = PopWord();
    WriteWord(address, sp);
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

void Executer::ExecuteJMP(const SingleOperandInstruction& instruction)
{
    const Address address = GetSourceAddress(instruction.Destination, OperationSizeType::Word);
    const Word valueInRegister = ReadWord(address);

    WriteWord(GetPCAddress(), valueInRegister);
}

void Executer::ExecuteBGT(const BranchInstruction& instruction)
{
    const Byte Z = FlagRegister.GetFlag(FlagRegister::FlagType::Zero);
    const Byte N = FlagRegister.GetFlag(FlagRegister::FlagType::Sign);
    const Byte V = FlagRegister.GetFlag(FlagRegister::FlagType::Overflow);

    bool f = Z || (N == 0 && V == 0);
    if (f)
    {
        Word pc = ReadWord(GetPCAddress());
        const int offset = static_cast<char>(instruction.Offset) ;
        pc = static_cast<Word>(static_cast<int>(pc) + offset * 2);
        WriteWord(GetPCAddress(), pc);
    }
}

Executer::MemoryAddressingType Executer::GetAddressingMode(const Byte reg) const
{
    int mode = (reg & 070) >> 3;
    switch (mode)
    {
        case static_cast<int>(MemoryAddressingType::Register) :
            return MemoryAddressingType::Register;

        case static_cast<int>(MemoryAddressingType::RegisterDeferred) :
            return MemoryAddressingType::RegisterDeferred;

        case static_cast<int>(MemoryAddressingType::Autoincrement) :
            return MemoryAddressingType::Autoincrement;

        case static_cast<int>(MemoryAddressingType::AutoincrementDeferred) :
            return MemoryAddressingType::AutoincrementDeferred;

        case static_cast<int>(MemoryAddressingType::Autodecrement) :
            return MemoryAddressingType::Autodecrement;

        case static_cast<int>(MemoryAddressingType::AutodecrementDeferred) :
            return MemoryAddressingType::AutodecrementDeferred;

        case static_cast<int>(MemoryAddressingType::Index) :
            return MemoryAddressingType::Index;

        case static_cast<int>(MemoryAddressingType::IndexDeferred) :
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
    {
        const Word pc = Bus->Read(GetPCAddress());
        const Word addend = Bus->Read(pc);
        Bus->Write(GetPCAddress(), pc + sizeof(Word));
        
        return valueInRegister + addend;
    }

    case MemoryAddressingType::IndexDeferred:
    {
        const Word pc = Bus->Read(GetPCAddress());
        const Word addend = Bus->Read(pc);
        Bus->Write(GetPCAddress(), pc + sizeof(Word));
        const Word address = Bus->Read(valueInRegister + addend);

        return address;
    }
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