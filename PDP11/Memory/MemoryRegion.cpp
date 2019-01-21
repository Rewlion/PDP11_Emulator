#include "MemoryRegion.h"

MemoryRegion::MemoryRegion(const Word addressBegin, const Word size)
    : MemoryBeginAddress(addressBegin)
    , Size(size)
{
}