#include "IRQ_Line.h"
#include "PriorityInterruptController.h"

IRQ_Line::IRQ_Line(PriorityInterruptController& pic, const unsigned int priority)
    : PIC(pic)
    , Priority(priority)
{
}

void IRQ_Line::SetInterrupt(const InterruptType i)
{
    PIC.SetInterrupt(Priority, i);
}