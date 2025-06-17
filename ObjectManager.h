#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>
#include "Constants.h"
#include "WObject.h"
#include <mutex>
#include <thread>

class ObjectManager
{
public:
    const std::unordered_map<CGGuid, WObject*>& GetObjects() const { return objects; }
    WObject* GetLocalPlayer() const { return localPlayer; }

    static void CycleObjects(bool refresh);
    static void CycleActivePlayer();
    static bool InGame();
    static void Test();
    static void TestObjectManager();

private:
    uintptr_t objManagerBase;
    std::unordered_map<CGGuid, WObject*> objects;  // Main object map (valid objects)
    std::unordered_map<CGGuid, WObject*> invalidObjects;  // Invalid objects map
    WObject* localPlayer;
};