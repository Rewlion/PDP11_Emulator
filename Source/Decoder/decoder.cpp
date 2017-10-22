#include "decoder.h"
#include <assert.h>

namespace PDP11Emulator::Decoding
{
    using PDP11Emulator::Common::Instruction;
    
    namespace
    {
        const uint16 DoubleOperandInstructionMask = 0170000;
        const uint16 OneAndHalfInstructionMask	  = 0177000;
        const uint16 SingleOperandInstructionMask = 0177700;
        const uint16 BranchInstructionMask        = 0177400;

        inline PDP11Emulator::Common::UnknownInstruction ConstructUnknownInstruction()
        {
            return PDP11Emulator::Common::UnknownInstruction { PDP11Emulator::Common::InstructionGroup::I_Unknown, PDP11Emulator::Common::InstructionType::I_UNKNOWN, "UNKNOWN" };
        }
    }

    Instruction Decoder::ConstructDoubleOperandInstruction(const uint16 raw) const
    {
        const uint16 opcode = raw & DoubleOperandInstructionMask;
        const auto it = DoubleOperandInstructions.find(opcode);
        
        if (it!= DoubleOperandInstructions.end())
        {
            const PDP11Emulator::Common::InstructionMeta meta = it->second;
            const uint8 destination = raw & 077;
            const uint8 source = (raw & 07700) >> 6;

            return PDP11Emulator::Common::DoubleOperandInstruction{ meta, destination, source, opcode };
        }
        
        return ConstructUnknownInstruction();
    }
    
    Instruction Decoder::ConstructOneAndHalfInstruction(const uint16 raw) const
    {
        const uint16 opcode = raw & OneAndHalfInstructionMask;
        const auto it = OneAndHalfInstructions.find(opcode);
        
        if (it != OneAndHalfInstructions.end())
        {
            const PDP11Emulator::Common::InstructionMeta meta = it->second;
            const uint8 destination = raw & 077;
            const uint8 reg = (raw & 0700) >> 6;

            return PDP11Emulator::Common::OneAndHalfInstruction{ meta, destination, reg, opcode };
        }
        
        return ConstructUnknownInstruction();
    }
    
    Instruction Decoder::ConstructSingleOperandInstruction(const uint16 raw) const
    {
        const uint16 opcode = raw & SingleOperandInstructionMask;
        const auto it = SingleOperandInstructions.find(opcode);
        
        if (it != SingleOperandInstructions.end())
        {
            const PDP11Emulator::Common::InstructionMeta meta = it->second;
            const uint8 destination = raw & (~SingleOperandInstructionMask);

            return PDP11Emulator::Common::SingleOperandInstruction{ meta, destination, opcode };
        }
        
        return ConstructUnknownInstruction();
    }
    
    Instruction Decoder::ConstructBranchInstruction(const uint16 raw) const
    {
        const uint16 opcode = raw & BranchInstructionMask;
        const auto it = BranchInstructions.find(opcode);
        
        if (it != BranchInstructions.end())
        {
            const PDP11Emulator::Common::InstructionMeta meta = it->second;
            const uint8 offset = raw & (~BranchInstructionMask);

            return PDP11Emulator::Common::SingleOperandInstruction{ meta, offset, opcode };
        }
        
        return ConstructUnknownInstruction();
    }
    
    inline bool Decoder::IsDoubleOperandInstruction(const uint16 raw) const
    {
        const uint16 opcode = raw & DoubleOperandInstructionMask;
        if (DoubleOperandInstructions.find(opcode) != DoubleOperandInstructions.end())
            return true;

        return false;
    }
    
    inline bool Decoder::IsOneAndHalfInstruction(const uint16 raw) const
    {
        const uint16 opcode = raw & OneAndHalfInstructionMask;
        if (OneAndHalfInstructions.find(opcode) != OneAndHalfInstructions.end())
            return true;

        return false;
    }
    
    inline bool Decoder::IsSingleOperandInstruction(const uint16 raw) const
    {
        const uint16 opcode = raw & SingleOperandInstructionMask;
        if (SingleOperandInstructions.find(opcode) != SingleOperandInstructions.end())
            return true;

        return false;
    }
    
    inline bool Decoder::IsBranchInstruction(const uint16 raw) const
    {
        const uint16 opcode = raw & BranchInstructionMask;
        if (BranchInstructions.find(opcode) != BranchInstructions.end())
            return true;

        return false;
    }
    
    Common::InstructionGroup  Decoder::GetInstructionGroup(const uint16 raw) const
    {
        if (IsDoubleOperandInstruction(raw))
            return PDP11Emulator::Common::I_DoubleOperand;

        if (IsOneAndHalfInstruction(raw))
            return PDP11Emulator::Common::I_OneAndHalf;

        if (IsSingleOperandInstruction(raw))
            return PDP11Emulator::Common::I_SingleOperand;

        if (IsBranchInstruction(raw))
            return PDP11Emulator::Common::I_Branch;

        return PDP11Emulator::Common::I_Unknown;
    }
    
    Instruction Decoder::Decode(const uint16 raw) const
    {
        switch (GetInstructionGroup(raw))
        {
        case PDP11Emulator::Common::I_DoubleOperand: return ConstructDoubleOperandInstruction(raw);
        case PDP11Emulator::Common::I_OneAndHalf:    return ConstructOneAndHalfInstruction(raw);
        case PDP11Emulator::Common::I_SingleOperand: return ConstructSingleOperandInstruction(raw);
        case PDP11Emulator::Common::I_Branch:        return ConstructBranchInstruction(raw);
        case PDP11Emulator::Common::I_Unknown:       return ConstructUnknownInstruction();

        default:
            assert(false);
        }
    }
}
