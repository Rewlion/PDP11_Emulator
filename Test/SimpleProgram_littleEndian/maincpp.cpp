#include <emulator/cpu/cpu.h>

int main()
{
    EmulatorComponents::Cpu pdp11;
    pdp11.LoadProgram("program.txt");
    pdp11.Run();
}