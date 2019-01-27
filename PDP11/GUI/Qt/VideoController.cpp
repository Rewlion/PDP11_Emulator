#include "VideoController.h"

namespace
{
    const int rows = 512;
    const int columns = 512;

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
    QImage img(512,512, QImage::Format::Format_Mono);
    RawRegion rom = Emulator.CopyVRAM();

    for(int x = 0; x < columns; ++x)
        for(int y = 0; y < rows; ++y)
        {
            const int i = Get2D(x,y);
            const int nByte = i / 8;
            const int nBit  = i % 8;
            const uint8_t byte = rom.Memory[nByte];
            const uint8_t value = (byte >> nBit) & 1;
            img.setPixel(x,y, value);
        }

    return img;
}
