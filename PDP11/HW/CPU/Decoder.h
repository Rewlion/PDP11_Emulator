#pragma once

#include "../../Common/Instruction.h"

#include <map>

typedef InstructionMeta IsaEntry;
typedef std::map<Word, IsaEntry> IsaTable;

class Decoder
{
public:
    Decoder() = default;
    Instruction Decode(const Word raw) const;

private:
    inline bool       IsDoubleOperandInstruction(const Word raw) const;
    inline bool       IsOneAndHalfInstruction(const Word raw) const;
    inline bool       IsSingleOperandInstruction(const Word raw) const;
    inline bool       IsBranchInstruction(const Word raw) const;
    InstructionGroup  GetInstructionGroup(const Word raw) const;

    Instruction       ConstructDoubleOperandInstruction(const Word raw) const;
    Instruction       ConstructOneAndHalfInstruction(const Word raw) const;
    Instruction       ConstructSingleOperandInstruction(const Word raw) const;
    Instruction       ConstructBranchInstruction(const Word raw) const;

private:
    const IsaTable SingleOperandInstructions = {
        /*Single operand instructions*/
        //GENERAL
        { 0005000, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_CLR, "CLR" } },
        { 0105000, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_CLRB, "CLRB" } },
        { 0005100, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_COM, "COM" } },
        { 0105100, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_COMB, "COMB" } },
        { 0005200, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_INC, "INC" } },
        { 0105200, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_INCB, "INCB" } },
        { 0005300, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_DEC, "DEC" } },
        { 0105300, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_DECB, "DECB" } },
        { 0005400, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_NEG, "NEG" } },
        { 0105400, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_NEGB, "NEGB" } },
        { 0005700, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_TST, "TST" } },
        { 0105700, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_TSTB, "TSTB" } },
        //SHIFT&ROTATE
        { 0006200, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ASR, "ASR" } },
        { 0106200, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ASRB, "ASRB" } },
        { 0006300, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ASL, "ASL" } },
        { 0106300, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ASLB, "ASLB" } },
        { 0006000, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ROR, "ROR" } },
        { 0106000, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_RORB, "RORB" } },
        { 0006100, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ROL, "ROL" } },
        { 0106100, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ROLB, "ROLB" } },
        { 0000300, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_SWAB, "SWAB" } },
        //MULTIPLE PRECISION
        { 0005500, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ADC, "ADC" } },
        { 0105500, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_ADCB, "ADCB" } },
        { 0005600, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_SBC, "SBC" } },
        { 0105600, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_SBCB, "SBCB" } },
        { 0006700, IsaEntry{ InstructionGroup::I_SingleOperand, InstructionType::I_SXT, "SXT" } },
        //JUMPS
        { 0000100, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_JMP, "JMP" } },
        };
    const IsaTable DoubleOperandInstructions = {
        /*Double operand instructions*/
        //GENERAL
        { 0010000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_MOV ,"MOV" } },
        { 0110000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_MOVB,"MOVB" } },
        { 0020000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_CMP ,"CMP" } },
        { 0120000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_CMPB,"CMPB" } },
        { 0060000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_ADD ,"ADD" } },
        { 0160000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_SUB ,"SUB" } },
        //LOGICAL
        { 0030000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_BIT ,"BIT" } },
        { 0130000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_BITB,"BITB" } },
        { 0040000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_BIC ,"BIC" } },
        { 0140000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_BICB,"BICB" } },
        { 0050000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_BIS ,"BIS" } },
        { 0150000, IsaEntry{ InstructionGroup::I_DoubleOperand, InstructionType::I_BISB,"BISB" } },
    };
    const IsaTable OneAndHalfInstructions = {
        // REGISTER (+3bit for opcode)
        { 0070000, IsaEntry{ InstructionGroup::I_OneAndHalf,    InstructionType::I_MUL , "MUL" } },
        { 0071000, IsaEntry{ InstructionGroup::I_OneAndHalf,    InstructionType::I_DIV , "DIV" } },
        { 0072000, IsaEntry{ InstructionGroup::I_OneAndHalf,    InstructionType::I_ASH , "ASH" } },
        { 0073000, IsaEntry{ InstructionGroup::I_OneAndHalf,    InstructionType::I_ASHC, "ASHC" } },
        { 0074000, IsaEntry{ InstructionGroup::I_OneAndHalf,    InstructionType::I_XOR , "XOR" } },
    };
    const IsaTable BranchInstructions = {
        /*Program control instructions*/
        //BRANCH
        { 0000400, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BR  , "BR" } },
        { 0001000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BNE , "BNE" } },
        { 0001400, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BEQ , "BEQ" } },
        { 1000000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BPL , "BPL" } },
        { 1000400, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BMI , "BMI" } },
        { 1020000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BVC , "BVC" } },
        { 1024000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BVS , "BVS" } },
        { 1030400, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BCC , "BCC" } },
        { 1034000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BCS , "BCS" } },
        //Signed Conditional Branch
        { 0002000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BGE,  "BGE" } },
        { 0002400, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BLT,  "BLT" } },
        { 0003000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BGT,  "BGT" } },
        { 0003400, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BLE,  "BLE" } },
        //Unsigned Conditional Branch
        { 0101000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BHI , "BHI" } },
        { 0101400, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BLO , "BLOS" } },
        { 0103000, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BHI , "BHIS" } },
        { 0103400, IsaEntry{ InstructionGroup::I_Branch,        InstructionType::I_BLO , "BLO" } },
    };
    const IsaTable Other = { // TODO: IMPLEMENT IN DECODER
                             // Jump & Subroutine
        { 0004000, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_JSR,   "JSR" } },
        { 0000200, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_RTS,   "RTS" } },
        { 0006400, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_MAR,   "MARK" } },
        { 0077000, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_SOB,   "SOB" } },
        //Trap & Interrupt
        { 0104000, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_EMT,   "EMT" } },
        { 0104400, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_TRAP,  "TRAP" } },
        { 0000003, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_BPT,   "BPT" } },
        { 0000004, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_IOT,   "IOT" } },
        { 0000002, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_RTI,   "RTI" } },
        { 0000006, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_RTT,   "RTT" } },
        //Miscellaneous
        { 0000000, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_HALT,  "HALT" } },
        { 0000001, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_WAIT,  "WAIT" } },
        { 0000005, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_RESET, "RESET" } },
        { 0006500, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_MFPI,  "MFPI" } },
        { 0006600, IsaEntry{ InstructionGroup::I_Other,         InstructionType::I_MTPI,  "MTPI" } },
    };
};