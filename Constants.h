#pragma once

#include <string>
#include <functional>  // For std::hash
#include "EncStr.h"
struct CGGuid
{
	uint64_t high;
	uint64_t low;

	bool isEmpty() { return high == 0 && low == 0; }

	bool operator!=(const CGGuid& rhs) const {
		return (this->high != rhs.high) || (this->low != rhs.low);
	}
	bool operator==(const CGGuid& rhs) const {
		return (this->high == rhs.high && this->low == rhs.low);
	}

	std::string toString() const { return std::string(E("Guid (") + std::to_string(high) + E(" ") + std::to_string(low) + E(")")); }
	std::string toStringReq() const { return std::string(std::to_string(high) + " " + std::to_string(low)); }
};

// Specialize std::hash for CGGuid
namespace std {
	template <>
	struct hash<CGGuid> {
		size_t operator()(const CGGuid& guid) const noexcept {
			// Combine the hash values of `high` and `low`
			size_t h1 = std::hash<uint64_t>{}(guid.high);
			size_t h2 = std::hash<uint64_t>{}(guid.low);
			return h1 ^ (h2 << 1);  // Combine the two hashes using XOR and bit shifting
		}
	};
}

enum class TypeId : uint8_t
{
	CGObject = 0,
	CGItem = 1,
	CGContainer = 2,
	CGAzeriteEmpoweredItem_C = 3,
	CGAzeriteItem_C = 4,
	CGUnit = 5,
	CGPlayer = 6,
	CGActivePlayer = 7,
	CGGameObject = 8,
	CGDynamicObject = 9,
	CGCorpse = 10,
	CGAreaTrigger = 11,
	CGSceneObject = 12,
	CGConversation = 13,
	// AIGroup = 14,       // Commented out
	// Scenario = 15,      // Commented out
	// Loot = 16,          // Commented out
	Invalid = 17
};
//B98  19FC 1A00  1A04
enum WoWClass : uint8_t
{
	None = 0,
	Warrior = 1,
	Paladin = 2,
	Hunter = 3,
	Rogue = 4,
	Priest = 5,
	DeathKnight = 6,
	Shaman = 7,
	Mage = 8,
	Warlock = 9,
	Monk = 10,
	Druid = 11,
};

enum WoWRace : uint8_t
{
	Human = 1,
	Orc,
	Dwarf,
	NightElf,
	Undead,
	Tauren,
	Gnome = 115,
	TrollFemale = 116,
	Troll = 158,
	Goblin = 8,
	BloodElf,
	Draenei,
	FelOrc,
	Naga,
	Broken,
	Skeleton = 15,
	Draeneis = 1629,
	BloodElfs = 1610,
};


enum ControlBits : uint64_t
{
	Nothing = 0x00000000,
	CtmWalk = 0x00001000,
	Front = 0x00000010,
	Back = 0x00000020,
	Jump = 0x00002000,
	Descend = 0x00004000,
	Left = 0x00000100,
	Right = 0x00000200,
	MovingFrontOrBack = 0x00010000,
	PitchUp = 0x400,
	PitchDown = 0x800,
	StrafeLeft = 0x00000040,
	StrafeRight = 0x00000080,
	Strafing = 0x00020000,
	Turning = 0x00040000,
	All = 0xFFFFFFFF
};

enum class PowerTypeId : uint8_t
{
	mana = 0,
	rage = 1,
	focus = 2,
	energy = 3,
	happiness = 4,
	runes = 5,
	runicpower = 6,
	SoulShards,
	HolyPower,
	Maelstrom,
	Chi,
	Insanity,
	ComboPoints,
	Obsolete2,
	ArcaneCharges,
	Fury,
	Pain,
	Essence,
	RuneBlood,
	RuneFrost,
	RuneUnholy
};


// INTERSECT FLAGS
enum IntersectFlags {
	M2COLLISION = 0x1,
	M2RENDER = 0x2,
	WMOCOLLISION = 0x10,
	WMORENDER = 0x20,
	TERRAIN = 0x100,
	WATERWALKABLELIQUID = 0x10000,
	LIQUID = 0x20000,
	ENTITYCOLLISION = 0x100000,

	NOENTITY = M2COLLISION | WMOCOLLISION | TERRAIN,
	COLLISION = M2COLLISION | WMOCOLLISION | TERRAIN | ENTITYCOLLISION,
	LINEOFSIGHT = WMOCOLLISION | ENTITYCOLLISION
};

enum UnitDynFlags {
	UNIT_DYNFLAG_NONE = 0x0000,
	UNIT_DYNFLAG_HIDE_MODEL = 0x0001, // Object model is not shown with this flag
	UNIT_DYNFLAG_LOOTABLE = 0x0004,
	UNIT_DYNFLAG_TRACK_UNIT = 0x0008,
	UNIT_DYNFLAG_TAPPED = 0x0010, // Lua_UnitIsTapped - Indicates the target as grey for the client.
	UNIT_DYNFLAG_TAPPEDBYME = 0x0020, // 
	UNIT_DYNFLAG_DEAD = 0x0040,
	UNIT_DYNFLAG_REFER_A_FRIEND = 0x0080,
	UNIT_DYNFLAG_ISTAPPEDBYALL_THREATLIST = 0x100
};

enum class AuraFlags : std::uint8_t
{
	Active = 0x80,  // 128 decimal
	Passive = 0x10,  // 16 decimal
	Harmful = 20     // 20 decimal (0x14 in hex)
};


enum UnitFlags
{
	UNIT_FLAG_NONE = 0x00000000,
	UNIT_FLAG_UNK_0 = 0x00000001,
	UNIT_FLAG_NON_ATTACKABLE = 0x00000002,           ///< not attackable
	UNIT_FLAG_DISABLE_MOVE = 0x00000004,
	UNIT_FLAG_PVP_ATTACKABLE = 0x00000008,           ///< allow apply pvp rules to attackable state in addition to faction dependent state, UNIT_FLAG_UNKNOWN1 in pre-bc mangos
	UNIT_FLAG_RENAME = 0x00000010,           ///< rename creature
	UNIT_FLAG_RESTING = 0x00000020,
	UNIT_FLAG_UNK_6 = 0x00000040,
	UNIT_FLAG_OOC_NOT_ATTACKABLE = 0x00000100,           ///< (OOC Out Of Combat) Can not be attacked when not in combat. Removed if unit for some reason enter combat (flag probably removed for the attacked and it's party/group only) \todo Needs more documentation
	UNIT_FLAG_PASSIVE = 0x00000200,           ///< makes you unable to attack everything. Almost identical to our "civilian"-term. Will ignore it's surroundings and not engage in combat unless "called upon" or engaged by another unit.
	UNIT_FLAG_PVP = 0x00001000,
	UNIT_FLAG_SILENCED = 0x00002000,           ///< silenced, 2.1.1
	UNIT_FLAG_UNK_14 = 0x00004000,           ///< 2.0.8
	UNIT_FLAG_UNK_15 = 0x00008000,           ///< related to jerky movement in water?
	UNIT_FLAG_UNK_16 = 0x00010000,           ///< removes attackable icon
	UNIT_FLAG_PACIFIED = 0x00020000,
	UNIT_FLAG_DISABLE_ROTATE = 0x00040000,
	UNIT_FLAG_IN_COMBAT = 0x00080000,
	UNIT_FLAG_NOT_SELECTABLE = 0x02000000,
	UNIT_FLAG_SKINNABLE = 0x04000000,
	UNIT_FLAG_AURAS_VISIBLE = 0x08000000,           ///< magic detect
	UNIT_FLAG_SHEATHE = 0x40000000,
	// UNIT_FLAG_UNK_31              = 0x80000000           // no affect in 1.12.1

	// [-ZERO] TBC enumerations [?]
	UNIT_FLAG_NOT_ATTACKABLE_1 = 0x00000080,           ///< ?? (UNIT_FLAG_PVP_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1) is NON_PVP_ATTACKABLE
	UNIT_FLAG_LOOTING = 0x00000400,           ///< loot animation
	UNIT_FLAG_PET_IN_COMBAT = 0x00000800,           ///< in combat?, 2.0.8
	UNIT_FLAG_STUNNED = 0x00040000,           ///< stunned, 2.1.1
	UNIT_FLAG_TAXI_FLIGHT = 0x00100000,           ///< disable casting at client side spell not allowed by taxi flight (mounted?), probably used with 0x4 flag
	UNIT_FLAG_DISARMED = 0x00200000,           ///< disable melee spells casting..., "Required melee weapon" added to melee spells tooltip.
	UNIT_FLAG_CONFUSED = 0x00400000,
	UNIT_FLAG_FLEEING = 0x00800000,
	UNIT_FLAG_PLAYER_CONTROLLED = 0x01000000,           ///< used in spell Eyes of the Beast for pet... let attack by controlled creature
	// [-ZERO] UNIT_FLAG_MOUNT                 = 0x08000000,
	UNIT_FLAG_UNK_28 = 0x10000000,
	UNIT_FLAG_UNK_29 = 0x20000000,            ///< used in Feign Death spell

	UNIT_FLAG_INVIS_ENT = UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_PASSIVE | UNIT_FLAG_NOT_SELECTABLE,
	UNIT_FLAG_UNK_INVIS_ENT = 0x80002008100
};

struct ActiveQuest
{
	uint32_t QuestId = 0;
	int8_t isCompleted = 0;
	uint32_t StartTime = 0;
	uint16_t Objective1 = 0;
	uint16_t Objective2 = 0;
	uint16_t Objective3 = 0;
	uint16_t Objective4 = 0;
	uint16_t Objective5 = 0;
};
