#pragma once

#include "Interrupts.h"

class PriorityInterruptController;

class IRQ_Line
{
public:
    void SetInterrupt(const InterruptType i);

private:
    IRQ_Line(PriorityInterruptController& pic, const unsigned int priority);
    friend class PriorityInterruptController;
private:
    PriorityInterruptController& PIC;
    const unsigned char          Priority;
};