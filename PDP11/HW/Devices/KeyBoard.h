#pragma once

#include "Device.h"
#include "Input.h"
#include "../../Memory/MemoryRegion.h"
#include "../../Memory/MemoryRegionInformation.h"
#include "../PIC/IRQ_Line.h"

constexpr Word GetKeyBoardBegining() { return GetIOBegining(); }
constexpr size_t GetKeyBoardSize()   { return 2 * sizeof(Word); }

class KeyBoard : public Device
{
public:
    KeyBoard(IRQ_Line irq_line);

    virtual MemoryRegion* GetMemoryRegion() override;

    void OnKeyInput(const unsigned int key, const InputType status);

private:
    class KeyBoardMemoryRegion : public MemoryRegion
    {
    public:
        KeyBoardMemoryRegion(KeyBoard& kb);

        virtual Word Read(const Word address);
        virtual void Write(const Word address, const Word value);

    private:
        KeyBoard& KB;
    };
    friend KeyBoardMemoryRegion;

private:
    IRQ_Line              IRQ;
    KeyBoardMemoryRegion* Region;
    Word                  Key;
    Word                  Status;
};