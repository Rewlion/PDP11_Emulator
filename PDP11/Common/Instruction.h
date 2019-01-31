#pragma once

#include "types.h"

#include <variant>
#include <string>

enum class InstructionGroup
{
    I_Unknown,
    I_NoOperand,
    I_SingleOperand,
    I_DoubleOperand,
    I_OneAndHalf,
    I_Branch,
    I_Condition,
    I_Other
};

enum class InstructionType
{
    I_UNKNOWN,
    /*NO OPERANDS*/
    I_NOP,
    /*Single operand instructions*/
    I_CLR,
    I_CLRB,
    I_COM,
    I_COMB,
    I_INC,
    I_INCB,
    I_DEC,
    I_DECB,
    I_NEG,
    I_NEGB,
    I_TST,
    I_TSTB,
    I_ASR,
    I_ASRB,
    I_ASL,
    I_ASLB,
    I_ROR,
    I_RORB,
    I_ROL,
    I_ROLB,
    I_SWAB,
    I_ADC,
    I_ADCB,
    I_SBC,
    I_SBCB,
    I_SXT,
    /*Double operand instructions*/
    I_MOV,
    I_MOVB,
    I_CMP,
    I_CMPB,
    I_ADD,
    I_SUB,
    I_BIT,
    I_BITB,
    I_BIC,
    I_BICB,
    I_BIS,
    I_BISB,
    /*One and half instructions*/
    I_MUL,
    I_DIV,
    I_ASH,
    I_ASHC,
    I_XOR,
    /*Branch instructions*/
    I_BR,
    I_BNE,
    I_BEQ,
    I_BPL,
    I_BMI,
    I_BVC,
    I_BVS,
    I_BCC,
    I_BCS,
    I_BGE,
    I_BLT,
    I_BGT,
    I_BLE,
    I_BHI,
    I_BLOS,
    I_BHIS,
    I_BLO,
    /*Other instructions*/
    I_JMP,
    I_JSR,
    I_RTS,
    I_MAR,
    I_SOB,
    I_EMT,
    I_TRAP,
    I_BPT,
    I_IOT,
    I_RTI,
    I_RTT,
    I_HALT,
    I_WAIT,
    I_RESET,
    I_MFPI,
    I_MTPI
};

struct InstructionMeta
{
    const InstructionGroup Group;
    const InstructionType Type;
    const std::string Name;
};

struct UnknownInstruction
{
    const InstructionMeta Meta;
};

struct NoOperandInstruction
{
    const InstructionMeta Meta;
    const Word Opcode;
};

struct DoubleOperandInstruction
{
    const InstructionMeta Meta;
    const Byte Destination;
    const Byte Source;
    const Word Opcode;
};

struct OneAndHalfInstruction
{
    const InstructionMeta Meta;
    const Byte Destination;
    const Byte Register;
    const Word Opcode;
};

struct SingleOperandInstruction
{
    const InstructionMeta Meta;
    const Byte Destination;
    const Word Opcode;
};

struct BranchInstruction
{
    const InstructionMeta Meta;
    const Byte Offset;
    const Word BaseCode;
};

typedef std::variant<UnknownInstruction,
    NoOperandInstruction,
    DoubleOperandInstruction,
    OneAndHalfInstruction,
    SingleOperandInstruction,
    BranchInstruction> Instruction;