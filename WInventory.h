#pragma once
#include "Utils/Vector.h"
#include "Constants.h"

class CGGuid; // Forward declaration of CGGuid

class WInventory
{
public:
    // Returns a CGGuid representing the bag at index 'ID'
    CGGuid GetBagByID(int ID);

    // Returns a CGGuid for a backpack slot
    CGGuid GetBackPackSlotByID(int ID);

    // Returns a CGGuid for an equipment slot
    CGGuid GetEquipmentSlotByID(int ID);
};

