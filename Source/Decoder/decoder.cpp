#include "decoder.h"
#include <assert.h>

namespace Decoding
{
    using Common::Instruction;
    
    namespace
    {
        const word DoubleOperandInstructionMask = 0170000;
        const word OneAndHalfInstructionMask    = 0177000;
        const word SingleOperandInstructionMask = 0177700;
        const word BranchInstructionMask        = 0177400;

        inline Common::UnknownInstruction ConstructUnknownInstruction()
        {
            return Common::UnknownInstruction { Common::InstructionGroup::I_Unknown, Common::InstructionType::I_UNKNOWN, "UNKNOWN" };
        }
    }

    Instruction Decoder::ConstructDoubleOperandInstruction(const word raw) const
    {
        const word opcode = raw & DoubleOperandInstructionMask;
        const auto it = DoubleOperandInstructions.find(opcode);
        
        if (it!= DoubleOperandInstructions.end())
        {
            const Common::InstructionMeta meta = it->second;
            const byte destination = raw & 077;
            const byte source = (raw & 07700) >> 6;

            return Common::DoubleOperandInstruction{ meta, destination, source, opcode };
        }
        
        return ConstructUnknownInstruction();
    }
    
    Instruction Decoder::ConstructOneAndHalfInstruction(const word raw) const
    {
        const word opcode = raw & OneAndHalfInstructionMask;
        const auto it = OneAndHalfInstructions.find(opcode);
        
        if (it != OneAndHalfInstructions.end())
        {
            const Common::InstructionMeta meta = it->second;
            const byte destination = raw & 077;
            const byte reg = (raw & 0700) >> 6;

            return Common::OneAndHalfInstruction{ meta, destination, reg, opcode };
        }
        
        return ConstructUnknownInstruction();
    }
    
    Instruction Decoder::ConstructSingleOperandInstruction(const word raw) const
    {
        const word opcode = raw & SingleOperandInstructionMask;
        const auto it = SingleOperandInstructions.find(opcode);
        
        if (it != SingleOperandInstructions.end())
        {
            const Common::InstructionMeta meta = it->second;
            const byte destination = raw & (~SingleOperandInstructionMask);

            return Common::SingleOperandInstruction{ meta, destination, opcode };
        }
        
        return ConstructUnknownInstruction();
    }
    
    Instruction Decoder::ConstructBranchInstruction(const word raw) const
    {
        const word opcode = raw & BranchInstructionMask;
        const auto it = BranchInstructions.find(opcode);
        
        if (it != BranchInstructions.end())
        {
            const Common::InstructionMeta meta = it->second;
            const byte offset = raw & (~BranchInstructionMask);

            return Common::SingleOperandInstruction{ meta, offset, opcode };
        }
        
        return ConstructUnknownInstruction();
    }
    
    inline bool Decoder::IsDoubleOperandInstruction(const word raw) const
    {
        const word opcode = raw & DoubleOperandInstructionMask;
        if (DoubleOperandInstructions.find(opcode) != DoubleOperandInstructions.end())
            return true;

        return false;
    }
    
    inline bool Decoder::IsOneAndHalfInstruction(const word raw) const
    {
        const word opcode = raw & OneAndHalfInstructionMask;
        if (OneAndHalfInstructions.find(opcode) != OneAndHalfInstructions.end())
            return true;

        return false;
    }
    
    inline bool Decoder::IsSingleOperandInstruction(const word raw) const
    {
        const word opcode = raw & SingleOperandInstructionMask;
        if (SingleOperandInstructions.find(opcode) != SingleOperandInstructions.end())
            return true;

        return false;
    }
    
    inline bool Decoder::IsBranchInstruction(const word raw) const
    {
        const word opcode = raw & BranchInstructionMask;
        if (BranchInstructions.find(opcode) != BranchInstructions.end())
            return true;

        return false;
    }
    
    Common::InstructionGroup  Decoder::GetInstructionGroup(const word raw) const
    {
        if (IsDoubleOperandInstruction(raw))
            return Common::I_DoubleOperand;

        if (IsOneAndHalfInstruction(raw))
            return Common::I_OneAndHalf;

        if (IsSingleOperandInstruction(raw))
            return Common::I_SingleOperand;

        if (IsBranchInstruction(raw))
            return Common::I_Branch;

        return Common::I_Unknown;
    }
    
    Instruction Decoder::Decode(const word raw) const
    {
        switch (GetInstructionGroup(raw))
        {
        case Common::I_DoubleOperand: return ConstructDoubleOperandInstruction(raw);
        case Common::I_OneAndHalf:    return ConstructOneAndHalfInstruction(raw);
        case Common::I_SingleOperand: return ConstructSingleOperandInstruction(raw);
        case Common::I_Branch:        return ConstructBranchInstruction(raw);
        case Common::I_Unknown:       return ConstructUnknownInstruction();

        default:
            assert(false);
        }
    }
}
