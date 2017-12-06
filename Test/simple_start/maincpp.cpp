#include <emulator/emulator.h>

int main(int argc, char** argv)
{
    PDP11::Emulator emulator(argc, argv);
    
    return emulator.exec();
}