#include "WItem.h"
#include <cstdint>  // just in case, for uint32_t

uint32_t WItem::GetID() {
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x150
        );
}

uint32_t WItem::Flag() {
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x1C0
        );
}

CGGuid WItem::GetOwner() {
    return *reinterpret_cast<CGGuid*>(
        reinterpret_cast<uintptr_t>(this) + 0x178
        );
}

uint32_t WItem::Container() {
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x188
        );
}

uint32_t WItem::GetStackCount() {
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x1B8
        );
}

uint32_t WItem::Enchant_ID(){
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x2F4
        );
}

uint32_t WItem::Enchant_Expire(){
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x2F8
        );
}

uint32_t WItem::GetDurability(){
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x1CC
        );
}

uint32_t WItem::GetMaxDurability(){
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x1D0
        );
}

uint32_t WItem::ContainerCount(){
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x470
        );
}

uint32_t WItem::ContainerItems(){
    return *reinterpret_cast<uint32_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x478
        );
}
