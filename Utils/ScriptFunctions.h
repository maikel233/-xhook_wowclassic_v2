#pragma once

#include <string>
#include <fstream>
#include <source_location>
#include <windows.h>
#include "../WObject.h"

#include <imgui.h>

namespace ScriptFunctions
{
	bool IsUnitEnemy(WObject* unit);
	bool IsUnitFriendly(WObject* unit);
	std::string GetRace(WObject* unit);





	ImColor GetFactionColor(WObject* unit);
	ImColor GetClassColor(WObject * Player);
}
