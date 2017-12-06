#include "gui.h"

#include <emulator/common/error.h>

#include <thirdparty/Qt/QtGui/qimage.h>
#include <thirdparty/Qt/QtGui/qpixmap.h>
#include <thirdparty/Qt/QtCore/qdebug.h>
#include <thirdparty/Qt/QtCore/qthread.h>
#include <thirdparty/Qt/QtWidgets/qfiledialog.h>

namespace EmulatorComponents 
{
    namespace
    {
        constexpr unsigned int GetVMOutputSize()
        {
            return 512;
        }
    }

    Gui::Gui()
        : StepButton(new QPushButton("Step"))
        , RunButton(nullptr)
        , StopButton(nullptr)
        , SetPCButton(nullptr)
        , MenuBar(nullptr)
        , VideoMemoryOutput(nullptr)
        , SetPCLineEdit(nullptr)
        , MemoryView(nullptr)
        , FlagsView(nullptr)
    {
        InitializeToolBar();
        InitializePushButtons();
        PlaceWidgets();
        setFixedSize(800, 600);
        show();
    }

    void Gui::SendNewPC()
    {
        const word newAddress = SetPCLineEdit->text().toULongLong(nullptr, 0);
        qDebug() << "sending new PC:" << newAddress;

        emit PCChanged(newAddress);
    }

    void Gui::GetPDP11ProgramfileLocation(bool checked)
    {
        const QString fileLocation = QFileDialog::getOpenFileName(this, QString::fromUtf8("PDP11 program"), "*");
        qDebug() << QString("selected pdp 11 program is located in '%1'").arg(fileLocation);
        qDebug() << "Gui thread:" << QThread::currentThreadId() << " " << "Stop";

        MemoryView->setModel(new Qt::Widgets::MemoryListModel());

        emit PDP11ProgramFileChanged(fileLocation);
    }

    void Gui::InitializeToolBar()
    {
        MenuBar = new QMenuBar();
        QMenu* const Menu = MenuBar->addMenu("File");
        QAction* const loadFileAction = new QAction("Load Program");
        
        Menu->addAction(loadFileAction);
        MenuBar->setFixedHeight(Menu->height());

        connect(loadFileAction, SIGNAL(triggered(bool)), this, SLOT(GetPDP11ProgramfileLocation(bool)));
    }

    QFormLayout* Gui::ConstructSetPCLayout()
    {
        SetPCLineEdit = new QLineEdit();
        connect(SetPCButton, SIGNAL(pressed()), this, SLOT(SendNewPC()));

        QFormLayout* const formLayout = new QFormLayout;
        formLayout->addRow(SetPCButton, SetPCLineEdit);

        return formLayout;
    }

    QHBoxLayout* Gui::ConstructVideoMemoryOutputLayer()
    {
        VideoMemoryOutput = new QLabel();
        QImage img(GetVMOutputSize(), GetVMOutputSize(), QImage::Format_Mono);
        img.fill(Qt::white);
        VideoMemoryOutput->setPixmap(QPixmap::fromImage(img));
        
        QHBoxLayout* const videoMemoryOutputLayer = new QHBoxLayout();
        videoMemoryOutputLayer->addWidget(VideoMemoryOutput);

        return videoMemoryOutputLayer;
    }

    void Gui::InitializePushButtons()
    {
        StepButton = new QPushButton("Step");
        StepButton->setFixedWidth(GetVMOutputSize() / 4);

        RunButton = new QPushButton("Run");
        RunButton->setFixedWidth(GetVMOutputSize() / 4);

        StopButton = new QPushButton("Stop");
        StopButton->setFixedWidth(GetVMOutputSize() / 4);

        SetPCButton = new QPushButton("Set PC");
        SetPCButton->setFixedWidth(GetVMOutputSize() / 4);
    }

    QHBoxLayout* Gui::ConstructCpuButtonLayer()
    {
        QHBoxLayout* const layer = new QHBoxLayout();
        layer->addWidget(StepButton);
        layer->addWidget(RunButton);
        layer->addWidget(StopButton);

        return layer;
    }

    QWidget* Gui::ConstructFirstColumn()
    {
        QVBoxLayout* const firstColumnLayer = new QVBoxLayout();

        firstColumnLayer->addWidget(MenuBar);
        firstColumnLayer->setAlignment(MenuBar, Qt::AlignTop);

        QHBoxLayout* const videoMemoryOutputLayer = ConstructVideoMemoryOutputLayer();
        firstColumnLayer->addLayout(videoMemoryOutputLayer);
        firstColumnLayer->setAlignment(videoMemoryOutputLayer, Qt::AlignTop);

        QHBoxLayout* const cpuButtonsLayer = ConstructCpuButtonLayer();
        firstColumnLayer->addLayout(cpuButtonsLayer);
        firstColumnLayer->setAlignment(cpuButtonsLayer, Qt::AlignTop);

        QFormLayout* const setPCLayout = ConstructSetPCLayout();
        firstColumnLayer->addLayout(setPCLayout);
        firstColumnLayer->setAlignment(setPCLayout, Qt::AlignTop);

        MemoryView = new QListView();
        MemoryView->setModel(new Qt::Widgets::MemoryListModel());
        firstColumnLayer->addWidget(MemoryView);
        firstColumnLayer->setAlignment(MemoryView, Qt::AlignTop);

        QWidget* const firstColumn = new QWidget();
        firstColumn->setMaximumWidth(GetVMOutputSize());
        firstColumn->setLayout(firstColumnLayer);

        return firstColumn;
    }

    QWidget* Gui::ConstructSecondColumn()
    {
        QVBoxLayout* const secondColumnLayout = new QVBoxLayout();

        RegistersView = new QListView();
        RegistersView->setModel(new Qt::Widgets::RegistersListModel(RegistersView));
        secondColumnLayout->addWidget(RegistersView);

        FlagsView = new QListView();
        FlagsView->setModel(new Qt::Widgets::FlagsListModel(FlagsView));
        secondColumnLayout->addWidget(FlagsView);

        QWidget* secondColumn = new QWidget();
        secondColumn->setFixedWidth(GetVMOutputSize() / 4);
        secondColumn->setFixedHeight(GetVMOutputSize() / 2);
        secondColumn->setLayout(secondColumnLayout);

        return secondColumn;
    }

    void Gui::PlaceWidgets()
    {
        QHBoxLayout* mainWindowLayout = new QHBoxLayout();

        QWidget* firstColumn = ConstructFirstColumn();
        mainWindowLayout->addWidget(firstColumn);
        mainWindowLayout->setAlignment(firstColumn, Qt::AlignLeft);

        QWidget* secondColumn = ConstructSecondColumn();
        mainWindowLayout->addWidget(secondColumn);
        mainWindowLayout->setAlignment(secondColumn, Qt::AlignLeft);

        setLayout(mainWindowLayout);
    }

    void Gui::UpdateRegistersContext(const RegistersManagement::RegisterManager context)
    {
        qDebug() << "Gui is going to update registers context.";

        auto* const registersModel = new Qt::Widgets::RegistersListModel();
        registersModel->SetRegisterManager(context);
        RegistersView->setModel(registersModel);

        auto* const flagsModel = new Qt::Widgets::FlagsListModel();
        flagsModel->SetFlags(context.GetFlagRegister());
        FlagsView->setModel(flagsModel);
    }

    void Gui::UpdateMemoryContext(byte* memory, size_t allocatedMemory)
    {
        qDebug() << "Gui is going to update memory context.";

        auto* const memoryModel = new Qt::Widgets::MemoryListModel();
        memoryModel->SetMemoryPointer(memory, allocatedMemory);
        MemoryView->setModel(memoryModel);
    }
}