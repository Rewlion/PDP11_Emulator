#pragma once

#include "../../Memory/MemoryRegion.h"

class Device
{
public:
    virtual MemoryRegion* GetMemoryRegion() { return nullptr; }
    virtual ~Device() {}
};