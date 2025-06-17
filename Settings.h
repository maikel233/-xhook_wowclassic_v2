#pragma once
#include "Utils/ColorVar.h"


namespace Setting
{

	namespace Fishing {
		inline bool Enabled = false;
		inline int selectedOption = 0;
	}

	namespace Menu
	{
		inline bool ShowMainWindow;
		inline bool ShowJavaScriptWindow;
		inline bool ShowProfileWindow;
		inline bool EntityList;
		inline char Fraction[2048];
		inline bool ShowWayPoints = false;
		inline bool ShowWayPoints1 = false;
		inline bool ShowProfilePoint = false;
		inline bool LootSwitch = true;
		inline int ItemId;
		inline int StackCount;
		inline char LocationName[2048];
		inline char SpellName[128];
		inline char ItemName[128];
		inline float RandomDist;
		inline float CatMulRom;
		inline int Points;
		inline bool Farm = false;

		inline int g1;
		inline int g2;
		inline int g3;
		inline int g4;
	}

	namespace Hacks
	{
		enum class PlayerState : int {
			Ground,
			Swimming,
			UnderWaterWalking,
			WaterWalking,
			FallingSlow,
			CanFly,
			DisableCollision,
			Root,
			Loggedoff,
			DisableGravity
		};

		extern bool enabled;
		extern PlayerState CurrentPlayerState;
		extern bool WallClimb;
		extern bool NoCollision;
		extern bool TogglePlayerState;
	}
	namespace ESP
	{
		extern bool TraceLine;
		extern bool Ally, Enemy, HostileUnits, HostilePlayers;
		extern bool Player, LocalPlayer, Unit, Corpse, Object, GameObject, DynamicObject, Race, Horde, Alliance, DrawDeadEntity;
		extern bool Enabled, Lines, DrawBox, Names, Lvl, Health, Power, WayPoints, GuidStr, UnitRank;
		extern int MaxLvl, MinLvl;
		extern float Distance, Distance2;
		extern ColorVar CorpseColor, GameObjectColor, UnlockedGameObjectColor, ObjectColor, DynamicObjectColor;
		extern HealthColorVar PlayerColor, LocalPlayerColor, UnitColor, HordeColor, AllianceColor;
	}

	namespace Camera
	{
		extern bool Enable;
		extern float Camera_zoomout, Camera_zoomin, Camera_fov;
	}

	namespace Radar
	{
		extern bool Enabled;
		extern bool name;
		extern bool Ally, Enemy, HostileUnits, HostilePlayers;
		extern bool Player, LocalPlayer, Unit, Corpse, Object, GameObject, DrawDeadEntity;
		extern float zoom;
		extern float iconsScale;
		extern float multiply;

		//extern bool Enabled;
		//extern bool name;
		//extern bool Ally, Enemy, HostileUnits, HostilePlayers;
		//extern bool Player, LocalPlayer, Unit, Corpse, Object, GameObject, DrawDeadEntity;
		//extern float zoom;
		//extern float iconsScale;
		//extern float multiply;
		////extern TeamColorType teamColorType;
		////extern HealthColorVar enemyColor;
		////extern HealthColorVar enemyVisibleColor;
		////extern HealthColorVar allyColor;
		////extern HealthColorVar allyVisibleColor;
		////extern HealthColorVar HordeColor;
		////extern HealthColorVar HordeVisibleColor;
		////extern HealthColorVar AllianceColor;
		////extern HealthColorVar AllianceVisibleColor;
		////extern HealthColorVar PlayerColor, UnitColor;
		////extern ColorVar GameObjectColor;
		////extern ColorVar UnlockedGameObjectColor;
	}

	namespace EntityList
	{
		extern std::string Race, Class, UnitHealth, ObjType, Faction, UnitMana;
		extern const char* cRace;
		extern const char* cClass;
		extern const char* cUnitHealth;
		extern const char* cUnitMana;
		extern const char* cObjType;
		extern const char* cFaction;
		extern ImColor ClassColor, FactionColor;
		extern bool Player, LocalPlayer, Unit, Corpse, Object, GameObject, DynamicObject, DrawDeadEntity;
	}
}