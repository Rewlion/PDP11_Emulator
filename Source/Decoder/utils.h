#pragma once

#include <Common/types.h>
#include <Common/instruction.h>

#include <map>

namespace Decoding
{
    typedef word opcode;

    typedef Common::InstructionMeta IsaEntry;
    typedef std::map<opcode, IsaEntry> IsaTable;	
}
