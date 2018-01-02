#include "emulator.h"

#include <thirdparty/Qt/QtCore/qobject.h>

namespace PDP11
{
    Emulator::Emulator(int argc, char** argv)
        : Application(argc, argv)
    {
        qRegisterMetaType<word>("word");
        qRegisterMetaType<size_t>("size_t");
        qRegisterMetaType<byte*>("byte*");
        qRegisterMetaType<EmulatorComponents::RegistersManagement::RegisterManager>("EmulatorComponents::RegistersManagement::RegisterManager");

        Cpu.moveToThread(&CpuThread);

        QObject::connect(&Gui, SIGNAL(PDP11ProgramFileChanged(QString)), &Cpu, SLOT(LoadProgram(QString)));
        QObject::connect(Gui.StepButton, SIGNAL(pressed()), &Cpu, SLOT(Step()));
        QObject::connect(Gui.RunButton, SIGNAL(pressed()), &Cpu, SLOT(Run()));
        QObject::connect(Gui.StopButton, SIGNAL(pressed()), &Cpu, SLOT(Stop()), Qt::DirectConnection);
        QObject::connect(&Gui, &EmulatorComponents::Gui::PCChanged, &Cpu, &EmulatorComponents::Cpu::SetPC);
        QObject::connect(&Cpu, &EmulatorComponents::Cpu::RegistersContextUpdated, &Gui, &EmulatorComponents::Gui::UpdateRegistersContext);
        QObject::connect(&Cpu, &EmulatorComponents::Cpu::ProgramLoaded, &Gui, &EmulatorComponents::Gui::UpdateMemoryContext);

        CpuThread.start();
    }
}
