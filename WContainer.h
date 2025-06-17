#pragma once
#include "Utils/Vector.h"
#include "Constants.h"
#include "WObject.h"


class WContainer : public WObject
{
public:
    int GetSlots();
    CGGuid GetSlotById(int ID);
};