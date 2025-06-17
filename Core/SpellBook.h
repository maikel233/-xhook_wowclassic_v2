#pragma once

#include "../Utils/Vector.h"
#include "../EncStr.h"
#include "../GlobalVars.h"
#include <vector>
#include <cstdint>
#include "../ItemCacheEntry.h"

namespace pSpellBook
{




 //   typedef int32_t SpellId;
 //   typedef int32_t SpellSlot;

 //   //int64_t SpellBook_FindSpellByName(const char* SpellName, uint64_t* unk);
 //   int64_t SpellBook_FindSpellByName(int64_t a1, const char* SpellName, bool* outFlag);
 //   bool IsInRange(SpellId spellId, WObject* target);
 //   //bool Spell_C_IsCurrentSpell(int SpellId);
 //   //int64_t Spell_C_GetMinMaxSpellRange(int32_t SpellId, float_t* MinRange, float_t* MaxRange, CGGuid* TargetGuid);
 //   bool Spell_C_HaveSpellPower(int32_t spellId);
 //   bool CastSpellById(SpellId spellId, WObject* target);
 //   int64_t GetSpellCooldown(pSpellBook::SpellId spellId, int32_t isPet);// bool Spell_C_GetSpellCooldown(uint32_t spellId, int64_t* duration, uint32_t* startTime, int64_t* modRate);
 //   bool IsSpellKnown(SpellId spellId);
 //  // int64_t FindSlotBySpellId(int32_t spellId);

 // /*  inline SpellId GetRepeatingSpellId()
 //   {
 //       return *reinterpret_cast<SpellId*>(Offsets::Offset_SpellBook_RepeatingSpellId);
 //   }

 //
 //   inline SpellSlot GetSpellSlotBySpellId(SpellId spellId)
 //   {
 //       return reinterpret_cast<SpellSlot(__fastcall*)(SpellId spellId, bool isPet)>(Offsets::Offset_SpellBook_findSlotBySpellId)(spellId, false);
 //   }

 //   inline bool IsCurrentSpell(SpellId spellId)
 //   {
 //       return reinterpret_cast<bool(__fastcall*)(SpellId)>(Offsets::Offset_CGUnit_IsSpellKnown)(spellId);
 //   }*/

 //   //bool InRange(SpellId spellId, WObject* target);

 //   //bool CastSpellById(SpellId spellId, WObject* target);

 //   //bool CastSpellById(SpellId spellId);

 //  // int GetSpellIdByName(const char* SpellName);

 //   int GetSpellIdByName(int64_t a1, const char* SpellName, bool Dummy);

 //   bool IsOnCooldown(SpellId spellId);

 //   int64_t FindSlotBySpellId(SpellId spellId);

 //  

 //   bool CanCast(SpellId spellId, WObject* target);

 //   bool CanCast(SpellId spellId);

	//inline static int64_t SpellBook_FindSpellByName(const char* SpellName, uint64_t* unk);

	inline static bool Spell_C_IsCurrentSpell(int SpellId);

	inline static int64_t Spell_C_GetMinMaxSpellRange(int32_t SpellId, float_t* MinRange, float_t* MaxRange, CGGuid* TargetGuid);

	bool Spell_C_HaveSpellPower(int32_t spellId);

	inline static int64_t Spell_C_CastSpell(int32_t spellSlot, CGGuid* targetGuid);

	bool Spell_C_GetSpellCooldown(uint32_t spellId, int64_t* duration, int64_t* startTime, int64_t* modRate);

	bool IsSpellKnown(int32_t spellId);

	int64_t FindSlotBySpellId(int32_t spellId);

	int GetSpellIdByName(const char* SpellName);

	bool CastSpell(WObject* Unit, int SpellID, const char* spellName);

	//   bool IsSpellLearned(SpellId spellId);
}