#pragma once

#include "../Common/Types.h"

#include <string>

class MemoryRegion
{
public:
    MemoryRegion(const Word addressBegin, const Word size);

    virtual Word Read(const Word address) = 0;
    virtual void Write(const Word address, const Word value) = 0;

    inline Word GetAddressBegin() const;
    inline Word GetSize() const;

protected:
    const Word MemoryBeginAddress;
    const Word Size;

};

Word MemoryRegion::GetAddressBegin() const
{
    return MemoryBeginAddress;
}

Word MemoryRegion::GetSize() const
{
    return Size;
}