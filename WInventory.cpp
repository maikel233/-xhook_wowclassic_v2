#include "WInventory.h"

#ifdef Logger
#include "Utils.h"
#endif

// Implementation of WInventory methods

CGGuid WInventory::GetBagByID(int ID)
{
#if Logger
    Utils::logger("start");
#endif

    // This reads a CGGuid from (this + 0x1F0 + (ID * 0x10))   
    auto res = *reinterpret_cast<CGGuid*>(
        reinterpret_cast<uintptr_t>(this) + 0x1F0 + (ID * 0x10)
        );

#if Logger
    Utils::logger("end");
#endif
    return res;
}

CGGuid WInventory::GetBackPackSlotByID(int ID)
{
#if Logger
    Utils::logger("start");
#endif

    // Reads CGGuid from (this + 0x240 + (ID * 0x10))
    auto res = *reinterpret_cast<CGGuid*>(
        reinterpret_cast<uintptr_t>(this) + 0x240 + (ID * 0x10)
        );

#if Logger
    Utils::logger("end");
#endif
    return res;
}

CGGuid WInventory::GetEquipmentSlotByID(int ID)
{
#if Logger
    Utils::logger("start");
#endif

    // Reads CGGuid from (this + 0x10 + (ID * 0x10))
    auto res = *reinterpret_cast<CGGuid*>(
        reinterpret_cast<uintptr_t>(this) + 0x10 + (ID * 0x10)
        );

#if Logger
    Utils::logger("end");
#endif
    return res;
}
