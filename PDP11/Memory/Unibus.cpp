#include "Unibus.h"
#include "MemoryRegion.h"

//#include "../Common/Exceptions/Error.h"
#include <assert.h>
#include <iostream>

void Unibus::AddMemoryRegion(MemoryRegion* region)
{
    //CHECK(DoesRegionOvarlapExistOnes(region) == false, std::string("Cannot add a new region: overlaps the exist one"));
    assert(DoesRegionOvarlapExistOnes(region) == false);
    MemoryRegions.push_back(region);
}

bool Unibus::DoesRegionOvarlapExistOnes(const MemoryRegion* region) const
{
    for (MemoryRegion* existRegion : MemoryRegions)
    {
        const Word n1 = region->GetAddressBegin();
        const Word n2 = n1 + region->GetSize();
        const Word e1 = existRegion->GetAddressBegin();
        const Word e2 = e1 + existRegion->GetSize();

        if ((e1 < n2) && (n1 < e2))
            return true;
    }

    return false;
}

MemoryRegion* Unibus::GetMemoryRegion(const Address address)
{
    for (MemoryRegion* region : MemoryRegions)
    {
        const DWord regionBegin = region->GetAddressBegin();
        const DWord regionEnd = regionBegin + region->GetSize();
        
        if ((address >= regionBegin) && (address < regionEnd))
            return region;
    }

    //throw Common::Error(DBG_LINE, "Region for address doesn't exist", Common::Critical);
    assert(!"Region for address doesn't exist");
}

Word Unibus::Read(const Address address)
{
    MemoryRegion* region = GetMemoryRegion(address);
    const Word data = region->Read(address);

    return data;
}

void Unibus::Write(const Address address, const Word value)
{
    MemoryRegion* region = GetMemoryRegion(address);
    region->Write(address, value);
}