#include "pch.h"
#include "scorch/navigation/Navigation.h"

static Navigator* activeNavigator = nullptr;

void Navigation::Shutdown() {
	if (activeNavigator != nullptr)
	{
		delete activeNavigator;
		activeNavigator = nullptr;
	}
}

bool Navigation::CalculatePath(uint32_t mapId, CGVector3* start, CGVector3* destination)
{
	// first load
	if (!activeNavigator)
	{
		activeNavigator = new Navigator();
		if (!activeNavigator->initialize(mapId)) {
			delete activeNavigator;
			activeNavigator = nullptr;
			return false;
		}
	}
	// have other map, only ever want one loaded
	else if (activeNavigator->getMapId() != mapId)
	{
		delete activeNavigator;
		activeNavigator = nullptr;

		activeNavigator = new Navigator();
		if (!activeNavigator->initialize(mapId)) {
			delete activeNavigator;
			activeNavigator = nullptr;
			return false;
		}
	}

	return activeNavigator->calculatePath(start, destination);
}

std::vector<CGVector3> const& Navigation::ActivePath()
{
	if (activeNavigator != nullptr)
		return activeNavigator->getGenerator()->GetPath();
	else
		return std::vector<CGVector3>();
}