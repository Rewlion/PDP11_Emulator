#pragma once

#include "memorylistmodel.h"
#include "registerslistmodel.h"
#include "flagslistmodel.h"

#include <emulator/cpu/cpu.h>
#include <emulator/common/types.h>

#include <thirdparty/Qt/QtCore/qobject.h>
#include <thirdparty/Qt/QtWidgets/qwidget.h>
#include <thirdparty/Qt/QtWidgets/qlabel.h>
#include <thirdparty/Qt/QtWidgets/qlistview.h>
#include <thirdparty/Qt/QtWidgets/qboxlayout.h>
#include <thirdparty/Qt/QtWidgets/qmenu.h>
#include <thirdparty/Qt/QtWidgets/qmenubar.h>
#include <thirdparty/Qt/QtWidgets/qaction.h>
#include <thirdparty/Qt/QtWidgets/qpushbutton.h>
#include <thirdparty/Qt/QtWidgets/qlineedit.h>
#include <thirdparty/Qt/QtWidgets/qformlayout.h>

#include <memory>

namespace EmulatorComponents
{
    class Gui : public QWidget
    {
        Q_OBJECT
    public slots:
        void UpdateRegistersContext(const RegistersManagement::RegisterManager context);
        void UpdateMemoryContext(byte* memory, size_t allocatedMemory);

    signals:
        void PCChanged(const word address);
        void PDP11ProgramFileChanged(const QString& fileLocation);

    public:
        Gui();

    public:
        QPushButton* StepButton;
        QPushButton* RunButton;
        QPushButton* StopButton;
        QPushButton* SetPCButton;

    private slots:
        void SendNewPC();
        void GetPDP11ProgramfileLocation(bool checked); //TODO rename to get form input
    private:
        QFormLayout* ConstructSetPCLayout();
        void InitializeToolBar();
        void InitializePushButtons();
        QHBoxLayout* ConstructVideoMemoryOutputLayer();
        QHBoxLayout* ConstructCpuButtonLayer();
        QWidget* ConstructFirstColumn();
        QWidget* ConstructSecondColumn();
        void PlaceWidgets();

    private:
        QMenuBar* MenuBar;
        QLabel* VideoMemoryOutput;
        QLineEdit* SetPCLineEdit;
        QListView* MemoryView;

        QListView* RegistersView;
        QListView* FlagsView;
    };
}