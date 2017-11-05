#pragma once

#include <functional_simulator/Common/types.h>
#include <functional_simulator/Common/instruction.h>

#include <map>

namespace Decoding
{
    typedef word opcode;

    typedef Common::InstructionMeta IsaEntry;
    typedef std::map<opcode, IsaEntry> IsaTable;	
}
