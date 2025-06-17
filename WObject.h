#pragma once
#include "Utils/Vector.h"
#include "Constants.h"
#include "WInventory.h"
#include "UnitInfo.h"

class Aura
{
public:
    char pad_0000[32]; //0x0000
    CGGuid OwnerGuid; //0x0020
    char pad_0028[16]; //0x0028
    uint32_t TimeLeft; //0x0040
    char pad_0044[68]; //0x0044
    int SpellID; //0x0088
    char pad_008C[4]; //0x008C
    uint16_t Flags; //0x0090
   // byte Level; //0x0092
    //char pad_0094[240]; //0x0094
}; //Size: 0x0184


class CGGuid; // Forward declaration of CGGuid
class WObject
{
public:
    virtual ~WObject() {}

    // Expose these as normal member function declarations (no inline macros here).

    WInventory* GetInventory();
    UnitInfo* GetUnitInfo();

    uint32_t GetHealth() const;
    uint32_t GetMaxHealth() const;

    void DebugPrintHealth() const;

    uint32_t GetUnitFlag1() const;

    uint32_t GetUnitFlag2() const;

    uint32_t GetUnitFlag3() const;

    uint32_t GetDynamicFlags() const;

    // New methods
    uintptr_t GetMovementPointer() const;
    uintptr_t GetTransportPointer() const;
    uint64_t GetTransportGuid() const;
    float GetPosition() const;
    float GetRotation() const;
    float GetPitch() const;
    float GetUnitSpeed() const;
    uint32_t GetMovementFlag() const;
    uint32_t GetMovementFlagEx() const;
    float GetCollisionWidth() const;
    float GetCollisionHeight() const;
    float GetWalkableSlope() const;
    Vector3 GetDirection() const;
    Vector3 GetDirection2() const;

    PowerTypeId Power_Type();

    std::string getPowerString();

    uint8_t GetRaceID() const;

    uint8_t GetClassID() const;

    uint8_t GetSex() const;

    void PrintTestOffsetValues() const;

    // Function declarations (no implementation)
    CGGuid* GetGuid();
    TypeId GetType();
    bool IsItem();
    bool IsUnit();
    bool IsPlayer();
    bool IsLocalPlayer();
    bool IsGameObject();
    bool IsDynamicObject();
    bool IsCorpse();
    bool IsAnyObj();
    bool IsGhost();
    bool IsDead();
    bool IsLootable();
    bool IsSkinnable() const;
    bool IsInCombat() const;
    bool IsTapped();
    bool IsTappedByMe();
    bool isValid();
    const char* GetObjectName();
    const float GetFacing();
    Vector3 Direction() const;
    uintptr_t Ptr() const;
    uint64_t GetUnitLevel(uint64_t) const;
    uint64_t Test(uint64_t) const;
    uint64_t Test2(uint64_t) const;
    void Interact();
    void BruteforceInteractRange(int startIndex, int endIndex);
    Vector3 GetObjectNamePosition() const;
    Vector3 GetUnitPosition() const;

    void EnumerateVtableVector3();
    void EnumerateVtableU64();
    void EnumerateVtableFloats();
    void EnumerateVtableConstChar();

    uint32_t GetAuraCount() const;

    std::vector<uint32_t> HasAura();

    bool pHasAura(int spellId);

    std::vector<ActiveQuest> GetActiveQuestId();

    ActiveQuest GetActiveQuestById(int idx);

    uint32_t GetID;
    uint32_t GetStackCount;
};
