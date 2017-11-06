#include <functional_simulator/functional_simulator.h>

int main()
{
    Runtime::Simulator pdp11;
    pdp11.LoadProgram("program.txt");
    pdp11.Run();
}