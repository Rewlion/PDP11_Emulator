#include "Qemulator.h"

#include <QtDebug>

QEmulator::QEmulator(QObject *parent) : QObject(parent)
{

}

void QEmulator::DoStep()
{
    if(Step())
        emit UpdateInformation();
}

void QEmulator::DoRun()
{
    Run();
    emit UpdateInformation();
}

void QEmulator::DoStop()
{
    Stop();
}

void QEmulator::DoUploadProgram(const QString& path)
{
    if(UploadProgramToROMFromFile(path.toStdString()))
        emit UpdateInformation();
}
