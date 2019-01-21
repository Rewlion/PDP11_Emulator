#include "Emulator.h"
#include <iostream>

int main()
{
    PDP11::Emulator emulator;
    emulator.UploadProgramToROMFromFile("C:/GitProjects/PDP11_Emulator/PDP11/TestPrograms/pr.m11");
    emulator.Run();
}