#include "WObject.h"
#include "Offsets.h"
#include "Utils/Utils.h"
#include "Utils/Vector.h"
#include "GameMethods.h"
#include "WInventory.h"
//////// Define your macros here (only if you don’t need them globally)
//////#define DFIELD(type, funcname, offset)               \
//////    type WObject::funcname()                         \
//////    {                                                \
//////        /* Example pointer arithmetic */             \
//////        return *reinterpret_cast<type*>(             \
//////            reinterpret_cast<uintptr_t>(this) +      \
//////            (offset)                                 \
//////        );                                           \
//////    }
//////
//////#define DFIELD_OBJ(type, funcname, offset)           \
//////    type& WObject::funcname()                        \
//////    {                                                \
//////        return *reinterpret_cast<type*>(             \
//////            reinterpret_cast<uintptr_t>(this) +      \
//////            (offset)                                 \
//////        );                                           \
//////    }


// DFIELD reads a *value* from (this + offset)
#define DFIELD(type, funcname, offset)                               \
    type funcname()                                                  \
    {                                                                \
        return *reinterpret_cast<type*>(                             \
            reinterpret_cast<uintptr_t>(this) + (offset)             \
        );                                                           \
    }

// DFIELD_OBJ reads a *reference* from (this + offset)
#define DFIELD_OBJ(type, funcname, offset)                           \
    type& funcname()                                                 \
    {                                                                \
        return *reinterpret_cast<type*>(                             \
            reinterpret_cast<uintptr_t>(this) + (offset)             \
        );                                                           \
    }


//slots counts A6D0
//DFIELD(WInventory*, WObject::GetInventory, 0xA6D8); //Script_PickupBagFromSlot
WInventory* WObject::GetInventory()
{
    return reinterpret_cast<WInventory*>(
        reinterpret_cast<uintptr_t>(this) + 0xA6D8
        );
}
UnitInfo* WObject::GetUnitInfo()
{
    // Convert `this` to an integer pointer, add the offset (0x500),
    // then reinterpret that as a pointer to UnitInfo.
    return reinterpret_cast<UnitInfo*>(
        reinterpret_cast<uintptr_t>(this) + 0x500
        );
}

//DFIELD(UnitInfo*, GetUnitInfo, 0x500); // was 0x530 in 49345) //+

//DFIELD(uint32_t, WObject::GetHealth, Offsets::Offset_GetHealth);//+
//DFIELD(uint32_t, WObject::GetMaxHealth, Offsets::Offset_GetMaxHealth);


//// Method to get the current health
////float WObject::GetHealth() const {
////    return *reinterpret_cast<const float*>(
////        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_GetHealth
////        );
////}
////
//// Method to get the maximum health
////float WObject::GetMaxHealth() const {
////    return *reinterpret_cast<const float*>(
////        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_GetMaxHealth
////        );
////}

uint32_t WObject::GetHealth() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_GetHealth);}

uint32_t WObject::GetMaxHealth() const {return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_GetMaxHealth);}



uint32_t WObject::GetUnitFlag1() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_UnitFlag1);}
uint32_t WObject::GetUnitFlag2() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_UnitFlag2);}
uint32_t WObject::GetUnitFlag3() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_UnitFlag3); }
uint32_t WObject::GetDynamicFlags() const { return *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_DynamicFlag);}




// Method to get Movement.Pointer
uintptr_t WObject::GetMovementPointer() const {
    return *reinterpret_cast<const uintptr_t*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_Pointer
        );
}

// Method to get TransportPointer
uintptr_t WObject::GetTransportPointer() const {
    return *reinterpret_cast<const uintptr_t*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_Transport_Pointer
        );
}

// Method to get TransportGuid
uint64_t WObject::GetTransportGuid() const {
    return *reinterpret_cast<const uint64_t*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_TransportGuid
        );
}

// Method to get Position
float WObject::GetPosition() const {
    return *reinterpret_cast<const float*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_Position
        );
}

// Method to get Rotation
float WObject::GetRotation() const {
    return *reinterpret_cast<const float*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_Rotation
        );
}

// Method to get Pitch
float WObject::GetPitch() const {
    return *reinterpret_cast<const float*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_Pitch
        );
}

// Method to get UnitSpeed
float WObject::GetUnitSpeed() const {
    return *reinterpret_cast<const float*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_UnitSpeed
        );
}

// Method to get MovementFlag
uint32_t WObject::GetMovementFlag() const {
    return *reinterpret_cast<const uint32_t*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_MovementFlag
        );
}

// Method to get MovementFlagEx
uint32_t WObject::GetMovementFlagEx() const {
    return *reinterpret_cast<const uint32_t*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_MovementFlagEx
        );
}

// Method to get CollisionWidth
float WObject::GetCollisionWidth() const {
    return *reinterpret_cast<const float*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_CollisionWidth
        );
}

// Method to get CollisionHeight
float WObject::GetCollisionHeight() const {
    return *reinterpret_cast<const float*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_CollisionHeight
        );
}

// Method to get WalkableSlope
float WObject::GetWalkableSlope() const {
    return *reinterpret_cast<const float*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_WalkableSlope
        );
}

// Method to get Direction
Vector3 WObject::GetDirection() const {
    return *reinterpret_cast<const Vector3*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_Direction
        );
}

// Method to get Direction2
Vector3 WObject::GetDirection2() const {
    return *reinterpret_cast<const Vector3*>(
        reinterpret_cast<const uintptr_t>(this) + Offsets::Offset_Movement_Direction2
        );
}


PowerTypeId WObject::Power_Type() { return *reinterpret_cast<PowerTypeId*>((uintptr_t)this + 0x00); } //Offsets::UnitPowerType

std::string WObject::getPowerString()
{
    switch (this->Power_Type())
    {
    case PowerTypeId::mana:
        return "Mana";
        break;

    case PowerTypeId::rage:
        return "Rage";
        break;

    case PowerTypeId::energy:
        return "Energy";
        break;

    case PowerTypeId::runicpower:
        return "Runic Power";
        break;
    }

    return "Unknown Power Type";
}


uint8_t WObject::GetRaceID() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::Offset_Race); }
uint8_t WObject::GetClassID() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::Offset_Class); }
//uint8_t WObject::GetSex() const { return *reinterpret_cast<int8_t*>((uintptr_t)this + Offsets::Offsets_Sex); }

// Example function that prints raw byte values at certain offsets
void WObject::PrintTestOffsetValues() const
{
    // Get the base address of 'this'
    uintptr_t base = reinterpret_cast<uintptr_t>(this);

    // We'll define a little helper macro to read & print a single byte.
    // If you need 32-bit or 64-bit, change uint8_t -> uint32_t / uint64_t, etc.
#define PRINT_OFFSET_BYTE(off)                                   \
            do {                                                         \
                uint8_t val = *reinterpret_cast<const uint8_t*>(base + (off)); \
                std::printf("Offset 0x%04X : 0x%02X (%u)\n",             \
                            static_cast<unsigned>(off), val, val);       \
            } while(0)

        // Now call it for each offset you listed:
    PRINT_OFFSET_BYTE(0x190D);
    PRINT_OFFSET_BYTE(0x1888);
    PRINT_OFFSET_BYTE(0x18D0);
    PRINT_OFFSET_BYTE(0x1910);
    PRINT_OFFSET_BYTE(0x05A0);
    PRINT_OFFSET_BYTE(0x00B0);
    // You repeated 0x18D0, so we'll just list it once or do it again:
    // PRINT_OFFSET_BYTE(0x18D0);
    PRINT_OFFSET_BYTE(0x18D8);
    PRINT_OFFSET_BYTE(0x1780);
    PRINT_OFFSET_BYTE(0x1878);
    PRINT_OFFSET_BYTE(0x1F94);
    PRINT_OFFSET_BYTE(0x1858);

#undef PRINT_OFFSET_BYTE
}


CGGuid* WObject::GetGuid() {
    __try {
        return reinterpret_cast<CGGuid*>((uintptr_t)this + Offsets::Offset_Guid);
    }
    __except (1) {
        return new CGGuid();
    }
}

TypeId WObject::GetType() {
    return *reinterpret_cast<TypeId*>((uintptr_t)this + Offsets::Offset_Type);
}


bool WObject::IsItem() { return this->GetType() == TypeId::CGItem; }
bool WObject::IsUnit() { return this->GetType() == TypeId::CGUnit; }
bool WObject::IsPlayer() { return this->GetType() == TypeId::CGPlayer; }
bool WObject::IsLocalPlayer() { return this->GetType() == TypeId::CGActivePlayer; }
bool WObject::IsGameObject() { return this->GetType() == TypeId::CGGameObject; }
bool WObject::IsDynamicObject() { return this->GetType() == TypeId::CGDynamicObject; }
bool WObject::IsCorpse() { return this->GetType() == TypeId::CGCorpse; }
bool WObject::IsAnyObj() {
    if (IsGameObject() || IsUnit() || IsPlayer() || IsLocalPlayer() || IsCorpse()) {
        return true;
    }
    else { return false; }
    return false;
}

//bool IsPlayerMoving() { return this->GetCurrentSpeed() != 0; }
bool WObject::IsGhost() { return GetHealth() == 1; }

//Can also use CGUnit_C::__vmt::IsDeadOrGhost
bool WObject::IsDead() { return (GetHealth() <= 0 || (GetDynamicFlags() & UnitDynFlags::UNIT_DYNFLAG_DEAD) == UnitDynFlags::UNIT_DYNFLAG_DEAD); }
bool WObject::IsLootable() { return (GetDynamicFlags() & UnitDynFlags::UNIT_DYNFLAG_LOOTABLE) == UnitDynFlags::UNIT_DYNFLAG_LOOTABLE; }
bool WObject::IsSkinnable() const { return (UnitFlags() & UnitFlags::UNIT_FLAG_SKINNABLE) == UnitFlags::UNIT_FLAG_SKINNABLE; }
bool WObject::IsInCombat() const { return (UnitFlags() & UnitFlags::UNIT_FLAG_IN_COMBAT) == UnitFlags::UNIT_FLAG_IN_COMBAT; }
bool WObject::IsTapped() { return (GetDynamicFlags() & UnitDynFlags::UNIT_DYNFLAG_TAPPED) == UnitDynFlags::UNIT_DYNFLAG_TAPPED; }
bool WObject::IsTappedByMe() { return (GetDynamicFlags() & UnitDynFlags::UNIT_DYNFLAG_TAPPEDBYME) == UnitDynFlags::UNIT_DYNFLAG_TAPPEDBYME; }

bool WObject::isValid() {
    __try {
        auto res = (uintptr_t(this) != 0 && (uintptr_t(this) & 1) == 0) && (!this->GetGuid()->isEmpty());
        return res;
    }
    __except (1) {
        return false;
    }
}


const char* WObject::GetObjectName() {
	__try {
		typedef const char* (__fastcall* GetName)(uintptr_t);

		uintptr_t* vTable = *(uintptr_t**)this;
		auto getNamePtr = (uintptr_t)vTable[0x32];
		auto getName = (GetName)getNamePtr;
		auto name = getName((uintptr_t)this);
		if (name) {

			return name;
		}

		return "None";
	}
	__except (1) {
		return "None";
	}
}

const float WObject::GetFacing() {
#if Logger
    Utils::logger("start");
#endif
    typedef const float(__fastcall* GetFacing)(uintptr_t);

    uintptr_t* vTable = *(uintptr_t**)this;
    auto getFacingPtr = (uintptr_t)vTable[0x27];
    auto getFacing = (GetFacing)getFacingPtr;
    auto res = getFacing((uintptr_t)this);
#if Logger
    Utils::logger("end");
#endif
    return res;
}

Vector3 WObject::GetObjectNamePosition() const {
#if Logger
    Utils::logger("start");
#endif
    typedef int64_t(__fastcall* GetPosition)(int64_t, int64_t);

    uintptr_t* vTable = *(uintptr_t**)this;
    auto getPosPtr = (uintptr_t)vTable[0xE];
    auto getPos = (GetPosition)getPosPtr;

    Vector3 v = Vector3(0, 0, 0);
    getPos((uintptr_t)this, (int64_t)&v);
#if Logger
    Utils::logger("end");
#endif
    return v;
}

Vector3 WObject::GetUnitPosition() const {

    __try {
        typedef int64_t(__fastcall* GetPosition)(int64_t, int64_t);

        uintptr_t* vTable = *(uintptr_t**)this;
        auto getPosPtr = (uintptr_t)vTable[0xF];
        auto getPos = (GetPosition)getPosPtr;

        Vector3 v = Vector3(0.0, 0.0, 0.0);
        getPos((uintptr_t)this, (int64_t)&v);

        return v;
    }
    __except (1)
    {
        Vector3 v{ 0,0,0 };

        return v;
    }
}

//Test
Vector3 WObject::Direction() const {

    __try {
        typedef int64_t(__fastcall* GetPosition)(int64_t, int64_t);

        uintptr_t* vTable = *(uintptr_t**)this;
        auto getPosPtr = (uintptr_t)vTable[0x2C];
        auto getPos = (GetPosition)getPosPtr;

        Vector3 v = Vector3(0.0, 0.0, 0.0);
        getPos((uintptr_t)this, (int64_t)&v);

        return v;
    }
    __except (1)
    {
        Vector3 v{ 0,0,0 };

        return v;
    }
}

uintptr_t WObject::Ptr() const {

    auto res = reinterpret_cast<uintptr_t>(this);

    return res;
}

uint64_t WObject::GetUnitLevel(uint64_t) const {

    typedef const uint64_t(__fastcall* GetUnitLvl)(uintptr_t);

    uintptr_t* vTable = *(uintptr_t**)this;
    auto GetUnitLevelPtr = (uintptr_t)vTable[0xA1];
    auto GetUnitLevel = (GetUnitLvl)GetUnitLevelPtr;
    auto res = GetUnitLevel((uintptr_t)this);

    return res;
}


uint64_t WObject::Test(uint64_t) const {

    typedef const uint64_t(__fastcall* GetUnitLvl)(uintptr_t);

    uintptr_t* vTable = *(uintptr_t**)this;
    auto GetUnitLevelPtr = (uintptr_t)vTable[0x9A];
    auto GetUnitLevel = (GetUnitLvl)GetUnitLevelPtr;
    auto res = GetUnitLevel((uintptr_t)this);

    return res; 
}

uint64_t WObject::Test2(uint64_t) const {

    typedef const uint64_t(__fastcall* GetUnitLvl)(uintptr_t);

    uintptr_t* vTable = *(uintptr_t**)this;
    auto GetUnitLevelPtr = (uintptr_t)vTable[0x4D];
    auto GetUnitLevel = (GetUnitLvl)GetUnitLevelPtr;
    auto res = GetUnitLevel((uintptr_t)this);

    return res;
}

void WObject::Interact() {

    typedef DWORD* (__fastcall* InteractWith)(uintptr_t);

    uintptr_t* vTable = *(uintptr_t**)this;
    auto interactPtr = (uintptr_t)vTable[0x2A];
    auto interact = (InteractWith)interactPtr;

    interact((uintptr_t)this);

}


typedef DWORD* (__fastcall* FnInteract)(uintptr_t);
void WObject::BruteforceInteractRange(int startIndex, int endIndex)
{
    // Get the vtable
    auto vTable = *reinterpret_cast<uintptr_t**>(this);
    if (!vTable)
    {
        printf("No vtable found.\n");
        return;
    }

    printf("Brute-forcing Interact across vtable indices [0x%X..0x%X].\n", startIndex, endIndex);

    for (int i = startIndex; i <= endIndex; i++)
    {
        // Get the pointer for this vtable slot
        uintptr_t fnPtr = vTable[i];
        if (!fnPtr)
        {
            printf("  vtable[0x%X] = NULL\n", i);
            // Wait 5 seconds before the next attempt
            Sleep(6000);
            continue;
        }

        // Cast to our guessed signature
        auto interactFunc = reinterpret_cast<FnInteract>(fnPtr);

        // Try calling it once, with SEH to catch access violations
        printf("  Trying vtable[0x%X]...\n", i);

        __try
        {
            // If the function is something that returns a pointer or a result,
            // you can store/inspect it. Often these "interact" calls might not return anything useful.
            DWORD* result = interactFunc(reinterpret_cast<uintptr_t>(this));

            // We'll just log we called it and possibly print the result pointer.
            printf("    Called vtable[0x%X]. Result ptr = %p\n", i, (void*)result);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("    vtable[0x%X] caused an exception.\n", i);
        }

        // Wait 5 seconds before moving to the next index
        Sleep(6000);
 
    }


    printf("Done brute-forcing Interact range.\n");
}

void WObject::EnumerateVtableFloats()
{

    // We'll define a function pointer type: __fastcall that takes one uintptr_t
    typedef float(__fastcall* FnGetFloat)(uintptr_t);

    // Get the vtable
    uintptr_t* vtable = *reinterpret_cast<uintptr_t**>(this);
    if (!vtable)
    {
        printf("No vtable found.\n");
        return;
    }

    printf("Enumerating vtable entries [0xF..0x3C] as float:\n");
  //  for (int i = 0x60; i <= 0xE6; i++)
    for (int i = 0x15; i <= 0x38; i++)
    {
        uintptr_t fnPtr = vtable[i];
        if (!fnPtr)
        {
            printf("  vtable[0x%X] = NULL\n", i);
            continue;
        }

        auto getFloat = reinterpret_cast<FnGetFloat>(fnPtr);

        __try
        {
            float value = getFloat(reinterpret_cast<uintptr_t>(this));
            printf("  vtable[0x%X] returned float: %f\n", i, value);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("  vtable[0x%X] caused an exception.\n", i);
        }
    }
}

void WObject::EnumerateVtableVector3()
{
    typedef int64_t(__fastcall* FnVectorOut)(uintptr_t, int64_t);

    uintptr_t* vTable = *(uintptr_t**)this;
    if (!vTable)
    {
        printf("No vtable found.\n");
        return;
    }

    printf("Enumerating vtable entries [0xF..0x3C] as Vector3-writer:\n");

    for (int i = 0x15; i <= 0x38; i++)
    {
        uintptr_t fnPtr = vTable[i];
        if (!fnPtr)
        {
            printf("  vtable[0x%X] = NULL\n", i);
            continue;
        }

        auto writeVec = reinterpret_cast<FnVectorOut>(fnPtr);

        __try
        {
            Vector3 v(0, 0, 0);
            int64_t retVal = writeVec(reinterpret_cast<uintptr_t>(this),
                reinterpret_cast<int64_t>(&v));

            // retVal might be a status or something else
            printf("  vtable[0x%X] wrote Vector3: (%f, %f, %f), ret=0x%llX\n",
                i, v.x, v.y, v.z, static_cast<long long>(retVal));
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("  vtable[0x%X] caused an exception.\n", i);
        }
    }
}




//Lvl 18,  HP 649  Mounted (wolf) Holgar Storm
void WObject::EnumerateVtableU64()
{
    // We'll define a function pointer type: __fastcall that takes one uintptr_t
    typedef uint64_t(__fastcall* FnGetU64)(uintptr_t);

    uintptr_t* vtable = *reinterpret_cast<uintptr_t**>(this);
    if (!vtable)
    {
        printf("No vtable found.\n");
        return;
    }

    printf("Enumerating vtable entries [0xF..0x3C] as uint64_t:\n");
    // 7E <= E06   10 tot 38 gedaan 
    for (int i = 0x15; i <= 0x38; i++)
    {
        uintptr_t fnPtr = vtable[i];
        if (!fnPtr)
        {
            printf("  vtable[0x%X] = NULL\n", i);
            continue;
        }

        auto getU64 = reinterpret_cast<FnGetU64>(fnPtr);

        __try
        {
            uint64_t value = getU64(reinterpret_cast<uintptr_t>(this));
            printf("  vtable[0x%X] returned uint64: 0x%llX (%llu)\n",
                i,
                static_cast<unsigned long long>(value),
                static_cast<unsigned long long>(value));
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            printf("  vtable[0x%X] caused an exception.\n", i);
        }
    }
}

// Enumerate vtable entries from 0xF to 0x3C, trying each as a "get name" function.
void  WObject::EnumerateVtableConstChar()
{
    // We'll define a function pointer type: __fastcall that takes a single uintptr_t.
    typedef const char* (__fastcall* FnGetName)(uintptr_t);

    // Reinterpret the start of 'this' as a pointer to our vtable array
    uintptr_t* vtable = *reinterpret_cast<uintptr_t**>(this);
    if (!vtable)
    {
        printf("No vtable found.\n");
        return;
    }

    printf("Enumerating vtable entries [0xF .. 0x3C]:\n");

    // Loop through each index in the specified range
    for (int i = 0x15; i <= 0x38; i++)
    {
        // Retrieve the pointer at vtable[i]
        uintptr_t fnPtr = vtable[i];
        if (!fnPtr)
        {
            printf("  vtable[0x%X] = NULL\n", i);
            continue;
        }

        // Cast to our guessed function signature
        auto getName = reinterpret_cast<FnGetName>(fnPtr);

        // Attempt to call it, wrapping in SEH to avoid crashes
        __try
        {
            const char* result = getName(reinterpret_cast<uintptr_t>(this));
            if (result && *result)
            {
                // Print the non-empty string
                printf("  vtable[0x%X] returned: \"%s\"\n", i, result);
            }
            else
            {
                // Either null or empty
                printf("  vtable[0x%X] returned: <empty or null>\n", i);
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            // If calling the function caused an exception, report it
            printf("  vtable[0x%X] caused an exception.\n", i);
        }
    }
}


uint32_t WObject::GetAuraCount() const {
#if Logger
    Utils::logger("start");
#endif
    auto res = *reinterpret_cast<int32_t*>((uintptr_t)this + Offsets::Offset_AuraCount);
#if Logger
    Utils::logger("end");
#endif
    return res;
}

std::vector<uint32_t> WObject::HasAura() {
#if Logger
    Utils::logger("start");
#endif
    std::vector<uint32_t> mBuffs;
    uint32_t auraCount = GetAuraCount();
    if (auraCount == -1)
    {  /* // Does this ever happen??? */
    }
    for (int32_t currentAuraCount = 0; currentAuraCount < auraCount; ++currentAuraCount) {
        Aura Table;
        auto offset = (Offsets::Offset_AuraTable + currentAuraCount * Offsets::Offset_AuraSize);
        uintptr_t a = (uintptr_t)this + offset;
        Table = *reinterpret_cast<Aura*>(a);
        if (Table.SpellID && (Table.Flags & static_cast<std::uint8_t>(AuraFlags::Harmful))) { // Table.Flags  & 20
            mBuffs.push_back(Table.SpellID);
        }
    }
#if Logger
    Utils::logger("end");
#endif
    return mBuffs;
}


bool WObject::pHasAura(int spellId) {
#if Logger
    Utils::logger("start");
#endif
    std::vector<uint32_t> mBuffs = HasAura();

    for (int i = 0; i < mBuffs.size(); i++)
    {
        if (mBuffs[i] == spellId)
        {
#if Logger
            Utils::logger("end");
#endif
            return true;
        }
    }
#if Logger
    Utils::logger("end");
#endif
    return false;
}

//
//std::vector<ActiveQuest> WObject::GetActiveQuestId()
//{
//    std::vector<ActiveQuest> QuestId;
//
//    if (this->isValid())
//    {
//        for (size_t i = 0; i < 25; i++) 
//        {
//            ActiveQuest quest;
//            quest.QuestId = *reinterpret_cast<uint32_t*>((uintptr_t)this + 0xDE58 + (i * 0x40));
//            quest.isCompleted = *reinterpret_cast<int8_t*>((uintptr_t)this + 0xDE5D + (i * 0x40));
//            quest.StartTime = *reinterpret_cast<uint32_t*>((uintptr_t)this + 0xDE64 + (i * 0x40));
//            quest.Objective1 = *reinterpret_cast<uint16_t*>((uintptr_t)this + 0xDE68 + (i * 0x40));
//            quest.Objective2 = *reinterpret_cast<uint16_t*>((uintptr_t)this + 0xDE6A + (i * 0x40));
//            quest.Objective3 = *reinterpret_cast<uint16_t*>((uintptr_t)this + 0xDE6C + (i * 0x40));
//            quest.Objective4 = *reinterpret_cast<uint16_t*>((uintptr_t)this + 0xDE6E + (i * 0x40));
//            quest.Objective5 = *reinterpret_cast<uint16_t*>((uintptr_t)this + 0xDE70 + (i * 0x40));
//            QuestId.push_back(quest);
//        }
//    }
//    return QuestId;
//}
//
//ActiveQuest WObject::GetActiveQuestById(int idx)
//{
//    ActiveQuest res = ActiveQuest();
//    std::vector<ActiveQuest> quests = GetActiveQuestId();
//
//    for (int i = 0; i < quests.size(); ++i) {
//        if (quests[i].QuestId == idx) {
//            return quests[i];
//        }
//    }
//
//    return res;
//}