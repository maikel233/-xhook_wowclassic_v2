#include "SpellBook.h"

#include "../GameMethods.h"
#include "../Utils/Utils.h"
#include "../Offsets.h"
#include <mutex>



static inline bool pSpellBook::Spell_C_IsCurrentSpell(int SpellId) {
	SetUnhandledExceptionFilter(Utils::VectoredHandler);
#if Logger
	Utils::logger("start");
#endif
	typedef bool(__cdecl* tIsCurrentSpellBySpellId)(int);
	tIsCurrentSpellBySpellId IsCurrentSpellBySpellId = (tIsCurrentSpellBySpellId)Offsets::Offset_Spell_C_IsCurrentSpell;
	auto res = IsCurrentSpellBySpellId(SpellId);
#if Logger
	Utils::logger("end");
#endif
	return res;
}

static inline int64_t pSpellBook::Spell_C_GetMinMaxSpellRange(int32_t SpellId, float_t* MinRange, float_t* MaxRange, CGGuid* TargetGuid) {
	auto res = reinterpret_cast<int64_t(__fastcall*)(int64_t playerPtr, int32_t, float_t*, float_t*, CGGuid*, int64_t)>(Offsets::Offset_Spell_C_GetMinMaxRange)(GlobalVars::LocalPlayer->Ptr(), SpellId, MinRange, MaxRange, TargetGuid, 0);
	return res;
}


bool pSpellBook::Spell_C_HaveSpellPower(int32_t spellId) {
	uint32_t unk0 = 0;
	uint32_t unk1 = 0;
	auto res = reinterpret_cast<bool(__fastcall*)(int64_t, int32_t, uint32_t * flag1, uint32_t * flag2)>(Offsets::Offset_Spell_C_HaveSpellPower)(GlobalVars::LocalPlayer->Ptr(), spellId, &unk0, &unk1);

	return res;
}

static inline int64_t pSpellBook::Spell_C_CastSpell(int32_t spellSlot, CGGuid* targetGuid) {
	auto res = reinterpret_cast<int64_t(__fastcall*)(int32_t, int32_t, CGGuid*, uint8_t, uint8_t)>(Offsets::Offset_Spell_C_CastSpell)(spellSlot, 0, targetGuid, 0, 0);
	return res;
}

bool pSpellBook::Spell_C_GetSpellCooldown(uint32_t spellId, int64_t* duration, int64_t* startTime, int64_t* modRate) {
	return reinterpret_cast<bool(__fastcall*)(uint32_t /* SpellId*/, int32_t /* Unk*/, int32_t/* isPet*/, int64_t* /* Duration*/, int64_t* /* StartTime*/, int64_t* /* IsEnabled??*/, int64_t* /* UNK3*/, int64_t*, int64_t*)>(Offsets::Offset_Spell_C_GetSpellCoolDown)(spellId, 0, 0, duration, startTime, 0, 0, 0, modRate);
}

bool pSpellBook::IsSpellKnown(int32_t spellId) {

	auto res = reinterpret_cast<bool(__fastcall*)(int64_t, int32_t, int32_t)>(Offsets::Offset_CGUnit_IsSpellKnown)(spellId, 0, 0); //GlobalVars::LocalPlayer->Ptr(), spellId, 0);

	return res;
}

int64_t pSpellBook::FindSlotBySpellId(int32_t spellId) {
	auto res = reinterpret_cast<int64_t(__fastcall*)(int64_t a1, int32_t, int32_t)>(Offsets::Offset_SpellBook_findSlotBySpellId)(0, spellId, 0);
	return res;
}

bool pSpellBook::CastSpell(WObject* Unit, int SpellID, const char* spellName = "") {
	SetUnhandledExceptionFilter(Utils::VectoredHandler);
	__try
	{
		/*for (int i = 0; i < GlobalVars::spellWithOverloadEnt.size(); ++i) {
			if (SpellID == GetSpellIdByName(GlobalVars::spellWithOverloadEnt[i])) {
				Unit = GlobalVars::LocalPlayer;
				break;
			}
		}*/

		if (!Unit->IsDead() && !Unit->IsLootable())
		{
			//if (Unit->GetGuid() != GlobalVars::LocalPlayer->GetGuid()) {
			//	SetFacing(Unit->GetPosition());
			//}

//			if (
//				Unit->GetGuid() != GlobalVars::LocalPlayer->GetGuid() &&
//				((abs(Utils::GetFloatPrecision(GetAngel(Unit->GetPosition()), 2) -
//					Utils::GetFloatPrecision(GlobalVars::LocalPlayer->r(), 2))) >= 1.F)
//				)
//			{
//#if Logger
//				Utils::logger("end");
//#endif
//				return false;
//			}

			if (!Spell_C_HaveSpellPower(SpellID)) {
#if Logger
				Utils::logger("end");
#endif
				return false;
			}


			if (Unit->GetGuid() != GlobalVars::LocalPlayer->GetGuid()) {

				float_t min = 0;
				float_t max = 0;
				Spell_C_GetMinMaxSpellRange(SpellID, &min, &max, Unit->GetGuid());

				if (GlobalVars::LocalPlayer->GetUnitPosition().DistanceTo(Unit->GetUnitPosition()) >= max) {

					return false;
				}
			}


			////int64_t duration = 0;
			////uint32_t startTime = 0;
			////int64_t modRate = 1;
			////Spell_C_GetSpellCooldown(SpellID, &duration, &startTime, &modRate);
			//////int CastDuration = startTime + duration - (int)GameMethods::getCurrentTime();

			/////*auto count = (int)ObjectManager::getCurrentTime();
			////auto result = start + duration - count;*/

			////if (duration > 0 || startTime > 0) {
			////	return false;
			////}


			if (!IsSpellKnown(SpellID))
			{
#if Logger
				Utils::logger("end");
#endif
				return false;
			}

			int32_t spellSlot = FindSlotBySpellId(SpellID);
			if (!spellSlot) {
#if Logger
				Utils::logger("end");
#endif
				return false;
			}

			std::cout << "Spell: " << spellName << std::endl;

			/*StopMovement(16);
			if (GlobalVars::LocalPlayer->IsPlayerMoving()) {
				GameMethods::ClickToMove(GlobalVars::LocalPlayer->Ptr(), GlobalVars::LocalPlayer->GetPosition());
				StopMovement(16);
			}*/

			Spell_C_CastSpell(spellSlot, Unit->GetGuid());

			//ObjectManager::SetHardwareEvent();

			//for (int j = 0; j < GlobalVars::spellNeedTerClk.size(); ++j) {
			//	if (SpellID == GetSpellIdByName(GlobalVars::spellNeedTerClk[j])) {
			//		auto pos = GlobalVars::LocalPlayer->GetPosition();
			//		pos.z += 0.5;
			//		HandleTerrainClick(pos);
			//		break;
			//	}
			//}
#if Logger
			Utils::logger("end");
#endif
			return true;
		}
	}
	__except (1) {}
}






//
////[WARNING] 3ARGS __int64 __fastcall SpellBook_FindSpellByName(__int64 a1, char *a2, bool *a3)
//////////int64_t pSpellBook::SpellBook_FindSpellByName(const char* SpellName, uint64_t* unk) {
//////////    auto res = reinterpret_cast<int64_t(__fastcall*)(const char*, uint64_t*)>(
//////////        Offsets::Offset_SpellBook_FindSpellByName)(SpellName, unk);
//////////    return res;
//////////}
//
//int64_t pSpellBook::SpellBook_FindSpellByName(int64_t a1, const char* SpellName, bool* outFlag) {
//    SetUnhandledExceptionFilter(Utils::VectoredHandler);
//    auto res = reinterpret_cast<int64_t(__fastcall*)(int64_t, const char*, bool*)>(
//        Offsets::Offset_SpellBook_FindSpellByName)(a1, SpellName, outFlag);
//    return res;
//}
//
//
//
//bool pSpellBook::IsInRange(SpellId spellId, WObject* target) {
//    SetUnhandledExceptionFilter(Utils::VectoredHandler);
//    if (!target) return false;
//
//    float minRange = 0.0f, maxRange = 0.0f;
//    auto fn = reinterpret_cast<bool(__fastcall*)(WObject*, SpellId, float*, float*, WObject*)>(
//        Offsets::Offset_Spell_C_GetMinMaxRange
//        );
//
//    fn(nullptr, spellId, &minRange, &maxRange, nullptr);
//
//    float distance = GlobalVars::LocalPlayer->GetUnitPosition().DistanceTo(target->GetUnitPosition());
//
//    return distance <= maxRange;
//
//    //int64_t pSpellBook::Spell_C_GetMinMaxSpellRange(int32_t SpellId, float* MinRange, float* MaxRange, CGGuid* TargetGuid){
////    auto fn = reinterpret_cast<int64_t(__fastcall*)(int64_t, int32_t, float*, float*, CGGuid*, int64_t)>(
////        Offsets::Offset_Spell_C_GetMinMaxRange
////        );
////    int64_t res = fn(GlobalVars::LocalPlayer->Ptr(), SpellId, MinRange, MaxRange, TargetGuid, 0);
////
////    return res;
////}
//}
//
//bool pSpellBook::Spell_C_HaveSpellPower(int32_t spellId){
//    SetUnhandledExceptionFilter(Utils::VectoredHandler);
//
//    uint32_t unk0 = 0;
//    uint32_t unk1 = 0;
//    auto fn = reinterpret_cast<bool(__fastcall*)(int64_t, int32_t, uint32_t*, uint32_t*)>(
//        Offsets::Offset_Spell_C_HaveSpellPower
//        );
//    bool res = fn(GlobalVars::LocalPlayer->Ptr(), spellId, &unk0, &unk1);
//
//    return res;
//}
//
//bool pSpellBook::CastSpellById(SpellId spellId, WObject* target) {
//    SetUnhandledExceptionFilter(Utils::VectoredHandler);
//    SpellSlot spellSlot = FindSlotBySpellId(spellId);
//    if (spellSlot < 0) return false;
//
//    auto fn = reinterpret_cast<int64_t(__fastcall*)(int64_t, SpellSlot, int32_t, WObject*, uint8_t, uint8_t)>(
//       Offsets::Offset_Spell_C_CastSpell
//        );
//
//    fn(0, spellSlot, 0, target, 0, 0);
//    return true;
//
//
//    //int64_t pSpellBook::Spell_C_CastSpell(int32_t spellSlot, CGGuid * targetGuid) {
//    //    auto fn = reinterpret_cast<int64_t(__fastcall*)(int32_t, int32_t, CGGuid*, uint8_t, uint8_t)>(
//    //        Offsets::Offset_Spell_C_CastSpell
//    //        );
//    //    int64_t res = fn(spellSlot, 0, targetGuid, 0, 0);
//
//    //    return res;
//    //}
//
//}
//
//
//
//int64_t pSpellBook::GetSpellCooldown(pSpellBook::SpellId spellId, int32_t isPet)
//{
//    SetUnhandledExceptionFilter(Utils::VectoredHandler);
//    int64_t enabled = 0;
//    int64_t duration = 0, startTime = 0, modRate = 1;
//
//    // Function pointer to match the old structure
//    auto fn = reinterpret_cast<bool(__fastcall*)(uint32_t, int32_t, int32_t, uint32_t*, int64_t*, int64_t*, int64_t, int32_t, int64_t, int64_t)>(
//        Offsets::Offset_Spell_C_GetSpellCoolDown
//        );
//
//    // Call the function with appropriate parameters
//    bool res = fn(spellId, 0, isPet, (uint32_t*)&startTime, &duration, &modRate, 0, 0, 0, 0);
//
//    if (duration <= 0)
//        return 0;
//
//    return duration - (GameMethods::GameTime() - startTime);
//}
//
////[WARNING] Now has 3 args. char __fastcall sub_299FA60(__int64 a1, __int64 a2, unsigned __int8 a3) 
//bool pSpellBook::IsSpellKnown(SpellId spellId){
//    SetUnhandledExceptionFilter(Utils::VectoredHandler);
//    auto fn = reinterpret_cast<bool(__fastcall*)(int32_t, int32_t)>(Offsets::Offset_CGUnit_IsSpellKnown);
//    bool res = fn(spellId, 0);
//    return res;
//}
//
////[WARNING] 3ARGS        signed __int64 __fastcall findSlotBySpellId(__int64 a1, int a2, char a3)  
//int64_t pSpellBook::FindSlotBySpellId(SpellId spellId){
//    SetUnhandledExceptionFilter(Utils::VectoredHandler);
//    auto fn = reinterpret_cast<int64_t(__fastcall*)(int32_t,int32_t, bool isPet)>(Offsets::Offset_SpellBook_findSlotBySpellId);
//    int64_t res = fn(0,spellId, false);
//
//    return res;
//}
//
//////int pSpellBook::GetSpellIdByName(const char* SpellName) {
//////
//////    int SpellId = pSpellBook::SpellBook_FindSpellByName(SpellName, &Dummy);
//////
//////    return SpellId;
//////}
//
//
//int pSpellBook::GetSpellIdByName(int64_t a1, const char* SpellName, bool Dummy) {
//    SetUnhandledExceptionFilter(Utils::VectoredHandler);
// //   bool Dummy = false; // Stores spell validity
//    int SpellId = static_cast<int>(pSpellBook::SpellBook_FindSpellByName(a1, SpellName, &Dummy));
//    return SpellId;
//}
//
//
//bool pSpellBook::IsOnCooldown(SpellId spellId)
//{
//    return GetSpellCooldown(spellId, 0) > 0;
//}
//
//bool pSpellBook::IsSpellLearned(SpellId spellId)
//{
//    return pSpellBook::FindSlotBySpellId(spellId) != 0;
//}
//
//bool pSpellBook::CanCast(SpellId spellId)
//{
//    return pSpellBook::CanCast(spellId, GlobalVars::LocalPlayer);
//}
//
//bool pSpellBook::CanCast(SpellId spellId, WObject* target)
//{
//    return pSpellBook::IsSpellLearned(spellId) && !pSpellBook::IsOnCooldown(spellId)
//        && pSpellBook::Spell_C_HaveSpellPower(spellId) && pSpellBook::IsInRange(spellId, target);
//}

//
//bool CastSpell(WObject* Unit, int SpellID, const char* spellName = "") {
//	__try
//	{
//		/*for (int i = 0; i < GlobalVars::spellWithOverloadEnt.size(); ++i) {
//			if (SpellID == GetSpellIdByName(GlobalVars::spellWithOverloadEnt[i])) {
//				Unit = GlobalVars::LocalPlayer;
//				break;
//			}
//		}*/
//
//		if (!Unit->IsDead() && !Unit->IsLootable())
//		{
//			if (Unit->GetGuid() != GlobalVars::LocalPlayer->GetGuid()) {
//				SetFacing(Unit->GetPosition());
//			}
//
//			if (
//				Unit->GetGuid() != GlobalVars::LocalPlayer->GetGuid() &&
//				((abs(Utils::GetFloatPrecision(GetAngel(Unit->GetPosition()), 2) -
//					Utils::GetFloatPrecision(GlobalVars::LocalPlayer->r(), 2))) >= 1.F)
//				)
//			{
//#if Logger
//				Utils::logger("end");
//#endif
//				return false;
//			}
//
//			if (!GameMethods::Spell_C_HaveSpellPower(SpellID)) {
//#if Logger
//				Utils::logger("end");
//#endif
//				return false;
//			}
//
//
//			if (Unit->GetGuid() != GlobalVars::LocalPlayer->GetGuid()) {
//
//				float_t min = 0;
//				float_t max = 0;
//				GameMethods::Spell_C_GetMinMaxSpellRange(SpellID, &min, &max, Unit->GetGuid());
//
//				if (GlobalVars::LocalPlayer->GetPosition().DistanceTo(Unit->GetPosition()) >= max) {
//#if Logger
//					Utils::logger("end");
//#endif
//					return false;
//				}
//			}
//
//
//			int64_t duration = 0;
//			uint32_t startTime = 0;
//			int64_t modRate = 1;
//			GameMethods::Spell_C_GetSpellCooldown(SpellID, &duration, &startTime, &modRate);
//			//int CastDuration = startTime + duration - (int)GameMethods::getCurrentTime();
//
//			/*auto count = (int)ObjectManager::getCurrentTime();
//			auto result = start + duration - count;*/
//
//			if (duration > 0 || startTime > 0) {
//#if Logger
//				Utils::logger("end");
//#endif
//				return false;
//			}
//
//
//			if (!GameMethods::IsSpellKnown(SpellID))
//			{
//#if Logger
//				Utils::logger("end");
//#endif
//				return false;
//			}
//
//			int32_t spellSlot = GameMethods::FindSlotBySpellId(SpellID);
//			if (!spellSlot) {
//#if Logger
//				Utils::logger("end");
//#endif
//				return false;
//			}
//
//			//std::cout << "Spell: " << spellName << std::endl;
//
//			StopMovement(16);
//			if (GlobalVars::LocalPlayer->IsPlayerMoving()) {
//				GameMethods::ClickToMove(GlobalVars::LocalPlayer->Ptr(), GlobalVars::LocalPlayer->GetPosition());
//				StopMovement(16);
//			}
//
//			GameMethods::Spell_C_CastSpell(spellSlot, Unit->GetGuid());
//
//			ObjectManager::SetHardwareEvent();
//
//			for (int j = 0; j < GlobalVars::spellNeedTerClk.size(); ++j) {
//				if (SpellID == GetSpellIdByName(GlobalVars::spellNeedTerClk[j])) {
//					auto pos = GlobalVars::LocalPlayer->GetPosition();
//					pos.z += 0.5;
//					HandleTerrainClick(pos);
//					break;
//				}
//			}
//#if Logger
//			Utils::logger("end");
//#endif
//			return true;
//		}
//	}
//	__except (1) {}
//}