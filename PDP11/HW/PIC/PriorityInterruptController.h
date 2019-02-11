#pragma once

#include "IRQ_Line.h"
#include "InterruptVector.h"
#include "Interrupts.h"

#include <assert.h>
#include <array>
#include <queue>
#include <mutex>
#include <optional>

constexpr unsigned int GetIRQLinesCount()
{
    return 8;
}

class PriorityInterruptController
{
public:
    void                           SetInterrupt(const unsigned int priority, const InterruptType i);
    std::optional<InterruptVector> GetInterrupt(const unsigned int priority);

    inline IRQ_Line                GetIRQLine(const unsigned int priority);

    void                           Reset();

private:
    typedef std::queue<InterruptVector> InterruptQueue;
    typedef std::array<InterruptQueue, GetIRQLinesCount()> InterruptQueues;

private:
    InterruptQueues Queues;
    std::mutex      QueuesMutex;
};

IRQ_Line PriorityInterruptController::GetIRQLine(const unsigned int priority)
{
    assert(priority <= GetIRQLinesCount(), "Wrong priority.");

    return IRQ_Line(*this, priority);
}

