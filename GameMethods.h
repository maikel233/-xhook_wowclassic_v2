#pragma once

//#include "Includes.h"
#include "Utils/Vector.h"
//#include "CoolDownStruct.h"
#include "EncStr.h"
#include "GlobalVars.h"
#include <vector>
#include <cstdint>
#include "ItemCacheEntry.h"
#include "CGWorldFrame.h"
struct PAGE {
    WORD language;
    WORD code;
};

struct Bone
{
    int boneID;
    Vector3 position;
};

namespace GameMethods
{
    using EnumVisibleObjectsCb = unsigned int(__fastcall*)(int64_t, int64_t);
    using LuaCallback = signed int(__fastcall*)(int64_t luaState);
    using ClntObjMgr__GetMapId_Fn = uint32_t(__stdcall*)();

    template<typename RET, typename ...ARGS>
    RET Invoke(uintptr_t offset, ARGS ...args) {
        if (!offset) {
            MessageBoxA(nullptr, "Invalid Function Address!", "Zero Address", MB_OK);
        }

        return reinterpret_cast<RET(__fastcall*)(ARGS...)>(offset)(args ...);
    }

    ItemCacheEntry* GetItemCacheEntry(int ItemID);
    bool ObjMgrIsValid(uint8_t param);
    char EnumVisibleObjects(EnumVisibleObjectsCb callback, int64_t filter);
    void ClickToMove(int64_t playerPtr, Vector3 position);
    void ToggleControlBit(ControlBits ControlBit, bool State);
   // ItemCacheEntry* GetItemCacheEntry(int ItemID);
  
    bool isLootWindowOpen();
    void Jump();
    int GetCorpseMapID();
    bool isCorpseInDungeon();
    Vector3 GetCorpsePosition();
   // void FaceTo(int64_t playerPtr, float_t angle);
    int64_t SpriteLeftClick(CGGuid* TargetGuid);
    int64_t SpriteRightClick(CGGuid* TargetGuid);

   /// int64_t RepopMe();
  
    int64_t CGUnit_C_OnAttackIconPressed(CGGuid* targetGuid);
    bool CGUnit_C_IsInCombat(int64_t playerPtr);
    void GuidToString(CGGuid* guid, char guidStr[]);
    uint64_t GetUnitReaction(WObject* localPlayer, WObject* unit);
    uint32_t ClntObjMgr__GetMapId();
    ////long getCurrentTime();
    ////bool GetCoolDown();
    ////bool isMerchantOpenned();
    ////bool isMailOpenned();
    ////bool isGossipOpenned();
    ////bool IsQuestWindowOpen();
    ////bool IsHuetaOpened();

    void CallSelectGossipOption(
        unsigned int optionID,
        const char* optionalText,
        bool         highByteFlag,  // if true => pass a3=0x0100 else 0
        bool         forceFlag      // for the a4 param
    );


    //int64_t SpellBook_FindSpellByName(const char* SpellName);

    bool GetBonePositions(__int64 a1, __int64 a2, std::vector<Bone>& bones);
    uint32_t GameTime();

    int64_t Spell_C_GetMinMaxSpellRange(int32_t SpellId, float_t* MinRange, float_t* MaxRange, CGGuid* TargetGuid);
   // std::vector<float> SpellMinMaxRange(int spellId);
    /*CGWorldFrame* WorldFrame();*/

  //  int64_t SpellBook_FindSpellByName(const char* SpellName, uint64_t* unk);
    int GetSpellIdByName(const char* SpellName);
    long getCurrentTime();
    int64_t FindSlotBySpellId(int32_t spellId);
}
