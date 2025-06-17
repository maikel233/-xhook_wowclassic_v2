#include "Offsets.h"

// Utility Macros
#define Addy(Off) Print(("%s = 0x%p\n"),(#Off),Off - (uintptr_t)GlobalVars::g_hModuleBase);
#define Offy(Off) Print(("%s = 0x%p\n"),(#Off),Off);

uintptr_t Offsets::Offset_IsPlayerInWorld = 0;
uintptr_t Offsets::Offset_CGGameObject_C_CanUse = 0;
uintptr_t Offsets::Offset_CGGameObject_C_CanUseNow = 0;
uintptr_t Offsets::Offset_CGGameObject_C_IsLocked = 0;
uintptr_t Offsets::Offset_LastRedMessage = 0;
uintptr_t Offsets::Offset_InstanceName = 0;

uintptr_t Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr = 0;
uintptr_t Offsets::Offset_ClntObjMgrGetMapId = 0;
uintptr_t Offsets::Offset_ClntObjMgrIsValid = 0;
uintptr_t Offsets::Offset_ClickToMove = 0;
uintptr_t Offsets::Offset_FaceTo = 0;

uintptr_t Offsets::Offset_InvalidPtrCheckMin = 0;
uintptr_t Offsets::Offset_InvalidPtrCheckMax = 0;

uintptr_t Offsets::Offset_HardwareEventPtr = 0;
uintptr_t Offsets::Offset_CGItem_UseItemParm = 0;
uintptr_t Offsets::Offset_CGItem_UseItem = 0;

uintptr_t Offsets::Offset_AuraCount = 0;
uintptr_t Offsets::Offset_AuraTable = 0;
uintptr_t Offsets::Offset_AuraSize = 0;

// Newly added offsets
uintptr_t Offsets::Offset_Spell_C_GetMinMaxRange = 0;
uintptr_t Offsets::Offset_Spell_C_IsCurrentSpell = 0;
uintptr_t Offsets::Offset_Spell_C_GetSpellCoolDown = 0;
uintptr_t Offsets::Offset_Spell_C_CastSpell = 0;
uintptr_t Offsets::Offset_Spell_C_HaveSpellPower = 0;
uintptr_t Offsets::Offset_CGUnit_IsSpellKnown = 0;
uintptr_t Offsets::Offset_SpellBook_findSlotBySpellId = 0;
uintptr_t Offsets::Offset_SpellBook_Instance = 0;
uintptr_t Offsets::Offset_SpellBook_FindSpellByName = 0;
uintptr_t Offsets::Offset_SpellBook_RepeatingSpellId = 0;
uintptr_t Offsets::Offset_UnitReaction = 0;
uintptr_t Offsets::Offset_Cooldown = 0;
uintptr_t Offsets::Offset_GuidToString = 0;
uintptr_t Offsets::Offset_CGPlayer_C_HandleRepopRequest = 0;
uintptr_t Offsets::Offset_SpriteLeftClick = 0;
uintptr_t Offsets::Offset_SpriteRightClick = 0;
uintptr_t Offsets::Offset_CGUnit_C_OnAttackIconPressed = 0;
uintptr_t Offsets::Offset_CGUnit_C_IsInMelee = 0;
uintptr_t Offsets::Offset_isLootWindowOpen = 0;
uintptr_t Offsets::Offset_CorpseMapID = 0;
uintptr_t Offsets::Offset_CorpsePos = 0;
uintptr_t Offsets::Offset_Bool_MustEnterInstanceToRecoverBodymsg = 0;
uintptr_t Offsets::Offset_CameraMgr = 0;
uintptr_t Offsets::Offset_WorldFrame_GetScreenCoordinates = 0;
uintptr_t Offsets::Offset_CameraPtr = 0;
uintptr_t Offsets::Offset_WorldFrame_GetWorld = 0;
uintptr_t Offsets::Offset_WorldFrame_Intersect = 0;
uintptr_t Offsets::Offset_InputControl = 0;
uintptr_t Offsets::Offset_ToggleControlBit = 0;
uintptr_t Offsets::Offset_Jump = 0;
uintptr_t Offsets::Offset_HandleTerrainClick = 0;
uintptr_t Offsets::Offset_CanAttack = 0;
uintptr_t Offsets::Offset_IsOutDoors = 0;
uintptr_t Offsets::Offset_Dismount = 0;
uintptr_t Offsets::Offset_GetItemCacheEntry = 0;
uintptr_t Offsets::Offset_ItemCacheEntryBase = 0;
uintptr_t Offsets::Offset_Merchant_unk_arg = 0;
uintptr_t Offsets::Offset_Merchant = 0;
uintptr_t Offsets::Offset_MerchantItems = 0;
uintptr_t Offsets::Offset_MerchantCount = 0;
uintptr_t Offsets::Offset_MerchantItemsInfoSize = 0;
uintptr_t Offsets::Offset_MerchantItemsInfoStackCount = 0;
uintptr_t Offsets::Offset_MerchantSellItem = 0;
uintptr_t Offsets::Offset_MerchantBuyItem = 0;
uintptr_t Offsets::Offset_MerchantGetAllRepairCost = 0;
uintptr_t Offsets::Offset_MerchantRepairStruct = 0;
uintptr_t Offsets::Offset_MerchantRepairAllItems = 0;
uintptr_t Offsets::Offset_GetSkillIndexById = 0;
uintptr_t Offsets::Offset_UseActionBar = 0;
uintptr_t Offsets::Offset_RetrieveCorpse1 = 0;
uintptr_t Offsets::Offset_RetrieveCorpseStruct = 0;
uintptr_t Offsets::Offset_RetrieveCorpse2 = 0;
uintptr_t Offsets::Offset_RetrieveCorpseGuid = 0;
uintptr_t Offsets::Offset_GetRuneType = 0;
uintptr_t Offsets::Offset_IsRuneAtCooldown = 0;
uintptr_t Offsets::Offset_GossipSelectOption = 0;
uintptr_t Offsets::Offset_Quest_SelectActiveQuest = 0;
uintptr_t Offsets::Offset_Quest_SelectAvalibleQuest = 0;
uintptr_t Offsets::Offset_Quest_AcceptQuest = 0;
uintptr_t Offsets::Offset_Quest_IsQuestComplete = 0;
uintptr_t Offsets::Offset_Quest_GetReward = 0;
uintptr_t Offsets::Offset_Quest_GetQuestReward = 0;
uintptr_t Offsets::Offset_Quest_GetQuestRewardid = 0;

uintptr_t Offsets::Offset_LastTargetGuid = 0;

//CGUnit Offsets
uintptr_t Offsets::Offset_GetHealth = 0;
uintptr_t Offsets::Offset_GetMaxHealth = 0;

uintptr_t Offsets::Offset_UnitFlag1 = 0;
uintptr_t Offsets::Offset_UnitFlag2 = 0;
uintptr_t Offsets::Offset_UnitFlag3 = 0;
uintptr_t Offsets::Offset_DynamicFlag = 0;

uintptr_t Offsets::Offset_CreatureInfo = 0;


uint8_t Offsets::Offset_Type = 0;
uint16_t Offsets::Offset_Guid = 0;
uint16_t Offsets::Offset_Owner = 0;

uint16_t Offsets::Offset_Race = 0;
uint16_t Offsets::Offset_Class = 0;
uint16_t Offsets::Offset_Sex = 0;

uint16_t Offsets::Offset_AnimationStatus = 0;
uint16_t Offsets::Offset_GatherStatus = 0;

//CGUnit Movement Offsets
uintptr_t Offsets::Offset_Movement_Pointer = 0;        // Movement.Pointer
uintptr_t Offsets::Offset_Movement_Transport_Pointer = 0;        // Movement.TransportPointer
uintptr_t Offsets::Offset_Movement_TransportGuid = 0;           // Movement.TransportGuid
uintptr_t Offsets::Offset_Movement_Position = 0;               // Movement.Position
uintptr_t Offsets::Offset_Movement_Rotation = 0;                // Movement.Rotation
uintptr_t Offsets::Offset_Movement_Pitch = 0;                  // Movement.Pitch
uintptr_t Offsets::Offset_Movement_UnitSpeed;              // Movement.UnitSpeed
uintptr_t Offsets::Offset_Movement_MovementFlag = 0;            // Movement.Flag
uintptr_t Offsets::Offset_Movement_MovementFlagEx = 0;         // Movement.FlagEx
uintptr_t Offsets::Offset_Movement_CollisionWidth = 0;         // Movement.CollisionWidth
uintptr_t Offsets::Offset_Movement_CollisionHeight = 0;       // Movement.CollisionHeight
uintptr_t Offsets::Offset_Movement_WalkableSlope = 0;          // Movement.WalkableSlope
uintptr_t Offsets::Offset_Movement_Direction = 0;              // Movement.Direction
uintptr_t Offsets::Offset_Movement_Direction2 = 0;            // Movement.Direction2


uintptr_t Offsets::Offset_CM2ModelGetBonePosition = 0;
uintptr_t Offsets::Offset_GameTime = 0;

////
//struct OffsetsSet {
//	uintptr_t Offset_IsPlayerInWorld;
//	uintptr_t Offset_LastRedMessage;
//	uintptr_t Offset_InstanceName;
//};
//
//std::map<std::wstring, OffsetsSet> offsetsByVersion = {
//   {L"11.0.7.58238", {0x123456, 0x654321, 0x789ABC}}, // Example offsets for Retail
//   {L"4.4.1.57141", {0x234567, 0x765432, 0x89ABCD}},  // Example offsets for Classic PTR
//   {L"1.0.0", {0x345678, 0x876543, 0x9ABCDE}}         // Example offsets for SOD servers
//};
//
//if (offsetsByVersion.find(GlobalVars::GameVersion) != offsetsByVersion.end()) {
//	auto selectedOffsets = offsetsByVersion[GlobalVars::GameVersion];
//	Offset_IsPlayerInWorld = selectedOffsets.Offset_IsPlayerInWorld;
//	Offset_LastRedMessage = selectedOffsets.Offset_LastRedMessage;
//	Offset_InstanceName = selectedOffsets.Offset_InstanceName;
//
//	Print("Offsets initialized for version: ");
//	std::wcout << GlobalVars::GameVersion << L"\n";
//}
//else {
//	std::wcerr << L"Unsupported game version: " << GlobalVars::GameVersion << L". Offsets not initialized.\n";
//}

//
//uintptr_t ExtractCameraAddress(const char* pattern)
//{
//	PBYTE patternAddress = FC::FindPattern_Wrapper(pattern);
//	if (!patternAddress) {
//		std::cerr << "Pattern not found." << std::endl;
//		return 0;
//	}
//
//	// Extract the relative displacement (disp32) from the pattern
//	// The displacement is located at patternAddress + 3 (after '48 8B 05')
//	int32_t relativeOffset = *reinterpret_cast<int32_t*>(patternAddress + 3);
//
//	// Calculate the absolute address: address of next instruction + disp32
//	uintptr_t absoluteAddress = reinterpret_cast<uintptr_t>(patternAddress + 7 + relativeOffset);
//
//	std::cout << "Pattern found at: 0x" << std::hex << reinterpret_cast<uintptr_t>(patternAddress) << std::endl;
//	std::cout << "camera_46BE728 absolute address: 0x" << std::hex << absoluteAddress << std::endl;
//
//	return absoluteAddress;
//}
//
//
//uintptr_t GetDynamicOffsetFromPattern(PBYTE baseAddress)
//{
//	// After finding the base address, check the next few bytes
//	// Look for the instruction that accesses rbx + offset.
//	// For example, you might find something like "mov rax, [rbx + 0x118]"
//
//	uint8_t* code = (uint8_t*)baseAddress;
//
//	// Check the instruction right after "mov rax, [rbx + ???]"
//	// Offset will be stored in the immediate value after the instruction.
//	uintptr_t offset = 0;
//
//	// Assuming the "mov rax, [rbx + offset]" instruction is found at 'code'
//	// The actual offset is usually a 4-byte immediate value at a fixed position after the `mov rax, [rbx + ...]`
//	offset = *(uintptr_t*)(code + 3); // Offset is usually at code + 3 (can vary)
//
//	return offset; // This will return the dynamically calculated offset
//}
//
//uintptr_t GetCreatureInfoOffset()
//{
//	const char* pattern = "48 8B 83 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 33 FF 48 39 B8 ? ? ? ? 74 09 48 8B B0 ? ? ? ? EB 03";
//
//	// Locate the pattern in memory
//	PBYTE baseAddress = FC::FindPattern_Wrapper(pattern);
//
//	if (baseAddress != nullptr)
//	{
//		// Once we find the pattern, dynamically calculate the offset
//		uintptr_t dynamicOffset = GetDynamicOffsetFromPattern(baseAddress);
//
//		// Print or use the offset
//		std::cout << "Dynamic Offset: 0x" << std::hex << dynamicOffset << std::dec << std::endl;
//
//		return dynamicOffset;
//	}
//	else
//	{
//		std::cerr << "Pattern not found!" << std::endl;
//	}
//
//	return 0;
//}


void Offsets::InitStaticOffsets()
{

	//5 is a Call
	//6 is  mov eax, dword ptr cs:xmmword
	//x is 7
	//x is 7+

	auto MainInstance = (uintptr_t)GlobalVars::g_hModuleBase;
	Print("Pattern search...\n");

	// //   // Start offset initialization
	//Offset_IsPlayerInWorld = RVA((uintptr_t)FindPattern(E("0F B6 05 ? ? ? ? 0F 28 B4 24 ? ? ? ? C0 E8 05 A8 01 74 35 48 8D 05 ? ? ? ? 0F 1F 44 00 ?")), 7); // Script_IsPlayerInWorld or Script_GameMovieFinished  Cata 0F B6 05 ? ? ? ? 48 8D 15 ? ? ? ? 66 FF 05 ? ? ? ? 0F BA F0 00 0F B6 D9 88 05 ? ? ? ? 48 8D 0D ? ? ? ? 

	Offset_ClntObjMgrEnumVisibleObjectsPtr = RVA((uintptr_t)FindPattern(E("E9 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 83 3D ? ? ? ? ? 75 A6 33 D2 C7 05 ? ? ? ? ? ? ? ? 48 8D 05 ? ? ? ? C6 05 ? ? ? ? ? 48 89 05 ? ? ? ?")), 5);//////////////////(MainInstance + 0x2059360);//RVA((uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 48 8D 54 24 ? 8D 4B 72")), 5);
	Offset_ClntObjMgrGetMapId = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 8B C8 E8 ? ? ? ? 33 C0 48 83 C4 28 C3")), 5); // Script_AutoChooseCurrentGraphicsSetting First call
	Offset_ClntObjMgrIsValid = (uintptr_t)FindPattern(E("48 83 EC 28 44 0F B6 C1 48 8B 0D ? ? ? ? 48 85 C9 74 15 BA ? ? ? ? E8 ? ? ? ? 84 C0 74 07 B0 01 48 83 C4 28 C3 32 C0 48 83 C4 28 C3"));

	Offset_LastTargetGuid = RVA((uintptr_t)FindPattern(E("8B 05 ? ? ? ? 41 B9 ? ? ? ? BA ? ? ? ? 48 8D 0C 40 48 8B 05 ? ? ? ? 48 8D 0C C8 E8 ? ? ? ? 8B 1D ? ? ? ?")), 7);

	Offset_UnitReaction = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 83 F8 01 7F 0A")), 5);

	Offset_ClickToMove = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 8B D3 48 8D 0D ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? 65 48 8B 04 25 ? ? ? ? 8B 15 ? ? ? ? BE ? ? ? ? 48 8B 3C D0 8B 04 37 39 05 ? ? ? ? 7F 79")), 5);//////////////////(MainInstance + 0x2059360);//RVA((uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 48 8D 54 24 ? 8D 4B 72")), 5);  //(uintptr_t)FC::FindPattern(E("48 83 EC 48 48 83 B9 ? ? ? ? ? 7E 62"));
	Offset_FaceTo = RVA((uintptr_t)FindPattern(E("E9 ? ? ? ? C1 E8 05 A8 01 74 0B 41 B0 01 48 8B CB E8 ? ? ? ?")), 5);
	Offset_Jump = RVA((uintptr_t)FindPattern(E("E9 ? ? ? ? 41 0F BA E0 ? 41 B0 01 73 14 C1 EA 14 41 84 D0 41 8B D2")), 5); //

	Offset_InvalidPtrCheckMin = RVA((uintptr_t)FindPattern(E("40 56 48 83 EC 60 48 8B 15 ? ? ? ?")) + 6, 7);
	Offset_InvalidPtrCheckMax = RVA((uintptr_t)FindPattern(E("40 56 48 83 EC 60 48 8B 15 ? ? ? ?")) + 16, 7);
	Offset_HardwareEventPtr = (uintptr_t)FindPattern(E("40 56 48 83 EC 60 48 8B 15 ? ? ? ?"));

	//
	auto addy = (uintptr_t)FindPattern(E("4C 8D 0D ? ? ? ? 48 89 7C 24 ? 45 33 C0 48 89 7C 24 ? 48 8D 54 24 ? 48 8B CB E8 ? ? ? ? BA ? ? ? ? 48 8D 4B 18"));
	Offset_CGItem_UseItemParm = RVA(addy, 7);
	Offset_CGItem_UseItem = RVA(addy + 28, 5);

	//	///*	Offset_ScreenSize = RVA((uintptr_t)FC::FindPattern(E("8B 05 ? ? ? ? 89 03 48 8B C3 48 83 C4 ? 5B C3 8B 05")), 6);*/
	//
	Offset_Spell_C_GetMinMaxRange = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? F3 0F 10 45 ? 66 0F 6F 0D ? ? ? ? F3 0F 10 15 ? ? ? ? 0F 54 C1 0F 2F C2 73 0D F3 0F 10 45 ? 0F 54 C1 0F 2F C2 72 09")), 5);
	//Offset_Spell_C_IsCurrentSpell = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 0F B6 C0 48 83 C4 40 5B C3 33 C0")), 5);
	Offset_Spell_C_GetSpellCoolDown = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? F6 87 ? ? ? ? ? 0F 84 ? ? ? ? 48 8B 87 ? ? ? ? 48 C1 E8 3A 84 C0 0F 84 ? ? ? ?")), 5);
	Offset_Spell_C_CastSpell = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 8B D3 8B CE E8 ? ? ? ? E9 ? ? ? ? 4C 39 35 ? ? ? ?")), 5);
	Offset_Spell_C_HaveSpellPower = (uintptr_t)FindPattern(E("4C 89 4C 24 ? 4C 89 44 24 ? 89 54 24 10 53 55 56 57 41 54 41 55")); // Old one: E8 ? ? ? ? 84 C0 0F B6 E8
	//
	//
	Offset_CGUnit_IsSpellKnown = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 44 8B C3 8B D6 48 8B C8 E8 ? ? ? ? 0F B6 D0 48 8B CF E8 ? ? ? ?")) + 13, 5);  //Old one: E8 ? ? ? ? 48 8B 5C 24 ? 48 8B CF 85 C0 79 15 E8 ? ? ? ?
	Offset_SpellBook_findSlotBySpellId = (uintptr_t)FindPattern(E("44 8B CA 85 D2 0F 84 ? ? ? ? 45 84 C0 74 54 8B 51 68 45 33 C0 85 D2 74 76 4C 8B 51 70 66 90"));                                   // classic one: E8 ? ? ? ? 85 C0 79 3E")), 5); //Incorrect
	Offset_SpellBook_FindSpellByName = (uintptr_t)FindPattern(E("48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B F0 48 8B F9 48 85 D2 0F 84 ? ? ? ?")); // Script_SetMacroSpell ->Decompile   v6 = SpellBook_FindSpellByName(v5, v4, v3 + 0x59C); if (!V6)
	Offset_SpellBook_Instance = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 4C 8D 44 24 ? 48 8B D3 48 8B C8 E8 ? ? ? ? 41 B1 01 C7 44 24 ? ? ? ? ? 45 33 C0")),5);


	Offset_SpellBook_RepeatingSpellId = RVA((uintptr_t)FindPattern(E("8B 0D ? ? ? ? 85 C9 0F 84 ? ? ? ? E8 ? ? ? ? BA ? ? ? ? 41 B8 ? ? ? ? 48 8B C8 E8 ? ? ? ? 84 C0 74 08 32 C0 48 83 C4 50 5B")), 5);

	Offset_Cooldown = RVA((uintptr_t)FindPattern(E("48 8D 05 ? ? ? ? 48 1B C9 F3 0F 10 43")), 7);
	Offset_GuidToString = (uintptr_t)FindPattern(E("48 89 ? ? ? 48 89 ? ? ? 56 48 ? ? ? 41 ? ? 48 ? ? 48 ? ? 45"));
	//
	Offset_CGPlayer_C_HandleRepopRequest = (uintptr_t)FindPattern(E("40 53 48 83 EC 50 B9 ? ? ? ? 0F B6 DA E8 ? ? ? ? 84 C0 74 18"));
	//
	Offset_SpriteLeftClick = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? E9 ? ? ? ? BA ? ? ? ? E8 ? ? ? ? 0F B6 C0")), 5);
	Offset_SpriteRightClick = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 83 7F ? ? 0F B6 D8")), 5);
	//
	//	//Offset_CGUnit_C_OnAttackIconPressed = RVA((uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 48 8B 03 8B D7 48 8B CB")), 5);
	//	//Offset_CGUnit_C_IsInMelee = (uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 48 8B 03 8B D7 48 8B CB"));
	//
	//	//addy = (uintptr_t)FC::FindPattern(E("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 30 8B 15 ? ? ? ? 33 DB 65 48 8B 04 25 ? ? ? ?"));
	//	//Offset_isLootWindowOpen = RVA(addy + 143, 7); // Van start tot  einde dus Hex - hex = x en dan de 7?


		//S_LOOT_WINDOW 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B CB 66 0F 6E C8 F3 0F E6 C9 E8 ? ? ? ? B8 ? ? ? ? 48 83 C4 20


	Offset_CorpseMapID = RVA((uintptr_t)FindPattern(E("48 8D 0D ? ? ? ? 44 89 75 DF")), 7);
	Offset_CorpsePos = Offset_CorpseMapID + 0x40;
	Offset_Bool_MustEnterInstanceToRecoverBodymsg = Offset_CorpseMapID + 0x04;

	Offset_CameraMgr = RVA((uintptr_t)FindPattern(E("48 8B 05 ? ? ? ? 48 85 C0 74 08 48 8B 80 ? ? ? ? C3 C3")), 7);
	Offset_CameraPtr = GetOffsetFromPattern(E("49 8B 8E ? ? ? ? E8 ? ? ? ? 48 8B CE E8 ? ? ? ? 48 8B 6E 30 8B BE ? ? ? ? EB 27"), 3); //RAX+0x3A58


	Offset_WorldFrame_GetScreenCoordinates = (uintptr_t)FindPattern(E("4C 8B DC 49 89 5B 08 49 89 73 10 57 48 83 EC 70 48 8B F9 0F 29 74 24 ? 49 8D 4B C8 49 C7 43 ? ? ? ? ? 49 89 4B C0 41 0F B6 C1 4D 89 43 B8 49 8D 4B D0 49 89 4B B0 4D 8D 4B E0 49 8D 4B D8 49 C7 43 ? ? ? ? ?"));


	//GetWorld needs the qword.
	Offset_WorldFrame_GetWorld = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 85 C0 74 10 48 8B C8 E8 ? ? ? ? F3 0F 11 44 24 ? EB 08")), 5); // Shift+F12 -> Search ---- Shutdown ---- -> second qword or third qword (SAME) -> x ref its the first sub
	Offset_WorldFrame_Intersect = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? F3 0F 10 57 ? 84 C0")), 5);
	//
	Offset_InputControl = RVA((uintptr_t)FindPattern(E("48 8D 0D ? ? ? ? C6 44 24 ? ? BA ? ? ? ? 41 B8 ? ? ? ? C6 44 24")), 7);
	//Offset_ToggleControlBit = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 84 DB 75 2B")), 5);



	//TODO
//	////addy = (uintptr_t)FC::FindPattern(E("E8 ? ? ? ? EB 30 C1 E9 14"));
//	////Offset_Jump = RVA(addy + 50, 5);
//
//  Cvar_register ->   s_CVar_deselectOnClick x ref -> rax value the call above it.  E8 ? ? ? ? 48 89 05 ? ? ? ? E8 ? ? ? ? 44 88 7C 24 ? 48 8D 15 ? ? ? ?
// 	//TODO
	Offset_HandleTerrainClick = (uintptr_t)FindPattern(E("48 89 5C 24 ? 57 48 83 EC 30 48 83 3D ? ? ? ? ? 48 8B F9 75 0E 48 83 3D ? ? ? ? ? 75 04")); // Easiest way is to go to s_CVar_deselectOnClick x ref  (RAX val) -> Top code first call
	//
	//	//////Offset_g_CurFrame = (uintptr_t)FC::FindPattern(E("48 8B 1D X ? ? ? ? 48 85 DB 74 20 48 8B 8B ? ? ? ? 48 85 C9"));


	Offset_CanAttack = RVA((uintptr_t)FindPattern(E("74 1E 49 8B D6 48 8B CE E8 ? ? ? ? 84 C0 74 0F B9 ? ? ? ? E8 ? ? ? ? E9 ? ? ? ?")) + 8, 5);   //RVA((uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? B0 01")), 5);
	Offset_IsOutDoors = RVA((uintptr_t)FindPattern(E("48 83 EC 28 48 8B 49 30 48 85 C9 74 18 48 8B 01 FF 50 58")), 5);//RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 84 C0 75 22 8D 4B 72 E8 ? ? ? ? 45 33 C9 48 8B C8")), 5);
	//
	//	//////CGUnit_C__Dismount  in Script_Dismount
	Offset_Dismount = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? F6 83 ? ? ? ? ? 75 0C")), 5);         //E8 ? ? ? ? 48 8B CF E8 ? ? ? ? 84 C0 74 37 48 8B CF E8 ? ? ? ? 4C 8D 4D 67 45 33 C0 8B D0 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 0D")), 5); // Old one E8 ? ? ? ? F6 83 ? ? ? ? ? 75 0C Script_Dismount 3rd call

	Offset_GetItemCacheEntry = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 8B F8 48 85 C0 74 51 48 8B C8 E8 ? ? ? ? E8 ? ? ? ?")), 5); //
	Offset_ItemCacheEntryBase = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 8B F8 48 85 C0 74 51 48 8B C8 E8 ? ? ? ? E8 ? ? ? ?") - 9), 7);

	Offset_Merchant_unk_arg = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? C7 44 24 ? ? ? ? ? 48 8B C8 C6 44 24 ? ? 48 8B 54 24 ? E8 ? ? ? ? 48 8D 4C 24 ? 0F 10 00 0F B6 05")), 5);                        //("E8 ? ? ? ? 80 7B 30 00")), 5); // Script_CloseTaxiMap First Call
	Offset_Merchant = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 8B 40 08 48 C1 E8 3A 84 C0 74 52 E8 ? ? ? ? 05 ? ? ? ? C6 05")), 5); ///("E8 ? ? ? ? 4C 8B 0F 4C 39 08")), 5); // Script_CheckInbox Second call is Merchant_unk_arg third call is Merchant
	Offset_MerchantItems = RVA((uintptr_t)FindPattern(E("48 8B 1D ? ? ? ? 48 03 FB 48 3B DF 74 1C 48 8D 4B 28 E8 ? ? ? ? 48 81 C3 ? ? ? ? 48 3B DF 75 EB 48 8B 1D ? ? ? ? 48 B8")), 7); // Script_GetMerchantNumItems cs:MerchantItems
	Offset_MerchantCount = RVA((uintptr_t)FindPattern(E("48 69 3D ? ? ? ? ? ? ? ? 48 8B 1D ? ? ? ? 48 03 FB 48 3B DF 74 1C 48 8D 4B 28 E8 ? ? ? ? 48 81 C3 ? ? ? ?")), 7); // Easiest way it to x ref JamCliVendorItem you will find the MerchantItem and Count there.
	Offset_MerchantItemsInfoSize = 0x98; // Beneat MerchantCounnt/Item  add rbx, 98h
	Offset_MerchantItemsInfoStackCount = 0x0;
	Offset_MerchantSellItem = RVA((uintptr_t)FindPattern(E("48 8B 54 24 ? E8 ? ? ? ? 44 8B C3 48 8D 54 24 ? 48 8B C8 E8 ? ? ? ? 33 C0 48 83 C4 30 5B C3")) + 15, 5);     //("E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 48 8D 4D C0")), 5);
	Offset_MerchantBuyItem = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 8B 5C 24 ? 48 8B 74 24 ? 33 C0 48 83 C4 40 5F C3")), 5);
	Offset_MerchantGetAllRepairCost = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 8B D8 0F 57 C9 48 8B CF F2 48 0F 2A CB E8 ? ? ? ? 33 D2 48 8B CF")), 5);

	Offset_MerchantRepairStruct = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? E8 ? ? ? ? C7 84 24 ? ? ? ? ? ? ? ? 48 8B C8 C6 84 24 ? ? ? ? ? 48 8B 94 24 ? ? ? ? E8 ? ? ? ? 48 8D 4C 24 ? 0F 10 00 33 C0")), 5);
	Offset_MerchantRepairAllItems = RVA((uintptr_t)FindPattern(E("B9 ? ? ? ? E8 ? ? ? ? 33 C0 48 8B 9C 24 ? ? ? ? 48 81 C4 ? ? ? ? 5F")) + 5, 5);  // 48 89 44 24 ? E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? 33 C0 48 83 C4 70)) + 5, 5);
	//
	//
	Offset_GetSkillIndexById = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 8B C8 0F B7 94 4B ? ? ? ? 89 94 24 ? ? ? ? 85 D2 74 11 0F B7 84 4B ? ? ? ? 03 D0 89 94 24 ? ? ? ?")), 5);
	Offset_UseActionBar = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 0F 28 45 E0 48 8D 55 F0 44 0F B6 CF 66 0F 7F 45 ? 4C 8B C0 48 8D 4D 40 E8 ? ? ? ?")) + 29, 5);
	//
	//	//Offset_RetriveCorpse1 = (uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 0F 10 05 ? ? ? ? 48 8D 4C 24 ?"));;
	//	//addy = (uintptr_t)FC::FindPattern(E("74 0D BA ? ? ? ? 48 8B C8 E8 ? ? ? ? 48 8D 4C 24"));
	//	//Offset_RetriveCorpseStruct = RVA(addy + 0x14, 5);
	//	//Offset_RetriveCorpse2 = RVA(addy + 0x2A, 5);
	//	//Offset_RetriveCorpseGuid = RVA(addy + 0x19, 7);
	//
	//	//Offset_GetRuneType = 0x00;
	//	////Offset_IsRuneColldown = RVA((uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 8B F8 E8 ? ? ? ? 3B C7")), 5);
	//
	//	//Offset_CanUse = RVA((uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 84 C0 74 68 0F B6 47 10")), 5); // E8 ? ? ? ? 84 C0 74 6A 0F B6 47 10
	//	////Offset_GameObjectCanUseNow = RVA((uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 84 C0 74 82 B0 01")), 5);
	//	//Offset_GameObjectIsLocked = RVA((uintptr_t)FC::FindPattern(E("E8 ? ? ? ? 44 39 6C 24 ? 74 50")), 5);
	addy = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 8B D8 E8 ? ? ? ? 48 8B C8 4C 8B C3 8B D6 E8 ? ? ? ? 48 8B 5C 24 ?")), 5);
	Offset_LastRedMessage = RVA(addy, 7); // Inventory is full.
	//
	//	//addy = RVA((uintptr_t)FC::FindPattern(E("48 8B 0D ? ? ? ? 4C 8D 44 24 ? 48 83 C1 20 48 89 5C 24 ?")), 7);
	//	//Offset_InstanceName = (uintptr_t)(addy)+0x60; // E8 ? ? ? ? 39 45 F7 qword + Check in reclass
	//
	//Offset_GossipSelectOption = (uintptr_t)FindPattern(E("48 89 74 24 ? 66 44 89 44 24 ? 57 48 81 EC ? ? ? ?"));
	Offset_GameTime = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 44 8B C0 48 8D 54 24 ? 45 33 C9 8B CB E8 ? ? ? ? 48 83 C4 50 5B C3")), 5);

	//	/*Offset_Gossip = (uintptr_t)FC::FindPattern(E("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 49 8B F0 48 8B FA 4C 8B C2"));
	//	Offset_GossipCInfo = (MainInstance + 0x26346E8);
	//	Offset_GossipSelectOptionByIdx = (MainInstance + 0x2634860);*/
	//	//Offset_GetQuestFrameUnitGuid = 0x00;

	Offset_Quest_SelectActiveQuest = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 33 C0 C7 05 ? ? ? ? ? ? ? ? 48 83 C4 20 5B C3 E8 ? ? ? ?")), 5);
	Offset_Quest_SelectAvalibleQuest = RVA((uintptr_t)FindPattern(E("48 8B 0D ? ? ? ? 48 69 D3 ? ? ? ? 44 8B 04 0A 80 BC 0A ? ? ? ? ? 48 8D 15 ? ? ? ? 48 8B C8 74 1A 45 33 C9 E8 ? ? ? ? 33 C0 C7 05")), 5);
	Offset_Quest_AcceptQuest = (uintptr_t)FindPattern(E("40 55 48 8B EC 48 81 EC ? ? ? ? 83 3D ? ? ? ? ? 0F 85 ? ? ? ? 48 89 5C 24 ?"));
	Offset_Quest_IsQuestComplete = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 83 F8 02 75 14 8B 8C 24 ? ? ? ? E8 ? ? ? ? 84 C0 0F 84 ? ? ? ?")), 5); // Might be wrong.
	Offset_Quest_GetReward = RVA((uintptr_t)FindPattern(E("48 3B 05 ? ? ? ? 73 2F 48 69 C8 ? ? ? ? 48 8B 05 ? ? ? ? 83 3C 01 01 75 1B 8B 54 01 08 EB 17")), 7);
	Offset_Quest_GetQuestReward = RVA((uintptr_t)FindPattern(E("E8 ? ? ? ? 48 8D 4C 24 ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 48 8B B4 24 ? ? ? ? 48 8B 9C 24 ? ? ? ?")), 5);
	Offset_Quest_GetQuestRewardid = RVA((uintptr_t)FindPattern(E("48 03 0D ? ? ? ? E8 ? ? ? ? FF C3 3B 1D ? ? ? ? 72 DD 48 8B 0D ? ? ? ?")), 7);

	//All of these are Offy
	Offset_Type = 0x8;
	Offset_Guid = 0x18;

	Offset_Movement_Pointer = 0xA0;         // Movement.Pointer
	Offset_Movement_Transport_Pointer = 0x0;         // Movement.TransportPointer
	Offset_Movement_TransportGuid = 0x10;           // Movement.TransportGuid
	Offset_Movement_Position = 0x18;                // Movement.Positioni
	Offset_Movement_Rotation = 0x28;                // Movement.Rotation
	Offset_Movement_Pitch = 0x154;                  // Movement.Pitch
	Offset_Movement_UnitSpeed = 0x1A0;              // UnitSpeed
	Offset_Movement_MovementFlag = 0xF8;            // Movement.Flag
	Offset_Movement_MovementFlagEx = 0xFC;          // Movement.FlagEx
	Offset_Movement_CollisionWidth = 0x244;         // Movement.CollisionWidth
	Offset_Movement_CollisionHeight = 0x248;        // Movement.CollisionHeight
	Offset_Movement_WalkableSlope = 0x24C;          // Movement.WalkableSlope
	//Offset_Movement_Direction = 0x110;              // Movement.Direction
	//Offset_Movement_Direction2 = 0x170;             // Movement.Direction2




	//Offset_Race = 0x188; // 8B 81 ? ? ? ? 85 C0 74 ? F6 81 ? ? ? ? ? 74 ? 0F B6 81 ? ? ? ? C3
	//Offset_Class = Offset_Race + 0x1;
	//Offset_Sex = Offset_Race + 0x2;


	//lvl CEC8                  E0B4
	//CEA4 returns 1           E0A4
	//CEA8 returns 5            E0A8
	//CEC4 returns 2            E0B0

	//Offset_UnitFlag1 = 0x1948;
	Offset_UnitFlag1 = GetOffsetFromPattern(E("F7 87 ? ? ? ? ? ? ? ? 0F 85 ? ? ? ? 48 8B CF E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 8B CF"), 3);
	Offset_UnitFlag2 = Offset_UnitFlag1 + 0x4;
	Offset_UnitFlag3 = Offset_UnitFlag2 + 0x4;

	Offset_DynamicFlag = 0xDC; // Probably wrong.

	//Power is 16D8
	Offset_GetHealth = GetOffsetFromPattern(E("48 8B 83 ? ? ? ? 0F 57 C0 F2 48 0F 2A C0 EB 1D 48 8B 83 ? ? ? ? 0F 57 C0"), 3);//0x16D0;	cvar health  below in this func is also GetHealth and GetMaxHealth
	Offset_GetMaxHealth = GetOffsetFromPattern(E("F2 48 0F 2A 87 ? ? ? ? F2 0F 5E C8 66 0F 5A C9 0F 2F 0D ? ? ? ? 73 20 48 8B 07 48 8B CF"), 5); // or Offsets_GetHealth + 0x8
	Offset_CreatureInfo = GetOffsetFromPattern(E("48 8B 83 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? 33 FF 48 39 B8 ? ? ? ? 74 09 48 8B B0 ? ? ? ? EB 03"), 3);



	// //   Offset_Owner = 0x210;
//S
//	//Offset_AnimationStatus = 0xA0;
// 
// 
//   UnitCreate info,type ffam,rank,gathertype,name = 48 89 5C 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4D 8B F1
// 
//
	Offset_AuraCount = GetOffsetFromPattern(E("85 C9 78 73 48 89 5C 24 ? 56 48 83 EC 20"), 3); //0x598 85 C9 78 ? 48 89 5C 24 ?
	Offset_AuraTable = Offset_AuraCount + 0x8;
	Offset_AuraSize = 0xC8; // C8?


	//========-------
	std::string leftSeparator = "========-------";
	std::string rightSeparator = "-------========";

#if DebugConsole
	Print("%sPattern search completed%s\n", leftSeparator, rightSeparator);
#endif

	Print("%sX-HOOK Pattern output:%s\n", leftSeparator, rightSeparator);

	Print("%sClntObjMgr functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_ClntObjMgrEnumVisibleObjectsPtr);
	Addy(Offset_ClntObjMgrGetMapId);
	Addy(Offset_ClntObjMgrIsValid);

	Print("%sMovement functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_ClickToMove);
	Addy(Offset_FaceTo);
	Addy(Offset_Jump);

	Print("%sValidation functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_InvalidPtrCheckMin);
	Addy(Offset_InvalidPtrCheckMax);
	Addy(Offset_HardwareEventPtr);

	Print("%sItem functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_CGItem_UseItemParm);
	Addy(Offset_CGItem_UseItem);

	Print("%sSpell functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_Spell_C_GetMinMaxRange);
	Addy(Offset_Spell_C_IsCurrentSpell);
	Addy(Offset_Spell_C_GetSpellCoolDown);
	Addy(Offset_Spell_C_CastSpell);
	Addy(Offset_Spell_C_HaveSpellPower);
	Addy(Offset_SpellBook_findSlotBySpellId);
	Addy(Offset_SpellBook_FindSpellByName);
	Addy(Offset_SpellBook_Instance);
	Addy(Offset_SpellBook_RepeatingSpellId);
	Addy(Offset_CGUnit_IsSpellKnown);

	Print("%sGeneral Unit functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_UnitReaction);
	Addy(Offset_Cooldown);
	Addy(Offset_GuidToString);

	Print("%sCGPlayer functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_CGPlayer_C_HandleRepopRequest);

	Print("%sCGGameObject functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_CGGameObject_C_CanUse);
	Addy(Offset_CGGameObject_C_CanUseNow);
	Addy(Offset_CGGameObject_C_IsLocked);

	Print("%sSprite functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_SpriteLeftClick);
	Addy(Offset_SpriteRightClick);

	Print("%sCombat functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_CGUnit_C_OnAttackIconPressed);
	Addy(Offset_CGUnit_C_IsInMelee);


	Print("%sCamera functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_Bool_MustEnterInstanceToRecoverBodymsg);
	Addy(Offset_CameraMgr);
	Offy(Offset_CameraPtr);

	Print("%sWorldFrame functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_WorldFrame_GetWorld);
	Addy(Offset_WorldFrame_Intersect);
	Addy(Offset_WorldFrame_GetScreenCoordinates);

	Print("%sInput functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_InputControl);
	Addy(Offset_ToggleControlBit);
	Addy(Offset_HandleTerrainClick);

	Print("%sAttack functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_CanAttack);
	Addy(Offset_IsOutDoors);
	Addy(Offset_Dismount);

	Print("%sItemCache functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_GetItemCacheEntry);
	Addy(Offset_ItemCacheEntryBase);

	Print("%sMerchant functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_Merchant_unk_arg);
	Addy(Offset_Merchant);
	Addy(Offset_MerchantItems);
	Addy(Offset_MerchantCount);
	Offy(Offset_MerchantItemsInfoSize);
	Offy(Offset_MerchantItemsInfoStackCount);
	Addy(Offset_MerchantSellItem);
	Addy(Offset_MerchantBuyItem);
	Addy(Offset_MerchantGetAllRepairCost);
	Addy(Offset_MerchantRepairStruct);
	Addy(Offset_MerchantRepairAllItems);

	Print("%sSkill functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_GetSkillIndexById);
	Addy(Offset_UseActionBar);

	Print("%sCorpse Retrieval functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_RetrieveCorpse1);
	Addy(Offset_RetrieveCorpseStruct);
	Addy(Offset_RetrieveCorpse2);
	Addy(Offset_RetrieveCorpseGuid);
	Addy(Offset_CorpseMapID);
	Addy(Offset_CorpsePos);

	Print("%sRune functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_GetRuneType);
	Addy(Offset_IsRuneAtCooldown);

	Print("%sGossip functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_GossipSelectOption);

	Print("%sTarget functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_LastTargetGuid);

	Print("%sBone Position functions dunno if we can get this working THO:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_CM2ModelGetBonePosition);

	Print("%sGameTime functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_GameTime);

	Print("%sQuest functions:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_Quest_SelectActiveQuest);
	Addy(Offset_Quest_SelectAvalibleQuest);
	Addy(Offset_Quest_AcceptQuest);
	Addy(Offset_Quest_IsQuestComplete);
	Addy(Offset_Quest_GetReward);
	Addy(Offset_Quest_GetQuestReward);
	Addy(Offset_Quest_GetQuestRewardid);


	Print("%sOther:%s\n", leftSeparator, rightSeparator);
	Addy(Offset_isLootWindowOpen);


	Addy(Offset_IsPlayerInWorld);
	Addy(Offset_LastRedMessage);
	Addy(Offset_InstanceName);

	Print("%sUnit Attributes:%s\n", leftSeparator, rightSeparator);
	Offy(Offset_Type);
	Offy(Offset_Guid);
	Offy(Offset_Owner);
	Offy(Offset_Race);
	Offy(Offset_Class);
	Offy(Offset_Sex);
	Offy(Offset_AnimationStatus);
	Offy(Offset_GatherStatus);

	Offy(Offset_GetHealth);
	Offy(Offset_GetMaxHealth);
	Offy(Offset_UnitFlag1);
	Offy(Offset_UnitFlag2);
	Offy(Offset_UnitFlag3);
	Offy(Offset_DynamicFlag);

	Offy(Offset_CreatureInfo);

	Print("%sMovement functions:%s\n", leftSeparator, rightSeparator);
	Offy(Offset_Movement_Pointer);
	Offy(Offset_Movement_Transport_Pointer);
	Offy(Offset_Movement_TransportGuid);
	Offy(Offset_Movement_Position);
	Offy(Offset_Movement_Rotation);
	Offy(Offset_Movement_Pitch);
	Offy(Offset_Movement_UnitSpeed);
	Offy(Offset_Movement_MovementFlag);
	Offy(Offset_Movement_MovementFlagEx);
	Offy(Offset_Movement_CollisionWidth);
	Offy(Offset_Movement_CollisionHeight);
	Offy(Offset_Movement_WalkableSlope);
	Offy(Offset_Movement_Direction);
	Offy(Offset_Movement_Direction2);

	Print("%sAura functions:%s\n", leftSeparator, rightSeparator);
	Offy(Offset_AuraCount);
	Offy(Offset_AuraTable);
	Offy(Offset_AuraSize);
}
