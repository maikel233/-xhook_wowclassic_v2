#pragma once

#include <cstdint>

class UnitInfo
{
public:
    //   0x30 -> GetType
    //   0x34 -> GetFamily
    //   0x38 -> GetUnitRank
    //   0xF8 -> GetName (char pointer)
    //   0xE8 -> GetGatherType

    uint32_t GetType();
    uint32_t GetFamily();
    uint32_t GetUnitRank();
    char* GetName();      
    uint32_t GetGatherType();
};
