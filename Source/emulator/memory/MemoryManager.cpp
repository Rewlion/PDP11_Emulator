#include "MemoryManager.h"

#include <emulator/common/error.h>

#include <limits>
#include <fstream>

namespace
{
    template<class To, class From> 
    constexpr To As(From& value)
    {
        return reinterpret_cast<To>(value);
    }

    std::streamoff GetFileSize(std::ifstream& file)
    {
        file.seekg(0, std::ios::end);
        const std::streamoff size = file.tellg();
        file.seekg(0, std::ios::beg);

        return size;
    }
}

namespace EmulatorComponents::MemoryManagement
{
    MemoryManager::MemoryManager()
    try : memory_(new byte[getSimulatedMachineMemorySize()])
    {
    }
    catch (std::exception& error)
    {
        throw Common::Error(error.what(), Common::Critical);
    }

    MemoryManager::~MemoryManager() {
        delete[] memory_;
    }

    void MemoryManager::loadProgram(const std::string& fileLocation)
    {
        std::ifstream file(fileLocation, std::ios::binary);
        if (file.is_open() == false)
            throw Common::Error("Unable to open the program", Common::Critical);

        programSize = GetFileSize(file);
        if (programSize > getROMSize())
            throw Common::Error("Unable to load the file: file size is bigger then the ROM's size", Common::Critical);

        file.read(As<char*>(memory_) + getROMBegining(), programSize);
        if (!file)
            throw Common::Error("Unable to successfully read the file with program", Common::Critical);
    }

    byte MemoryManager::getByteAt(const word address) const {
        const byte* mem = memory_ + address;

        return *mem;
    }


    word MemoryManager::getWordAt(const word address) const {
        byte* mem = memory_ + address;

        return *(reinterpret_cast<word*>(mem));
    }

    void MemoryManager::setByteAt(const word relativeAddress, const byte value) const
    {
        byte* const address = memory_ + relativeAddress;
        *address = value;
    }

    void MemoryManager::setWordAt(const word relativeAddress, const word value) const
    {
        byte* const address = memory_ + relativeAddress;
        *(reinterpret_cast<word*>(address)) = value;
    }
}
