#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Qemulator.h"
#include <QThread>
#include "MemoryDumpWidget.h"
#include "VideoController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void OnStep();
    void OnRun();
    void OnStop();
    void OnProgramUpload(const QString& path);

private slots:
    void OnFrameUpdate(const QImage& img);

    void on_actionLoadProgram_triggered();

    void on_stepButton_clicked();

    void on_actionDumpMemory_triggered();

    void on_runButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::MainWindow*       ui;
    MemoryDumpWidget*     DumpWidget;
    QEmulator             Emulator;
    QThread               EmulatorThread;
    VideoController*      VideoController;
    QThread               VCThread;
};

#endif // MAINWINDOW_H
