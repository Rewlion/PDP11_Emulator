#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "RegistersModel.h"
#include "RomModel.h"
#include "EmullatorLogModel.h"
#include "QLog.h"
#include <Common/Logs/Logs.h>

#include <QTableView>
#include <QFileDialog>
#include <QLabel>
#include <QKeyEvent>
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<LogType>("LogType");

    auto* logger = dynamic_cast<QLog*>(Logger);
    auto* logModel = new EmullatorLogModel;
    connect(logger, &QLog::OnLog, logModel, &EmullatorLogModel::AddLog);
    auto* logs = findChild<QListView*>("emulatorLog");
    logs->setModel(logModel);

    connect(this, &MainWindow::OnStep, &Emulator, &QEmulator::DoStep);
    connect(this, &MainWindow::OnRun, &Emulator, &QEmulator::DoRun);
    connect(this, &MainWindow::OnProgramUpload, &Emulator, &QEmulator::DoUploadProgram);
    Emulator.Initialize();
    Emulator.moveToThread(&EmulatorThread);
    EmulatorThread.start();

    auto* registers = findChild<QTableView*>("registersView");
    auto* registersModel = new RegistersModel(Emulator);
    registers->setModel(registersModel);
    connect(&Emulator, &QEmulator::UpdateInformation, registersModel, &RegistersModel::DoUpdate);

    auto* rom = findChild<QTableView*>("romView");
    auto* romModel = new RomModel(Emulator);
    rom->setModel(romModel);
    connect(&Emulator, &QEmulator::UpdateInformation, romModel, &RomModel::DoUpdate);

    DumpWidget = new MemoryDumpWidget(Emulator);
    DumpWidget->hide();

    VideoController = new ::VideoController(Emulator);
    connect(VideoController, &::VideoController::UpdateFrame, this, &MainWindow::OnFrameUpdate);
    connect(&VCThread, &QThread::started, VideoController, &::VideoController::Start);
    VideoController->moveToThread(&VCThread);
    VCThread.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    EmulatorThread.terminate();
    VCThread.terminate();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    Emulator.KeyInput(event->key(), InputType::Press);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    Emulator.KeyInput(event->key(), InputType::Release);
}

void MainWindow::OnFrameUpdate(const QImage& img)
{
    auto* display = findChild<QLabel*>("display");
    display->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_actionLoadProgram_triggered()
{
    QString path = QFileDialog::getOpenFileName();
    emit OnProgramUpload(path);
}

void MainWindow::on_stepButton_clicked()
{
    emit OnStep();
}

void MainWindow::on_actionDumpMemory_triggered()
{
    DumpWidget->show();
}

void MainWindow::on_runButton_clicked()
{
    emit OnRun();
}

void MainWindow::on_stopButton_clicked()
{
    Emulator.DoStop();
}
