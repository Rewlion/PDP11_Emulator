#pragma once

#include "MemoryRegion.h"
#include "RawRegion.h"

#include <vector>

class DirectMemoryRegion final: public MemoryRegion
{
public:
    DirectMemoryRegion(const Word addressBegin, const Word size);
    ~DirectMemoryRegion();

    virtual Word Read(const Word address) override;
    virtual void Write(const Word address, const Word value) override;

    RawRegion CopyMemory() const;

private:
    Byte* Memory;
    Word  AllocatedSize;
};