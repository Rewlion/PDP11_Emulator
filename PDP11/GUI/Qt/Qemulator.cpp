#include "Qemulator.h"

#include <QtDebug>

QEmulator::QEmulator(QObject *parent) : QObject(parent)
{

}

void QEmulator::DoStep()
{
    if(Step());
        emit UpdateInformation();
}

void QEmulator::DoUploadProgram(const QString& path)
{
    if(UploadProgramToROMFromFile(path.toStdString()))
        emit UpdateInformation();
}
