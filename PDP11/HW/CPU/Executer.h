#pragma once

#include "FlagRegister.h"
#include "../../Common/Exceptions/Error.h"
#include "../../Common/Instruction.h"
#include "../../Memory/MemoryRegionInformation.h"
#include "../../Memory/Unibus.h"

class Unibus;

class Executer
{
public:
    Executer(FlagRegister& flagRegister, Unibus* bus);

    void operator()(const UnknownInstruction& instruction);
    void operator()(const NoOperandInstruction& instruction);
    void operator()(const DoubleOperandInstruction& instruction);
    void operator()(const OneAndHalfInstruction& instruction);
    void operator()(const SingleOperandInstruction& instruction);
    void operator()(const BranchInstruction& instruction);

private:
    //NO OPERAND
    void ExecuteNOP(const NoOperandInstruction& instruction);

    // DOUBLE OPERAND
    void ExecuteCMP(const DoubleOperandInstruction& instruction);
    
    void ExecuteCMPB(const DoubleOperandInstruction& instruction);

    void ExecuteMOV(const DoubleOperandInstruction& instruction);

    void ExecuteMOVB(const DoubleOperandInstruction& instruction);

    void ExecuteADD(const DoubleOperandInstruction& instruction);

    void ExecuteSUB(const DoubleOperandInstruction& instruction);


    void ExecuteBIC(const DoubleOperandInstruction& instruction);

    void ExecuteBICB(const DoubleOperandInstruction& instruction);

    // ONE AND HALF
    void ExecuteXOR(const OneAndHalfInstruction& instruction);

    void ExecuteDIV(const OneAndHalfInstruction& instruction);

    //SINGLE OPERAND
    void ExecuteCLR(const SingleOperandInstruction& instruction);

    void ExecuteCLRB(const SingleOperandInstruction& instruction);

    void ExecuteINC(const SingleOperandInstruction& instruction);

    void ExecuteINCB(const SingleOperandInstruction& instruction);

    void ExecuteNEG(const SingleOperandInstruction& instruction);

    void ExecuteNEGB(const SingleOperandInstruction& instruction);

    void ExecuteASR(const SingleOperandInstruction& instruction);

    void ExecuteASRB(const SingleOperandInstruction& instruction);

    void ExecuteROR(const SingleOperandInstruction& instruction);

    void ExecuteRORB(const SingleOperandInstruction& instruction);

    void ExecuteADC(const SingleOperandInstruction& instruction);

    void ExecuteADCB(const SingleOperandInstruction& instruction);

    void ExecuteJMP(const SingleOperandInstruction& instruction);

    //BRANCHES
    void ExecuteBGT(const BranchInstruction& instruction);

private:
    enum class OperationSizeType
    {
        Byte = 0,
        Word = 1
    };

    enum class MemoryAddressingType
    {
        Register = 0,
        RegisterDeferred = 1,
        Autoincrement = 2,
        AutoincrementDeferred = 3,
        Autodecrement = 4,
        AutodecrementDeferred = 5,
        Index = 6,
        IndexDeferred = 7
    };

    MemoryAddressingType GetAddressingMode(const Byte reg) const;
    inline Byte          GetRegisterNumber(const Byte source) const;
    inline Address       ConvertRegisterNumberToAddress(const Byte number) const;
    Word                 GetSourceAddress(const Byte source, const OperationSizeType operationSizeType) const;
    inline Byte          GetByteMSB(const Byte byte) const;
    inline Byte          GetWordMSB(const Word word) const;

    Byte                 ReadByte(const Address address) const;
    Word                 ReadWord(const Address address) const;
    void                 WriteByte(const Address address, const Byte value);
    void                 WriteWord(const Address address, const Word value);

    inline void          IncPC();

private:
    FlagRegister& FlagRegister;
    Unibus*       Bus;
};

Byte Executer::GetRegisterNumber(const Byte source) const
{
    return (source & 07);
}

Address Executer::ConvertRegisterNumberToAddress(const Byte number) const
{
    CHECK((number >= 0) && (number <= 7), "invalid register number");//check that addressing mode is Register

    return GetRegistersBegining() + number * sizeof(Word);
}

Byte Executer::GetByteMSB(const Byte byte) const
{
    return byte >> 7;
}

Byte Executer::GetWordMSB(const Word word) const
{
    return word >> 15;
}

void Executer::IncPC()
{
    const Word current = Bus->Read(GetPCAddress());
    Bus->Write(GetPCAddress(), current + sizeof(Word));
}