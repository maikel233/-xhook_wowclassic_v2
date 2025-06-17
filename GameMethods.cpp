#include "GameMethods.h"
#include "Utils/Utils.h"
#include "Offsets.h"
#include <mutex>
#include "CGWorldFrame.h"


namespace GameMethods
{
   
    ItemCacheEntry* GetItemCacheEntry(int ItemID)
    {
#if Logger
        Utils::logger("start");
#endif
        char unk[48]; //just for sure original is 24
        auto res = GameMethods::Invoke<ItemCacheEntry*>(Offsets::Offset_GetItemCacheEntry, Offsets::Offset_ItemCacheEntryBase, ItemID, (uint8_t)0, unk);
#if Logger
        Utils::logger("end");
#endif
        return res;
    }

    void GameMethods::GuidToString(CGGuid* guid, char guidStr[]) {
#if Logger
        Utils::logger("start");
#endif
        GameMethods::Invoke<int64_t>(Offsets::Offset_GuidToString, (int64_t)guid, guidStr, 128);  // 128 might be the buffer size
#if Logger
        Utils::logger("end");
#endif
    }

    bool ObjMgrIsValid(uint8_t param) {
#if Logger
        Utils::logger("start");
#endif
        auto res = reinterpret_cast<bool(__fastcall*)(int8_t)>(Offsets::Offset_ClntObjMgrIsValid)(param);
#if Logger
        Utils::logger("end");
#endif
        return res;
    }

    char EnumVisibleObjects(EnumVisibleObjectsCb callback, int64_t filter) {
#if Logger
        Utils::logger("start");
#endif
        auto res = reinterpret_cast<char(__fastcall*)(GameMethods::EnumVisibleObjectsCb, int64_t)>(
            Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr)(callback, filter);
#if Logger
        Utils::logger("end");
#endif
        return res;
    }

    void ClickToMove(int64_t playerPtr, Vector3 position) {
        reinterpret_cast<void(__fastcall*)(int64_t, Vector3&)>(Offsets::Offset_ClickToMove)(playerPtr, position);
    }

    void ToggleControlBit(ControlBits ControlBit, bool State) {
#if Logger
        Utils::logger("start");
#endif
        GameMethods::Invoke<uintptr_t>(Offsets::Offset_ToggleControlBit, Offsets::Offset_InputControl,
            (uint64_t)ControlBit, (int32_t)State, (uint32_t)GetTickCount(), (uint8_t)0);
#if Logger
        Utils::logger("end");
#endif
    }

    uint64_t GameMethods::GetUnitReaction(WObject* localPlayer, WObject* unit)
    {
        // For example, if the new function is actually __fastcall:
        typedef __int64(__fastcall* UnitIsFriendlyOrEnemy_t)(__int64, __int64);

        // The address of the function in memory
        auto fnAddress = Offsets::Offset_UnitReaction;

        // Cast to your function pointer
        auto fn = reinterpret_cast<UnitIsFriendlyOrEnemy_t>(fnAddress);

        // Call it, passing your two pointers re-cast to __int64
        // Because the function signature is (me, target) as __int64
        __int64 result = fn(
            reinterpret_cast<__int64>(localPlayer),
            reinterpret_cast<__int64>(unit)
        );

        return static_cast<uint64_t>(result);
    }

    using ClntObjMgr__GetMapId_Fn = uint32_t(__stdcall*)();
    uint32_t GameMethods::ClntObjMgr__GetMapId() {
        __try {
            return reinterpret_cast<ClntObjMgr__GetMapId_Fn>(Offsets::Offset_ClntObjMgrGetMapId)();
        }
        __except (1) {
            return 0;
        }
    }

//    ItemCacheEntry* GetItemCacheEntry(int ItemID) {
//#if Logger
//        Utils::logger("start");
//#endif
//        char unk[48];  // Just for sure, original is 24
//        auto res = GameMethods::Invoke<ItemCacheEntry*>(Offset_GetItemCachEntry, Offset_ItemCachEntryBase, ItemID, (uint8_t)0, unk);
//#if Logger
//        Utils::logger("end");
//#endif
//        return res;
//    }

   

    void Jump()
    {
#if Logger
        Utils::logger("start");
#endif
        // e.g. GameMethods::Invoke<uintptr_t>(Offset_Jump, GlobalVars::LocalPlayer, GetTickCount64());
        Invoke<uintptr_t>(Offsets::Offset_Jump, GlobalVars::LocalPlayer, (uint32_t)GetTickCount64());
#if Logger
        Utils::logger("end");
#endif
    }

    int GetCorpseMapID() {
#if Logger
        Utils::logger("start");
#endif
        int CorpseMapId = *reinterpret_cast<int*>(Offsets::Offset_CorpseMapID);
#if Logger
        Utils::logger("end");
#endif
        return CorpseMapId;
    }

    bool isCorpseInDungeon() {
        bool msg = *reinterpret_cast<bool*>(Offsets::Offset_Bool_MustEnterInstanceToRecoverBodymsg);
        bool res = (msg == 30 || msg == 229 || msg == 44 || msg == 62);
        return res;
    }

    Vector3 GetCorpsePosition() {
#if Logger
        Utils::logger("start");
#endif
        Vector3 CorpsePos = *reinterpret_cast<Vector3*>(Offsets::Offset_CorpsePos);
#if Logger
        Utils::logger("end");
#endif
        return CorpsePos;
    }

    void FaceTo(int64_t playerPtr, float angle)
    {
#if Logger
        Utils::logger("start");
#endif
        __try
        {
            // Possibly we do *(float*)(playerPtr + 0x158) = angle;
            // The code snippet shows GlobalVars::LocalPlayer->Ptr() + 0x158
            *(float*)(GlobalVars::LocalPlayer->Ptr() + 0x158) = angle;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            // swallow exception
        }
#if Logger
        Utils::logger("end");
#endif
    }

    int64_t SpriteLeftClick(CGGuid* TargetGuid)
    {
#if Logger
        Utils::logger("start");
#endif
        auto fn = reinterpret_cast<int64_t(__fastcall*)(CGGuid*)>(Offsets::Offset_SpriteLeftClick);
        int64_t res = fn(TargetGuid);
#if Logger
        Utils::logger("end");
#endif
        return res;
    }

    int64_t SpriteRightClick(CGGuid* TargetGuid)
    {
#if Logger
        Utils::logger("start");
#endif
        auto fn = reinterpret_cast<int64_t(__fastcall*)(CGGuid*, int32_t)>(Offsets::Offset_SpriteRightClick);
        int64_t res = fn(TargetGuid, 10);
#if Logger
        Utils::logger("end");
#endif
        return res;
    }


    int64_t CGUnit_C_OnAttackIconPressed(CGGuid* targetGuid)
    {
#if Logger
        Utils::logger("start");
#endif
        auto fn = reinterpret_cast<int64_t(__fastcall*)(int64_t, CGGuid*, uint32_t, int32_t, int32_t, int32_t)>(
            Offsets::Offset_CGUnit_C_OnAttackIconPressed
            );
        int64_t res = fn(GlobalVars::LocalPlayer->Ptr(), targetGuid, 0, 0, 0, 0);
#if Logger
        Utils::logger("end");
#endif
        return res;
    }

    bool CGUnit_C_IsInCombat(int64_t playerPtr)
    {
#if Logger
        Utils::logger("start");
#endif
        auto fn = reinterpret_cast<bool(__fastcall*)(int64_t)>(Offsets::Offset_CGUnit_C_IsInMelee);
        bool res = fn(playerPtr);
#if Logger
        Utils::logger("end");
#endif
        return res;
    }

    // 1) Define the struct for the second argument
#pragma pack(push, 1)
    struct GossipTextArg
    {
        const char* textPtr;  // offset 0
        uint8_t     hasText;  // offset 8
        // We can add padding if needed, but these are at least the critical fields
    };
#pragma pack(pop)

    // 2) Define the function pointer type
    using SelectGossipOption_t = void(__fastcall*)(
        unsigned int gossipOptionID,
        __int64      structPtr,
        short        a3,
        bool         a4
        );

    // 3) Hardcode or store the function’s address
    static uintptr_t Addr_SelectGossipOption = Offsets::Offset_GossipSelectOption; // or (moduleBase + 0x2C5E660)


    // 4) A helper wrapper
    void CallSelectGossipOption(
        unsigned int optionID,
        const char* optionalText,
        bool         highByteFlag,  // if true => pass a3=0x0100 else 0
        bool         forceFlag      // for the a4 param
    )
    {
        // Cast the address to our function pointer
        auto fn = reinterpret_cast<SelectGossipOption_t>(Addr_SelectGossipOption);

        // Build up the small Arg struct for param #2
        GossipTextArg arg2{};
        arg2.textPtr = optionalText;
        arg2.hasText = (optionalText && *optionalText) ? 1 : 0;

        // Construct the `a3` short so that HIBYTE(a3) is 1 or 0
        // Example: if highByteFlag == true => a3 = 0x0100
        short a3Value = highByteFlag ? 0x0100 : 0x0000;

        // Now call it
        fn(
            optionID,                    // a1
            reinterpret_cast<__int64>(&arg2),  // a2 (pointer to struct)
            a3Value,                     // a3
            forceFlag                    // a4
        );
    }



    // Function to get bone positions
    bool GetBonePositions(__int64 a1, __int64 a2, std::vector<Bone>& bones)
    {
#if Logger
        Utils::logger("Start GetBonePositions");
#endif

        auto fn = reinterpret_cast<__int64(__fastcall*)(__int64, __int64)>(Offsets::Offset_CM2ModelGetBonePosition);
        __int64 result = fn(a1, a2);

        if (!result)
            return false;

        // Extract bone positions (pseudo-code, adapt based on actual structure)
        for (int i = 0; i < 24; i++) // Assuming 24 bones, adjust as needed
        {
            Bone bone;
            bone.boneID = i;
            bone.position = *(Vector3*)(result + i * sizeof(Vector3));
            bones.push_back(bone);
        }

#if Logger
        Utils::logger("End GetBonePositions");
#endif

        return true;
    }

    bool isLootWindowOpen() {
        auto res = (*reinterpret_cast<uintptr_t*>(Offsets::Offset_isLootWindowOpen)) != 0L;
        return res;
    }


    uint32_t GameTime() { return reinterpret_cast<uint32_t(__fastcall*)()>(Offsets::Offset_GameTime)(); }


    int64_t Spell_C_GetMinMaxSpellRange(int32_t SpellId, float_t* MinRange, float_t* MaxRange, CGGuid* TargetGuid) {
        auto res = reinterpret_cast<int64_t(__fastcall*)(int64_t playerPtr, int32_t, float_t*, float_t*, CGGuid*, int64_t)>(Offsets::Offset_Spell_C_GetMinMaxRange)(GlobalVars::LocalPlayer->Ptr(), SpellId, MinRange, MaxRange, TargetGuid, 0);
        return res;
    }

    using F_SpellByName_t = void** (__fastcall*)();
    using SpellBook_FindSpellByName_t = __int64(__fastcall*)(__int64, char*, bool*);
    int GetSpellIdByName(const char* SpellName) {
        if (!SpellName || !*SpellName) {
            Print("Invalid spell name.\n");
            return -1;
        }

        // Call F_SpellByName to get the spellbook context
        void** spellbookContext = nullptr;
        __try {
            spellbookContext = Invoke<void**>(Offsets::Offset_SpellBook_Instance);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            Print("Crash occurred while calling F_SpellByName!\n");
            return -1;
        }

        if (!spellbookContext) {
            Print("Failed to get spellbook context.\n");
            return -1;
        }

        // Debug: Print the spellbook context and spell name
        Print("Spellbook Context: %p\n", spellbookContext);
        Print("Spell Name: %s\n", SpellName);

        // Call SpellBook_FindSpellByName
        bool spellValid = false;
        __int64 spellId = 0;
        __try {
            spellId = Invoke<__int64>(Offsets::Offset_SpellBook_FindSpellByName, reinterpret_cast<__int64>(spellbookContext), const_cast<char*>(SpellName), &spellValid);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            Print("Crash occurred while calling SpellBook_FindSpellByName!\n");
            return -1;
        }

        // Debug: Print the spell ID and validity
        Print("Spell: %s, ID: %lld, Valid: %d\n", SpellName, spellId, spellValid);

        if (spellId == 0 /*|| spellValid*/) {
            Print("Spell not found or invalid.\n");
            return -1;
        }

        return static_cast<int>(spellId);
    }
   



 //   using F_SpellByName_t = void** (__fastcall*)();
    using FindSlotBySpellID_t = int64_t(__fastcall*)(__int64, int32_t, int32_t);

    int64_t FindSlotBySpellId(int32_t spellId) {
        // Validate spell ID
        if (spellId <= 0) {
            Print("Invalid spell ID.\n");
            return -1;
        }

        // Retrieve the spellbook context
        void** spellbookContext = nullptr;
        __try {
            spellbookContext = Invoke<void**>(GlobalVars::g_hModuleBase + 0x2D96B00);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            Print("Crash occurred while retrieving spellbook context!\n");
            return -1;
        }

        if (!spellbookContext) {
            Print("Failed to get spellbook context.\n");
            return -1;
        }

        // Debug: Print the spellbook context and spell ID
        Print("Spellbook Context: %p\n", spellbookContext);
        Print("Spell ID: %d\n", spellId);

        // Call CGSpellBook::FindSlotBySpellID
        int64_t slot = -1;
        __try {
            slot = Invoke<int64_t>(
                Offsets::Offset_SpellBook_findSlotBySpellId,
                reinterpret_cast<__int64>(spellbookContext),
                spellId,
                0 // Additional argument (e.g., flag)
            );
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            Print("Crash occurred while calling CGSpellBook::FindSlotBySpellID!\n");
            return -1;
        }

        // Debug: Print the result
        Print("Spell ID: %d, Slot: %lld\n", spellId, slot);

        if (slot == -1) {
            Print("Failed to find slot for spell ID %d.\n", spellId);
        }

        return slot;
    }







    long getCurrentTime() {
        LARGE_INTEGER frequency, counter;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&counter);
        long currentTime = (counter.QuadPart * 1000) / frequency.QuadPart;
        return currentTime;
    }

}
