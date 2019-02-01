#include "VideoController.h"

namespace
{
    const int rows = 128;
    const int columns = 128;

    int Get2D(const int x, const int y)
    {
        return x + y * columns;
    }
}

VideoController::VideoController(const QEmulator& emulator, QObject *parent)
    : QObject(parent)
    , Emulator(emulator)
{

}


void VideoController::Start()
{
    const float v = 60;
    const float t = 1/v;

    auto t1 = std::chrono::system_clock::now();
    while(true)
    {
        const auto t2 = std::chrono::system_clock::now();
        const std::chrono::duration<double> dt = t2 - t1;
        if(dt.count() > t)
        {
            QImage frame = ConstructFrame();
            emit UpdateFrame(frame);
            t1 = t2;
        }
    }
}

QImage VideoController::ConstructFrame()
{
    QImage img(columns,rows, QImage::Format::Format_Mono);
    RawRegion rom = Emulator.CopyVRAM();

    for(int x = 0; x < columns; ++x)
        for(int y = 0; y < rows; ++y)
        {
            const int i = Get2D(x,y);
            const uint8_t value = rom.Memory[i];
            img.setPixel(x,y, value);
        }

    delete rom.Memory;

    return img;
}
