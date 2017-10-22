#pragma once

#include <Common/types.h>
#include <Common/instruction.h>

#include <map>

namespace PDP11Emulator::Decoding
{
    typedef uint16 opcode;

    typedef PDP11Emulator::Common::InstructionMeta IsaEntry;
    typedef std::map<opcode, IsaEntry> IsaTable;	
}
