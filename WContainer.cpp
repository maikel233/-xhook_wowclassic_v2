#include "WContainer.h"

int WContainer::GetSlots()
{
    return *reinterpret_cast<int*>(
        reinterpret_cast<uintptr_t>(this) + 0x470
        );
}

CGGuid WContainer::GetSlotById(int ID)
{
#if Logger
    Utils::logger("start");
#endif

    auto res = *reinterpret_cast<CGGuid*>(
        reinterpret_cast<uintptr_t>(this) + 0x478 + (ID * 0x10)
        );

#if Logger
    Utils::logger("end");
#endif
    return res;
}
