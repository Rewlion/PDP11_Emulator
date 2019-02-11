#include "KeyBoard.h"
#include "../PIC/Interrupts.h"

KeyBoard::KeyBoardMemoryRegion::KeyBoardMemoryRegion(KeyBoard& kb)
    : MemoryRegion(GetKeyBoardBegining(), GetKeyBoardSize())
    , KB(kb)
{
}

Word KeyBoard::KeyBoardMemoryRegion::Read(const Word address)
{
    const Word localAddress = address - MemoryBeginAddress;
    if (localAddress == 0)
        return KB.Key;
    if (localAddress == sizeof(Word))
        return KB.Status;

    return 0;
}

void KeyBoard::KeyBoardMemoryRegion::Write(const Word address, const Word value)
{
    return;
}

KeyBoard::KeyBoard(IRQ_Line irq_line)
    : Region(new KeyBoardMemoryRegion(*this))
    , Key(0)
    , Status(0)
    , IRQ(irq_line)
{
}

MemoryRegion* KeyBoard::GetMemoryRegion()
{
    return Region;
}

void KeyBoard::OnKeyInput(const unsigned int key, const InputType status)
{
    Key = key;
    Status = static_cast<Word>(status);

    IRQ.SetInterrupt(InterruptType::KeyBoard);
}