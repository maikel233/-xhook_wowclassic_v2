#pragma once
#include "Navigator.h"

namespace Navigation
{
	void Shutdown();
	bool CalculatePath(uint32_t mapId, CGVector3* start, CGVector3* destination);
	std::vector<CGVector3> const& ActivePath();
}