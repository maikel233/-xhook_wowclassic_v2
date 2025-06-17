#pragma once

#include <cstdint>

struct ItemCacheEntry
{
public:
    uint16_t GetQuality();
    char* GetName();
    uint32_t GetSellPrice();
};
