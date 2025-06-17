#include "ItemCacheEntry.h"
#include <cstdint>  // For uint16_t, uint32_t

uint16_t ItemCacheEntry::GetQuality(){
    return *reinterpret_cast<uint16_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x185
        );
}

// offset 0x48
char* ItemCacheEntry::GetName(){
    return *reinterpret_cast<char**>(
        reinterpret_cast<uintptr_t>(this) + 0x48
        );
}

// offset 0xD0
uint32_t ItemCacheEntry::GetSellPrice() {
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0xD0
        );
}
