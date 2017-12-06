#pragma once

#include <emulator/cpu/cpu.h>
#include <emulator/gui/gui.h>

#include <thirdparty/Qt/QtCore/qthread.h>
#include <thirdparty/Qt/QtWidgets/qapplication.h>

#include <memory>
#include <string>

namespace PDP11
{
    class Emulator
    {
    public:
        Emulator(int argc, char** argv);
        inline int exec() { return Application.exec(); }
    private:
        QApplication Application;

        QThread CpuThread;
        EmulatorComponents::Cpu Cpu;
        EmulatorComponents::Gui Gui;
    };
}
