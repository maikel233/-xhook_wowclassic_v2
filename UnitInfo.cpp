#include "UnitInfo.h"

// GetType at offset 0x30
uint32_t UnitInfo::GetType()
{
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x30
        );
}

// GetFamily at offset 0x34
uint32_t UnitInfo::GetFamily()
{
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x34
        );
}

// GetUnitRank at offset 0x38
uint32_t UnitInfo::GetUnitRank()
{
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x38
        );
}

// GetName at offset 0xF8
char* UnitInfo::GetName()
{
    // If the macro originally returned a reference to char*, that effectively means
    // "return *reinterpret_cast<char**>". So we do that explicitly here:
    return *reinterpret_cast<char**>(
        reinterpret_cast<uintptr_t>(this) + 0xF8
        );
}

// GetGatherType at offset 0xE8
uint32_t UnitInfo::GetGatherType()
{
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0xE8
        );
}
