#ifndef QEMULATOR_H
#define QEMULATOR_H

#include <QObject>
#include <Emulator.h>

class QEmulator : public QObject, public Emulator
{
    Q_OBJECT
public:
    explicit QEmulator(QObject *parent = nullptr);

signals:
    void UpdateInformation();

public slots:
    void DoStep();
    void DoUploadProgram(const QString& path);
};

#endif // QEMULATOR_H
