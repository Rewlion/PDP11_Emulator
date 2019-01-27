#ifndef VIDEOCONTROLLER_H
#define VIDEOCONTROLLER_H

#include <QObject>
#include "Qemulator.h"
#include <QImage>

class VideoController : public QObject
{
    Q_OBJECT
public:
    explicit VideoController(const QEmulator& emulator, QObject *parent = nullptr);

signals:
    void UpdateFrame(const QImage& frame);

public slots:
    void Start();

private:
    QImage ConstructFrame();
private:
    const QEmulator& Emulator;
};

#endif // VIDEOCONTROLLER_H
