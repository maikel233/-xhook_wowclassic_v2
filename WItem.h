#pragma once

#include <cstdint>
#include "WObject.h"   // so we can inherit from WObject
#include "Constants.h"

class WItem : public WObject
{
public:
    uint32_t GetID();
    uint32_t Flag();
    CGGuid   GetOwner();
    uint32_t Container();
    uint32_t GetStackCount();
    uint32_t Enchant_ID();
    uint32_t Enchant_Expire();
    uint32_t GetDurability();
    uint32_t GetMaxDurability();
    uint32_t ContainerCount();
    uint32_t ContainerItems();
};
