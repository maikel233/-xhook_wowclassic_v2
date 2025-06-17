#pragma once
#include "FC.h"
#include <cstdint>
#include "GlobalVars.h"
class Offsets
{
public:
    static uintptr_t Offset_IsPlayerInWorld;
    static uintptr_t Offset_CGGameObject_C_CanUse;
    static uintptr_t Offset_CGGameObject_C_CanUseNow;
    static uintptr_t Offset_CGGameObject_C_IsLocked;
    static uintptr_t Offset_LastRedMessage;
    static uintptr_t Offset_InstanceName;

    static uintptr_t Offset_ClntObjMgrEnumVisibleObjectsPtr;
    static uintptr_t Offset_ClntObjMgrGetMapId;
    static uintptr_t Offset_ClntObjMgrIsValid;
    static uintptr_t Offset_ClickToMove;
    static uintptr_t Offset_FaceTo;

    static uintptr_t Offset_InvalidPtrCheckMin;
    static uintptr_t Offset_InvalidPtrCheckMax;
    static uintptr_t Offset_HardwareEventPtr;
    static uintptr_t Offset_CGItem_UseItemParm;
    static uintptr_t Offset_CGItem_UseItem;

    static uintptr_t Offset_Spell_C_GetMinMaxRange;
    static uintptr_t Offset_Spell_C_IsCurrentSpell;
    static uintptr_t Offset_Spell_C_GetSpellCoolDown;
    static uintptr_t Offset_Spell_C_CastSpell;
    static uintptr_t Offset_Spell_C_HaveSpellPower;
    static uintptr_t Offset_CGUnit_IsSpellKnown;
    static uintptr_t Offset_SpellBook_findSlotBySpellId;
    static uintptr_t Offset_SpellBook_Instance;
    static uintptr_t Offset_SpellBook_FindSpellByName;
    static uintptr_t Offset_SpellBook_RepeatingSpellId;

    static uintptr_t Offset_UnitReaction;
    static uintptr_t Offset_Cooldown;
    static uintptr_t Offset_GuidToString;
    static uintptr_t Offset_CGPlayer_C_HandleRepopRequest;
    static uintptr_t Offset_SpriteLeftClick;
    static uintptr_t Offset_SpriteRightClick;
    static uintptr_t Offset_CGUnit_C_OnAttackIconPressed;
    static uintptr_t Offset_CGUnit_C_IsInMelee;
    static uintptr_t Offset_isLootWindowOpen;
    static uintptr_t Offset_CorpseMapID;
    static uintptr_t Offset_CorpsePos;
    static uintptr_t Offset_Bool_MustEnterInstanceToRecoverBodymsg;
    static uintptr_t Offset_CameraMgr;
    static uintptr_t Offset_CameraPtr;
    static uintptr_t Offset_WorldFrame_GetWorld;
    static uintptr_t Offset_WorldFrame_Intersect;
    static uintptr_t Offset_WorldFrame_GetScreenCoordinates;
    static uintptr_t Offset_InputControl;
    static uintptr_t Offset_ToggleControlBit;
    static uintptr_t Offset_Jump;
    static uintptr_t Offset_HandleTerrainClick;
    static uintptr_t Offset_CanAttack;
    static uintptr_t Offset_IsOutDoors;
    static uintptr_t Offset_Dismount;
    static uintptr_t Offset_GetItemCacheEntry;
    static uintptr_t Offset_ItemCacheEntryBase;
    static uintptr_t Offset_Merchant_unk_arg;
    static uintptr_t Offset_Merchant;
    static uintptr_t Offset_MerchantItems;
    static uintptr_t Offset_MerchantCount;
    static uintptr_t Offset_MerchantItemsInfoSize;
    static uintptr_t Offset_MerchantItemsInfoStackCount;
    static uintptr_t Offset_MerchantSellItem;
    static uintptr_t Offset_MerchantBuyItem;
    static uintptr_t Offset_MerchantGetAllRepairCost;
    static uintptr_t Offset_MerchantRepairStruct;
    static uintptr_t Offset_MerchantRepairAllItems;
    static uintptr_t Offset_GetSkillIndexById;
    static uintptr_t Offset_UseActionBar;
    static uintptr_t Offset_RetrieveCorpse1;
    static uintptr_t Offset_RetrieveCorpseStruct;
    static uintptr_t Offset_RetrieveCorpse2;
    static uintptr_t Offset_RetrieveCorpseGuid;
    static uintptr_t Offset_GetRuneType;
    static uintptr_t Offset_IsRuneAtCooldown;
    static uintptr_t Offset_GossipSelectOption;
    static uintptr_t Offset_LastTargetGuid;
    static uintptr_t Offset_CM2ModelGetBonePosition;
    static uintptr_t Offset_GameTime;


    static uintptr_t Offset_Quest_SelectActiveQuest;
    static uintptr_t Offset_Quest_SelectAvalibleQuest;
    static uintptr_t Offset_Quest_AcceptQuest;
    static uintptr_t Offset_Quest_IsQuestComplete;
    static uintptr_t Offset_Quest_GetReward;
    static uintptr_t Offset_Quest_GetQuestReward;
    static uintptr_t Offset_Quest_GetQuestRewardid;


    static uint8_t Offset_Type;
    static uint16_t Offset_Guid;
    static uint16_t Offset_Owner;
    static uint16_t Offset_Race;
    static uint16_t Offset_Class;
    static uint16_t Offset_Sex;
    static uint16_t Offset_AnimationStatus;
    static uint16_t Offset_GatherStatus;
    static uintptr_t Offset_GetHealth;
    static uintptr_t Offset_GetMaxHealth;

    static uintptr_t Offset_UnitFlag1;
    static uintptr_t Offset_UnitFlag2;
    static uintptr_t Offset_UnitFlag3;
    static uintptr_t Offset_DynamicFlag; 

    static uintptr_t Offset_CreatureInfo;

    static uintptr_t Offset_Movement_Pointer;
    static uintptr_t Offset_Movement_Transport_Pointer;
    static uintptr_t Offset_Movement_TransportGuid;
    static uintptr_t Offset_Movement_Position;
    static uintptr_t Offset_Movement_Rotation;
    static uintptr_t Offset_Movement_Pitch;
    static uintptr_t Offset_Movement_UnitSpeed;
    static uintptr_t Offset_Movement_MovementFlag;
    static uintptr_t Offset_Movement_MovementFlagEx;
    static uintptr_t Offset_Movement_CollisionWidth;
    static uintptr_t Offset_Movement_CollisionHeight;
    static uintptr_t Offset_Movement_WalkableSlope;
    static uintptr_t Offset_Movement_Direction;
    static uintptr_t Offset_Movement_Direction2;
    static uintptr_t Offset_AuraCount;
    static uintptr_t Offset_AuraTable;
    static uintptr_t Offset_AuraSize;

    static void InitStaticOffsets();
};
