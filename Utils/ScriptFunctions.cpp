#include "ScriptFunctions.h"

#include "../GlobalVars.h"
#include "../GameMethods.h"

namespace ScriptFunctions
{
    bool IsUnitEnemy(WObject* unit)
    {
        if (!GlobalVars::LocalPlayer || !unit)
            return false;

        uint64_t reaction = GameMethods::GetUnitReaction(GlobalVars::LocalPlayer, unit);
        return (reaction <= 3);
    }

    bool IsUnitFriendly(WObject* unit) {
        return !IsUnitEnemy(unit);
    }

	//ImColor ScriptFunctions::GetFactionColor(WObject* Player) {
	//	ImColor FactionColor;
	//	if (Player->IsPlayer() || Player->IsLocalPlayer())
	//	{
	//		/*if (Player->GetFactionID() == FactionID::Horde)
	//			FactionColor = ImColor(1.00f, 0.0f, 0.0f, 1.0f);
	//		else*/
	//			FactionColor = ImColor(0.00f, 0.0f, 1.0f, 1.0f);
	//	}
	//	else { FactionColor; }
	//	return FactionColor;
	//}

	//ImColor ScriptFunctions::GetClassColor(WObject* unit) {
	//	int RaceID = unit->GetClassID();
	//	ImColor Class;

	//	if (RaceID == WoWClass::None) { Class = ImColor(0.0f, 0.0f, 0.0f, 1.0f); }
	//	else if (RaceID == WoWClass::Warrior) { Class = ImColor(0.78f, 0.61f, 0.43f, 1.0f); }
	//	else if (RaceID == WoWClass::Paladin) { Class = ImColor(0.96f, 0.55f, 0.73f, 1.0f); }
	//	else if (RaceID == WoWClass::Hunter) { Class = ImColor(0.67f, 0.83f, 0.45f, 1.0f); }
	//	else if (RaceID == WoWClass::Rogue) { Class = ImColor(1.0f, 0.96f, 0.41f, 1.0f); }
	//	else if (RaceID == WoWClass::Priest) { Class = ImColor(1.0f, 1.0f, 1.0f, 1.0f); }
	//	else if (RaceID == WoWClass::DeathKnight) { Class = ImColor(0.77f, 0.12f, 0.23f, 1.0f); }
	//	else if (RaceID == WoWClass::Shaman) { Class = ImColor(0.00f, 0.44f, 0.87f, 1.0f); }
	//	else if (RaceID == WoWClass::Mage) { Class = ImColor(0.25f, 0.78f, 0.92f, 1.0f); }
	//	else if (RaceID == WoWClass::Warlock) { Class = ImColor(0.53f, 0.53f, 0.93f, 1.0f); }
	//	else if (RaceID == WoWClass::Monk) { Class = ImColor(0.53f, 0.53f, 0.93f, 1.0f); }
	//	else if (RaceID == WoWClass::Druid) { Class = ImColor(1.0f, 0.49f, 0.04f, 1.0f); }
	//	else { Class = ImColor(1.0f, 0.49f, 1.04f, 1.0f); }

	//	return Class;
	//}

	///*std::string ScriptFunctions::GetRace(WObject* unit) {
	//	std::string Race;
	//	if (unit->IsPlayer() || unit->IsLocalPlayer()) {
	//		int RaceID = unit->GetRaceID();
	//		if (RaceID == WoWRace::Undead) { Race = "Undead"; }
	//		else if (RaceID == WoWRace::Troll) { Race = "Troll"; }
	//		else if (RaceID == WoWRace::TrollFemale) { Race = "Troll"; }
	//		else if (RaceID == WoWRace::Tauren) { Race = "Tauren"; }
	//		else if (RaceID == WoWRace::Skeleton) { Race = "Skeleton"; }
	//		else if (RaceID == WoWRace::Orc) { Race = "Orc"; }
	//		else if (RaceID == WoWRace::NightElf) { Race = "Nightelf"; }
	//		else if (RaceID == WoWRace::Naga) { Race = "Naga"; }
	//		else if (RaceID == WoWRace::Human) { Race = "Human"; }
	//		else if (RaceID == WoWRace::Goblin) { Race = "Goblin"; }
	//		else if (RaceID == WoWRace::Gnome) { Race = "Gnome"; }
	//		else if (RaceID == WoWRace::FelOrc) { Race = "FelOrc"; }
	//		else if (RaceID == WoWRace::Dwarf) { Race = "Dwarf"; }
	//		else if (RaceID == WoWRace::Draenei) { Race = "Draenei"; }
	//		else if (RaceID == WoWRace::Broken) { Race = "Broken"; }
	//		else if (RaceID == WoWRace::BloodElf) { Race = "BloodElf"; }
	//	}
	//	else { Race = ""; }
	//	return Race;
	//}*/








}