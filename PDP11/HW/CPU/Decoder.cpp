#include "Decoder.h"

#include <assert.h>

namespace PDP11
{
    namespace
    {
        const Word DoubleOperandInstructionMask = 0170000;
        const Word OneAndHalfInstructionMask = 0177000;
        const Word SingleOperandInstructionMask = 0177700;
        const Word BranchInstructionMask = 0177400;

        inline UnknownInstruction ConstructUnknownInstruction()
        {
            return UnknownInstruction{ InstructionGroup::I_Unknown, InstructionType::I_UNKNOWN, "UNKNOWN" };
        }
    }

    Instruction Decoder::ConstructDoubleOperandInstruction(const Word raw) const
    {
        const Word opcode = raw & DoubleOperandInstructionMask;
        const auto it = DoubleOperandInstructions.find(opcode);

        if (it != DoubleOperandInstructions.end())
        {
            const InstructionMeta meta = it->second;
            const Byte destination = raw & 077;
            const Byte source = (raw & 07700) >> 6;

            return DoubleOperandInstruction{ meta, destination, source, opcode };
        }

        return ConstructUnknownInstruction();
    }

    Instruction Decoder::ConstructOneAndHalfInstruction(const Word raw) const
    {
        const Word opcode = raw & OneAndHalfInstructionMask;
        const auto it = OneAndHalfInstructions.find(opcode);

        if (it != OneAndHalfInstructions.end())
        {
            const InstructionMeta meta = it->second;
            const Byte destination = raw & 077;
            const Byte reg = (raw & 0700) >> 6;

            return OneAndHalfInstruction{ meta, destination, reg, opcode };
        }

        return ConstructUnknownInstruction();
    }

    Instruction Decoder::ConstructSingleOperandInstruction(const Word raw) const
    {
        const Word opcode = raw & SingleOperandInstructionMask;
        const auto it = SingleOperandInstructions.find(opcode);

        if (it != SingleOperandInstructions.end())
        {
            const InstructionMeta meta = it->second;
            const Byte destination = raw & (~SingleOperandInstructionMask);

            return SingleOperandInstruction{ meta, destination, opcode };
        }

        return ConstructUnknownInstruction();
    }

    Instruction Decoder::ConstructBranchInstruction(const Word raw) const
    {
        const Word opcode = raw & BranchInstructionMask;
        const auto it = BranchInstructions.find(opcode);

        if (it != BranchInstructions.end())
        {
            const InstructionMeta meta = it->second;
            const Byte offset = raw & (~BranchInstructionMask);

            return SingleOperandInstruction{ meta, offset, opcode };
        }

        return ConstructUnknownInstruction();
    }

    inline bool Decoder::IsDoubleOperandInstruction(const Word raw) const
    {
        const Word opcode = raw & DoubleOperandInstructionMask;
        if (DoubleOperandInstructions.find(opcode) != DoubleOperandInstructions.end())
            return true;

        return false;
    }

    inline bool Decoder::IsOneAndHalfInstruction(const Word raw) const
    {
        const Word opcode = raw & OneAndHalfInstructionMask;
        if (OneAndHalfInstructions.find(opcode) != OneAndHalfInstructions.end())
            return true;

        return false;
    }

    inline bool Decoder::IsSingleOperandInstruction(const Word raw) const
    {
        const Word opcode = raw & SingleOperandInstructionMask;
        if (SingleOperandInstructions.find(opcode) != SingleOperandInstructions.end())
            return true;

        return false;
    }

    inline bool Decoder::IsBranchInstruction(const Word raw) const
    {
        const Word opcode = raw & BranchInstructionMask;
        if (BranchInstructions.find(opcode) != BranchInstructions.end())
            return true;

        return false;
    }

    InstructionGroup  Decoder::GetInstructionGroup(const Word raw) const
    {
        if (IsDoubleOperandInstruction(raw))
            return InstructionGroup::I_DoubleOperand;

        if (IsOneAndHalfInstruction(raw))
            return InstructionGroup::I_OneAndHalf;

        if (IsSingleOperandInstruction(raw))
            return InstructionGroup::I_SingleOperand;

        if (IsBranchInstruction(raw))
            return InstructionGroup::I_Branch;

        return InstructionGroup::I_Unknown;
    }

    Instruction Decoder::Decode(const Word raw) const
    {
        switch (GetInstructionGroup(raw))
        {
        case InstructionGroup::I_DoubleOperand: return ConstructDoubleOperandInstruction(raw);
        case InstructionGroup::I_OneAndHalf:    return ConstructOneAndHalfInstruction(raw);
        case InstructionGroup::I_SingleOperand: return ConstructSingleOperandInstruction(raw);
        case InstructionGroup::I_Branch:        return ConstructBranchInstruction(raw);
        case InstructionGroup::I_Unknown:       return ConstructUnknownInstruction();

        default:
            assert(false);
        }
    }
}