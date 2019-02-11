#include "PriorityInterruptController.h"
#include "../../Memory/MemoryRegionInformation.h"

void PriorityInterruptController::SetInterrupt(const unsigned int priority, const InterruptType i)
{
    assert(priority < GetIRQLinesCount());
    std::lock_guard<std::mutex> lg(QueuesMutex);

    InterruptQueue& q = Queues[priority];
    const Word handler = static_cast<Word>(i) * sizeof(Word);
    q.push(InterruptVector{ handler });
}

std::optional<InterruptVector> PriorityInterruptController::GetInterrupt(const unsigned int priority)
{
    assert(priority < GetIRQLinesCount());
    if (priority != 0)
    {
        std::lock_guard<std::mutex> lg(QueuesMutex);

        for (int i = priority-1; i >= 0; --i)
        {
            InterruptQueue& q = Queues[i];
            if (q.empty() == false)
            {
                InterruptVector v = q.front();
                q.pop();

                return v;
            }
        }
    }

    return std::nullopt;
}

void PriorityInterruptController::Reset()
{
    for (InterruptQueue& q : Queues)
    {
        InterruptQueue empty;
        q.swap(empty);
    }
}