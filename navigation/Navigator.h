#pragma once
#include <windows.h>
#include <unordered_map>

#include "DetourCommon.h"
#include "PathGenerator.h"

uint32_t worldToTile(float_t worldPosition);

class Navigator
{
public:
	~Navigator();
	bool initialize(int32_t mapId);
	bool hasTile(uint32_t packedTileId);
	bool loadTile(uint32_t tileX, uint32_t tileY);
	bool initializeTile(uint32_t tileX, uint32_t tileY);
	bool calculatePath(CGVector3* source, CGVector3* destination);

	int32_t getMapId() { return mapId; }
	PathGenerator* getGenerator() { return generator; }

private:
	int32_t mapId = -1;
	dtNavMesh* _navMesh = nullptr;
	dtNavMeshQuery* _navMeshQuery = nullptr;
	PathGenerator* generator = nullptr;
	std::unordered_map<uint32_t, dtTileRef> activeTiles;
};
