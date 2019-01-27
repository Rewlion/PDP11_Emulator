#include "DirectMemoryRegion.h"

DirectMemoryRegion::DirectMemoryRegion(const Word addressBegin, const Word size)
    : MemoryRegion(addressBegin, size)
    , Memory(new Byte[size]())
    , AllocatedSize(size)
{
}

DirectMemoryRegion::~DirectMemoryRegion()
{
    delete[] Memory;
}

Word DirectMemoryRegion::Read(const Word address)
{
    const Word localAddress = address - MemoryBeginAddress;
    const Word value = *reinterpret_cast<Word*>(Memory + localAddress);

    return value;
}

void DirectMemoryRegion::Write(const Word address, const Word value)
{
    const Word localAddress = address - MemoryBeginAddress;
    *reinterpret_cast<Word*>(Memory + localAddress) = value;
}

RawRegion DirectMemoryRegion::CopyMemory() const
{
    RawRegion raw;
    raw.Memory = new Byte[AllocatedSize];
    raw.AllocatedSize = AllocatedSize;
    raw.MemoryBegin = GetAddressBegin();

    std::memcpy(raw.Memory, Memory, AllocatedSize);

    return raw;
}