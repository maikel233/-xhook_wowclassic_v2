#include "pch.h"

#include "scorch/navigation/Navigator.h"

#include <windows.h>
#include <iostream>
#include <string>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
static char const* const MAP_FILE_NAME_FORMAT = "%smmaps/%03i.mmap";
static char const* const TILE_FILE_NAME_FORMAT = "%smmaps/%03i%02i%02i.mmtile";

struct MmapTileHeader
{
	unsigned int mmapMagic;
	unsigned int dtVersion;
	unsigned int mmapVersion;
	unsigned int size;
	bool usesLiquids : 1;
};

uint32_t worldToTile(float_t worldPosition)
{
	return 32 - worldPosition / SIZE_OF_GRIDS;
}

uint32_t packTileId(uint32_t tileX, uint32_t tileY)
{
	return uint32_t(tileX << 16 | tileY);
}

/* https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf */
template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
	auto size = static_cast<size_t>(size_s);
	auto buf = std::make_unique<char[]>(size);
	std::snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

std::string runningDirectory = "";

std::string getRunningDirectory() {
	if (runningDirectory.length() == 0)
	{
		TCHAR dllPath[MAX_PATH] = { 0 };
		GetModuleFileName((HINSTANCE)&__ImageBase, dllPath, _countof(dllPath));
		std::wstring wideString(dllPath);
		std::string tempDirectory(wideString.begin(), wideString.end());
		auto lastBacktick = tempDirectory.find_last_of('\\');
		runningDirectory = tempDirectory.substr(0, lastBacktick + 1);
	}

	return runningDirectory;
}

std::string getMapFileLocation(uint32_t mapId)
{
	return string_format(MAP_FILE_NAME_FORMAT, getRunningDirectory().c_str(), mapId);
}

std::string getTileFileLocation(uint32_t mapId, uint32_t tileX, uint32_t tileY)
{
	return string_format(TILE_FILE_NAME_FORMAT, getRunningDirectory().c_str(), mapId, tileX, tileY);
}

Navigator::~Navigator()
{
	if (_navMeshQuery != nullptr) {
		dtFreeNavMeshQuery(_navMeshQuery);
		_navMeshQuery = nullptr;
	}

	if (_navMesh != nullptr) {
		dtFreeNavMesh(_navMesh);
		_navMesh = nullptr;
	}

	if (this->generator != nullptr) {
		delete this->generator;
		this->generator = nullptr;
	}

	this->activeTiles.clear();
	this->mapId = -1;
	printf("Navigation deconstructed\n");
}

bool Navigator::initialize(int32_t mapId)
{
	printf("[Navigator.initialize] Loading map id: %u\n", mapId);
	auto mapFileName = getMapFileLocation(mapId);
	dtNavMeshParams params;
	FILE* file = fopen(mapFileName.c_str(), "rb");
	size_t fileRead = fread(&params, sizeof(dtNavMeshParams), 1, file);
	fclose(file);
	if (fileRead != 1)
	{
		printf("\t[!] Failed to read nav mesh params from: %s\n", mapFileName.c_str());
		return false;
	}
	printf("\t[?] Nav Mesh Params tileWidth: %f, tileHeight: %f\n", params.tileWidth, params.tileHeight);

	_navMesh = dtAllocNavMesh();
	dtStatus dtResult = _navMesh->init(&params);
	if (dtStatusFailed(dtResult))
	{
		printf("\t[!] Failed to create NavMesh for map: %u with dtStatus: %i\n", mapId, dtResult);
		dtFreeNavMesh(_navMesh);
		return false;
	}
	else { printf("\t[*] Successfully created NavMesh for map: %u\n", mapId); }

	_navMeshQuery = dtAllocNavMeshQuery();
	dtResult = _navMeshQuery->init(_navMesh, 1024);
	if (dtStatusFailed(dtResult))
	{
		printf("\t[!] Failed to create NavMeshQuery for map: %u with dtStatus: %i\n", mapId, dtResult);
		dtFreeNavMeshQuery(_navMeshQuery);
		return false;
	}
	else { printf("\t[*] Successfully created NavMeshQuery for map: %u\n", mapId); }

	this->generator = new PathGenerator(_navMesh, _navMeshQuery);
	this->mapId = mapId;
	return true;
}

bool Navigator::hasTile(uint32_t packedTileId)
{
	return this->activeTiles.find(packedTileId) != this->activeTiles.end();
}

bool Navigator::loadTile(uint32_t tileX, uint32_t tileY)
{
	if (this->hasTile(packTileId(tileX, tileY)))
		return true;

	return this->initializeTile(tileX, tileY);
}

bool Navigator::initializeTile(uint32_t tileX, uint32_t tileY)
{
	printf("[Navigation.initializeTile] Loading Tile mapId: %u, tileX: %u, tileY:%u\n", this->mapId, tileX, tileY);
	auto tileFileLocation = getTileFileLocation(this->mapId, tileX, tileY);
	printf("\t[?] Tile File Path: %s\n", tileFileLocation.c_str());
	MmapTileHeader fileHeader;

	FILE* file = fopen(tileFileLocation.c_str(), "rb");
	if (file == nullptr)
	{
		printf("\t[!] Failed to find tile file: %s\n", tileFileLocation.c_str());
		return false;
	}

	size_t mmapRead = fread(&fileHeader, sizeof(MmapTileHeader), 1, file);
	if (mmapRead != 1)
	{
		printf("\t[!] Failed to read TrinityCore::MmapTileHeader from tile file\n");
		fclose(file);
		return false;
	}

	printf("\t[?] Tiles Geometry Data Size is: %u\n", fileHeader.size);

	unsigned char* data = (unsigned char*)dtAlloc(fileHeader.size, DT_ALLOC_PERM);
	size_t result = fread(data, fileHeader.size, 1, file);
	fclose(file);
	if (result != 1)
	{
		printf("\t[!] Failed to read Detour Data from tile file\n");
		dtFree(data);
		return false;
	}

	dtMeshHeader* header = (dtMeshHeader*)data;
	dtTileRef tileRef = 0;
	dtStatus dtResult = _navMesh->addTile(data, fileHeader.size, DT_TILE_FREE_DATA, 0, &tileRef);
	if (dtStatusFailed(dtResult))
	{
		printf("\t[!] Failed to add tile to active mesh\n");
		dtFree(data);
		return false;
	}

	this->activeTiles.insert(std::pair<uint32_t, dtTileRef>(packTileId(tileX, tileY), tileRef));
	return true;
}

bool Navigator::calculatePath(CGVector3* start, CGVector3* destination) {
	uint32_t startTileX = worldToTile(start->x);
	uint32_t startTileY = worldToTile(start->y);
	ImGui::Text("Start tx: %u, ty: %u\n", startTileX, startTileY);

	uint32_t endTileX = worldToTile(destination->x);
	uint32_t endTileY = worldToTile(destination->y);
	ImGui::Text("End tx: %u, ty: %u\n", endTileX, endTileY);

	if (!loadTile(startTileX, startTileY) || !loadTile(endTileX, endTileY))
	{
		printf("[Navigator.calculatePath] Failed to load start/destination tile\n");
		return false;
	}

	return generator->CalculatePath(start->x, start->y, start->z, destination->x, destination->y, destination->z);
}