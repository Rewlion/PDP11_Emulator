#pragma once

#include <emulator/common/instruction.h>
#include <emulator/common/types.h>
#include <emulator/cpu/decoder.h>
#include <emulator/cpu/RegisterManager.h>
#include <emulator/memory/MemoryManager.h>

#include <thirdparty/Qt/QtCore/qobject.h>

#include <atomic>
#include <string>
#include <memory>

namespace EmulatorComponents
{
    struct Context
    {
        RegistersManagement::RegisterManager registers;
    };

    class Cpu : public QObject
    {
       Q_OBJECT
    public slots:
        void Step();
        void Run();
        void Stop();
        void SetPC(const word startAddress);
        void LoadProgram(const QString& fileLocation);
    signals:
        void RegistersContextUpdated(EmulatorComponents::RegistersManagement::RegisterManager context);
        void ProgramLoaded(byte* memory, size_t size);
    public:
        Cpu();
    private:
        void Execute(const Common::Instruction& instruction);
    private:
        MemoryManagement::MemoryManager Memory;
        Decoding::Decoder Decoder;
        RegistersManagement::RegisterManager RegistersManager;

        std::atomic_bool IsExecutionOver;
    };
}
