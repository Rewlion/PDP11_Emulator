#pragma once

#include "utils.h"

#include <Common/instruction.h>

namespace PDP11Emulator::Decoding
{
    class Decoder
    {
    public:
        Decoder() = default;
        PDP11Emulator::Common::Instruction Decode(const word raw) const;
    
    private:
        inline bool IsDoubleOperandInstruction(const word raw) const;
        inline bool IsOneAndHalfInstruction(const word raw) const;
        inline bool IsSingleOperandInstruction(const word raw) const;
        inline bool IsBranchInstruction(const word raw) const;
        Common::InstructionGroup  GetInstructionGroup(const word raw) const;
    
        PDP11Emulator::Common::Instruction ConstructDoubleOperandInstruction(const word raw) const;
        PDP11Emulator::Common::Instruction ConstructOneAndHalfInstruction(const word raw) const;
        PDP11Emulator::Common::Instruction ConstructSingleOperandInstruction(const word raw) const;
        PDP11Emulator::Common::Instruction ConstructBranchInstruction(const word raw) const;
    
    private:
        const IsaTable SingleOperandInstructions = {
            /*Single operand instructions*/
                //GENERAL
            { 0005000, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_CLR, "CLR"  } },
            { 0105000, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_CLRB, "CLRB" } },
            { 0005100, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_COM, "COM"  } },
            { 0105100, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_COMB, "COMB" } },
            { 0005200, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_INC, "INC"  } },
            { 0105200, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_INCB, "INCB" } },
            { 0005300, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_DEC, "DEC"  } },
            { 0105300, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_DECB, "DECB" } },
            { 0005400, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_NEG, "NEG"  } },
            { 0105400, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_NEGB, "NEGB" } },
            { 0005700, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_TST, "TST"  } },
            { 0105700, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_TSTB, "TSTB" } },
                //SHIFT&ROTATE
            { 0006200, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ASR, "ASR"  } },
            { 0106200, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ASRB, "ASRB" } },
            { 0006300, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ASL, "ASL"  } },
            { 0106300, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ASLB, "ASLB" } },
            { 0006000, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ROR, "ROR"  } },
            { 0106000, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_RORB, "RORB" } },
            { 0006100, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ROL, "ROL"  } },
            { 0106100, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ROLB, "ROLB" } },
            { 0000300, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_SWAB, "SWAB" } },
                //MULTIPLE PRECISION
            { 0005500, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ADC, "ADC"  } },
            { 0105500, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_ADCB, "ADCB" } },
            { 0005600, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_SBC, "SBC"  } },
            { 0105600, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_SBCB, "SBCB" } },
            { 0006700, IsaEntry{ PDP11Emulator::Common::I_SingleOperand, PDP11Emulator::Common::I_SXT, "SXT"  } },
        };
        const IsaTable DoubleOperandInstructions = {
            /*Double operand instructions*/
                //GENERAL
            { 0010000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_MOV ,"MOV" } },
            { 0110000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_MOVB,"MOVB" } },
            { 0020000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_CMP ,"CMP" } },
            { 0120000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_CMPB,"CMPB" } },
            { 0060000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_ADD ,"ADD" } },
            { 0160000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_SUB ,"SUB" } },
            //LOGICAL
            { 0030000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_BIT ,"BIT" } },
            { 0130000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_BITB,"BITB" } },
            { 0040000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_BIC ,"BIC" } },
            { 0140000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_BICB,"BICB" } },
            { 0050000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_BIS ,"BIS" } },
            { 0150000, IsaEntry{ PDP11Emulator::Common::I_DoubleOperand, PDP11Emulator::Common::I_BISB,"BISB" } },
        };
        const IsaTable OneAndHalfInstructions = {
                // REGISTER (+3bit for opcode)
            { 0070000, IsaEntry{ PDP11Emulator::Common::I_OneAndHalf, PDP11Emulator::Common::I_MUL , "MUL" } },
            { 0071000, IsaEntry{ PDP11Emulator::Common::I_OneAndHalf, PDP11Emulator::Common::I_DIV , "DIV" } },
            { 0072000, IsaEntry{ PDP11Emulator::Common::I_OneAndHalf, PDP11Emulator::Common::I_ASH , "ASH" } },
            { 0073000, IsaEntry{ PDP11Emulator::Common::I_OneAndHalf, PDP11Emulator::Common::I_ASHC, "ASHC" } },
            { 0074000, IsaEntry{ PDP11Emulator::Common::I_OneAndHalf, PDP11Emulator::Common::I_XOR , "XOR"  } },
        };
        const IsaTable BranchInstructions = {
            /*Program control instructions*/
                //BRANCH
            { 0000400, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BR  , "BR"  } },
            { 0001000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BNE , "BNE" } },
            { 0001400, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BEQ , "BEQ" } },
            { 1000000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BPL , "BPL" } },
            { 1000400, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BMI , "BMI" } },
            { 1020000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BVC , "BVC" } },
            { 1024000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BVS , "BVS" } },
            { 1030400, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BCC , "BCC" } },
            { 1034000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BCS , "BCS" } },
                //Signed Conditional Branch
            { 0002000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BGE,  "BGE" } },
            { 0002400, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BLT,  "BLT" } },
            { 0003000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BGT,  "BGT" } },
            { 0003400, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BLE,  "BLE" } },
                //Unsigned Conditional Branch
            { 0101000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BHI , "BHI" } },
            { 0101400, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BLO , "BLOS" } },
            { 0103000, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BHI , "BHIS" } },
            { 0103400, IsaEntry{ PDP11Emulator::Common::I_Branch, PDP11Emulator::Common::I_BLO , "BLO" } },
        };
        const IsaTable Other = { // TODO: IMPLEMENT IN DECODER
                // Jump & Subroutine
            { 0000100, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_JMP,   "JMP" } },
            { 0004000, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_JSR,   "JSR" } },
            { 0000200, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_RTS,   "RTS" } },
            { 0006400, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_MAR,   "MARK" } },
            { 0077000, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_SOB,   "SOB" } },
                //Trap & Interrupt
            { 0104000, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_EMT,   "EMT" } },
            { 0104400, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_TRAP,  "TRAP" } },
            { 0000003, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_BPT,   "BPT" } },
            { 0000004, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_IOT,   "IOT" } },
            { 0000002, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_RTI,   "RTI" } },
            { 0000006, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_RTT,   "RTT" } },
                //Miscellaneous
            { 0000000, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_HALT,  "HALT" } },
            { 0000001, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_WAIT,  "WAIT" } },
            { 0000005, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_RESET, "RESET" } },
            { 0006500, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_MFPI,  "MFPI" } },
            { 0006600, IsaEntry{ PDP11Emulator::Common::I_Other, PDP11Emulator::Common::I_MTPI,  "MTPI" } },
        };
    };
}
