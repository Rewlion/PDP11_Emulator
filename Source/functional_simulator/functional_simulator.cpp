#include "functional_simulator.h"

#include <fstream>
#include <exception>
#include <iostream>

namespace
{
    inline word GetPC(const RegistersManagement::RegisterManager& registerManager)
    {
        return registerManager.GetRegister(RegistersManagement::R7);
    }

    inline void SetPC(RegistersManagement::RegisterManager& registerManager, const word value)
    {
        registerManager.SetRegister(RegistersManagement::R7, value);
    }
}

namespace Runtime
{
    Simulator::Simulator(const std::string fileWithProgram)
        : CurrentInstructionsNumber(0)
        , CurrentInstruction(0)
    {
        LoadProgram(fileWithProgram);
    }

    Simulator::Simulator()
        : CurrentInstructionsNumber(0)
        , CurrentInstruction(0)
    {
    }

    void Simulator::LoadProgram(const std::string fileWithProgram)
    {
        std::ifstream file(fileWithProgram, std::ifstream::ate | std::ifstream::binary);
        if (!file.is_open())
            throw std::runtime_error("unable to open the file with program");

        const auto size = file.tellg();
        if (size % sizeof(word))
            throw std::runtime_error("size of loaded program is not multiples of word");

        LoadNewContext(size);

        file.seekg(0, file.beg);
        file.read(reinterpret_cast<char*>(Program.get()), size);

        SetPC(RegistersManager, Program[0]);
    }

    void Simulator::Run()
    {
        for (int i = 0; i < CurrentInstructionsNumber; ++i)
        {
            const word rawInstruction = GetPC(RegistersManager);
            const Common::Instruction instruction = Decoder.Decode(rawInstruction);
            Execute(instruction);
        }
    }

    void Simulator::LoadNewContext(const int sizeInBytes)
    {
        CurrentInstructionsNumber = sizeInBytes / sizeof(word);
        CurrentInstruction = 0;
        Program.reset(new word[sizeInBytes /2]);
    }

    void Simulator::Execute(const Common::Instruction& instruction)
    {

    }
}
