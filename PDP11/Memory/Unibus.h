#pragma once

#include <vector>
#include "../Common/Types.h"

class MemoryRegion;

class Unibus
{
public:
    void AddMemoryRegion(MemoryRegion* region);

    Word Read(const Address address);
    void Write(const Address address, const Word value);

private:
    bool DoesRegionOvarlapExistOnes(const MemoryRegion* region) const;
    MemoryRegion* GetMemoryRegion(const Address address);

private:
    std::vector<MemoryRegion*> MemoryRegions;
};