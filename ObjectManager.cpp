#include "ObjectManager.h"
#include "Offsets.h"
//#include "WObject.h"  // Include only the header file
//
#include "GameMethods.h"
#include "Utils/Utils.h"
#include "Utils/ScriptFunctions.h"


unsigned int EnumVisibleObjCb(int64_t objectPtr, int64_t filter)
{
    if (objectPtr)
    {
        auto object = reinterpret_cast<WObject*>(objectPtr);
        auto objType = object->GetType();

        // Temporary map to hold the objects found in the current pass
        static std::unordered_map<std::string, WObject*> currentObjects;

        // Check for valid object type and filter
        if (objType == static_cast<TypeId>(filter))
        {
            if (objType == TypeId::CGActivePlayer)
            {
                if (object->isValid() && !GlobalVars::LocalPlayer){
                    GlobalVars::LocalPlayer = object;
                }
                else if (!object->isValid() && GlobalVars::LocalPlayer) {
                    GlobalVars::LocalPlayer = object;
               }            
            }

            std::string objectGuid = object->GetGuid()->toString();

            // Check if the object is valid
            if (object->isValid())
            {
                if (GlobalVars::invalidObjects.contains(objectGuid)) {
                    // Remove from invalid objects and add to valid objects
                    GlobalVars::invalidObjects.erase(objectGuid);
                }

                // Add to currentObjects for this pass
                currentObjects[objectGuid] = object;

                // If not already in valid objects, add it
                if (!GlobalVars::Objects.contains(objectGuid)) {
                    GlobalVars::Objects.emplace(objectGuid, object);
                }
            }
            else {
                // Add to the invalid list if not already present
                if (!GlobalVars::invalidObjects.contains(objectGuid)) {
                    GlobalVars::invalidObjects.emplace(objectGuid, object);
                }
                // Remove invalid object from the valid objects map
                if (GlobalVars::Objects.contains(objectGuid)) {
                    GlobalVars::Objects.erase(objectGuid);
                }
            }
        }

        // Once the enumeration is complete, compare the maps
        if (currentObjects.size() > 0 && filter == 0)  // Assuming 'filter == 0' signals the final pass
        {
            // Find missing objects in the global map and remove them
            for (auto it = GlobalVars::Objects.begin(); it != GlobalVars::Objects.end();)
            {
                const auto& objectGuid = it->first;

                // If an object in GlobalVars::Objects is not in currentObjects, remove it
                if (currentObjects.find(objectGuid) == currentObjects.end())
                {
                    it = GlobalVars::Objects.erase(it);
                }
                else
                {
                    ++it;
                }
            }

            // Add any new objects in currentObjects to GlobalVars::Objects
            for (const auto& [guid, obj] : currentObjects)
            {
                if (!GlobalVars::Objects.contains(guid))
                {
                    GlobalVars::Objects.emplace(guid, obj);
                }
            }

            // Clear the temporary map for the next enumeration pass
            currentObjects.clear();
        }

        return 1;  // Continue processing
    }

    return 0;  // Break processing
}

void ObjectManager::CycleObjects(bool refresh)
{
   // std::cout << "[DEBUG] Starting object cycling." << std::endl;

    if (refresh) {
        GlobalVars::Objects.clear();  // Clear the existing valid objects
        GlobalVars::invalidObjects.clear();  // Clear the invalid objects
        Utils::logger("Cleared object lists");
    }

    // Call GameMethods::Invoke for different object types
    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGItem));
    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGUnit));
    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGPlayer));
    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGGameObject));
    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGCorpse));
    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGActivePlayer));

    Utils::logger("Finished cycling objects");
}

void ObjectManager::CycleActivePlayer()
{
    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGActivePlayer));
}

bool ObjectManager::InGame()
{
    return 1; //return *reinterpret_cast<uint8_t*>(Offsets::Offset_IsPlayerInWorld) != 0;
}

void ObjectManager::Test()
{
    WObject* localPlayer = GlobalVars::LocalPlayer;

    if (localPlayer && localPlayer->isValid()) {
        std::cout << "[+] LocalPlayer address: " << std::hex << localPlayer << std::endl;

        auto unitPos = localPlayer->GetUnitPosition();
        auto namePos = localPlayer->GetObjectNamePosition();

        printf("[+] LocalPlayer address: %p, Character name: %s, Facing: %f, Character lvl: %i\n"
            "    Unit position vector: %f %f %f, Name Position vector: %f %f %f\n",
            localPlayer,
            localPlayer->GetObjectName(),
            localPlayer->GetFacing(),
            localPlayer->GetUnitLevel(1),
            unitPos.x, unitPos.y, unitPos.z,
            namePos.x, namePos.y, namePos.z);
    }
    else {
        std::cout << "LocalPlayer is invalid or not found." << std::endl;
        ObjectManager::CycleActivePlayer();
    }
}

void ObjectManager::TestObjectManager()
{
    ObjectManager::CycleObjects(true);  // Refresh and cycle through objects

    // Check if local player is found
    auto localPlayer = GlobalVars::LocalPlayer;
    if (localPlayer && localPlayer->isValid())
    {
        auto unitPos = localPlayer->GetUnitPosition();
        auto namePos = localPlayer->GetObjectNamePosition();

        printf("[+] LocalPlayer address: %p, Character name: %s, Facing: %f, Character lvl: %i\n"
            "    Unit position vector: %f %f %f, Name Position vector: %f %f %f Health: %i Max Health: %i MapID: %i\n",
            localPlayer,
            localPlayer->GetObjectName(),
            localPlayer->GetFacing(),
            localPlayer->GetUnitLevel(1),
            unitPos.x, unitPos.y, unitPos.z,
            namePos.x, namePos.y, namePos.z,
            localPlayer->GetHealth(),
            localPlayer->GetMaxHealth(),
            GameMethods::ClntObjMgr__GetMapId()
            
        );
    }
    else
    {
        std::cout << "Local Player not found." << std::endl;
    }

    // Print all valid objects in the object list
    for (const auto& obj : GlobalVars::Objects)
    {

        if (obj.second->IsUnit() || obj.second->IsPlayer() || obj.second->IsLocalPlayer()) {
            std::cout << "Object GUID: " << obj.first
                << ", Type: " << static_cast<int>(obj.second->GetType()) << ", Name:" << obj.second->GetObjectName() << "HP: " << static_cast<int>(obj.second->GetHealth()) << "MAX HP:" << static_cast<int>(obj.second->GetMaxHealth()) << std::endl;
        }
        else {
            std::cout << "Object GUID: " << obj.first
                << ", Type: " << static_cast<int>(obj.second->GetType()) << ", Name:" << obj.second->GetObjectName() << std::endl;
        }
   
    }

    // Print all invalid objects in the invalid objects list
    for (const auto& obj : GlobalVars::invalidObjects)
    {
        std::cout << "Invalid Object GUID: " << obj.first
            << ", Type: " << static_cast<int>(obj.second->GetType()) << ", Name:" << obj.second->GetObjectName() << std::endl;
    }
}

////
////unsigned int EnumVisibleObjCb(int64_t objectPtr, int64_t filter)
////{
////    if (objectPtr)
////    {
////        auto object = reinterpret_cast<WObject*>(objectPtr);
////        auto objType = object->GetType();
////
////        if (/*objType < TypeId::Invalid && */objType == static_cast<TypeId>(filter))
////        {
////            if (objType == TypeId::CGActivePlayer /*&& !GlobalVars::LocalPlayer->isValid()*/)
////            {
////                GlobalVars::LocalPlayer = object;
////            }
////
////            if (!GlobalVars::Objects.contains(object->GetGuid()->toString()))
////            {
////                GlobalVars::Objects.emplace(object->GetGuid()->toString(), object);
////            }
////        }
////        return 1;  // Continue processing
////    }
////    return 0;  // Break processing
////}
////
////void ObjectManager::CycleObjects(bool refresh)
////{
////    std::cout << "[DEBUG] Starting object cycling." << std::endl;
////  
////
////    if (refresh) {
////        GlobalVars::Objects.clear();
////        Utils::logger("Cleared object list");
////    }
////
////    // Call GameMethods::Invoke with the callback and type filters
////    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGItem));
////    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGUnit));
////    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGPlayer));
////    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGGameObject));
////    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGCorpse));
////    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGActivePlayer));
////
////    Utils::logger("Finished cycling objects");
////}
////
////void ObjectManager::CycleActivePlayer()
////{
////    GameMethods::Invoke<char>(Offsets::Offset_ClntObjMgrEnumVisibleObjectsPtr, EnumVisibleObjCb, static_cast<int>(TypeId::CGActivePlayer));
////}
////
////bool ObjectManager::InGame()
////{
////    return *reinterpret_cast<uint8_t*>(Offsets::Offset_IsPlayerInWorld) != 0;
////}
////
////void ObjectManager::LoopFuncs()
////{
////    if (InGame())
////    {
////        if (!GlobalVars::LocalPlayer || !GlobalVars::LocalPlayer->isValid())
////        {
////            CycleActivePlayer();
////            GlobalVars::hooked = false;
////        }
////    }
////    else
////    {
////        GlobalVars::LocalPlayer = nullptr;
////        GlobalVars::hooked = false;
////    }
////}
////
////
////void ObjectManager::Test() {
////    //Utils::RegisterVectoredHandler();
////    // Check if local player is found
////    WObject* localPlayer = GlobalVars::LocalPlayer;
////
////    if (localPlayer && localPlayer->isValid()) {
////      
////        std::cout << "[+] LocalPlayer address:" << std::hex << localPlayer << std::endl;
////
////        auto unitPos = localPlayer->GetUnitPosition();      // Assume returns {x, y, z} or similar
////        auto namePos = localPlayer->GetObjectNamePosition();
////
////        printf("[+] LocalPlayer address: %p, Character name: %s, Facing: %f, Character lvl: %i\n"
////            "    Unit position vector: %f %f %f, Name Position vector: %f %f %f\n",
////            localPlayer,
////            localPlayer->GetObjectName(),
////            localPlayer->GetFacing(),
////            localPlayer->GetUnitLevel(1),
////            unitPos.x, unitPos.y, unitPos.z,
////            namePos.x, namePos.y, namePos.z);
////
////        //localPlayer->PrintTestOffsetValues();
////
////       // localPlayer->EnumerateVtableFloats();
////
////      
////        //for (auto& [guid, o] : GlobalVars::Objects)
////        //{
////
////        ////    if (!o->isValid())
////        ////        continue;
////
////        ////  
////        ////    //0x55 CGUnit_C::ShouldPlayHoverAnim(void)? Hovers character.
////        //// //0XA Object fade out
////        //// //0XB Object Fade In
////        //// //0x1C glow/star effect start
////        //// //0x1D glow/star effect stop
////
////
////        ////    //LP
////        ////    //0x06 teleports to plane?
////        ////localPlayer->BruteforceInteractRange(0x1F, 0x83); // stopped at 0x83  Van 0x64
////        //     // localPlayer->EnumerateVtableU64(); // stopped at 0x83  Van 0x64
////
////        //    if (o->IsUnit()) {
////        //        bool test = ScriptFunctions::IsUnitFriendly(o);
////        //        if (!test) {
////        //            std::cout << o->GetObjectName() << ", Enemy:" << std::endl;
////        //        }
////        //        else {
////        //            std::cout << o->GetObjectName() << ", Friendly:" << std::endl;
////        //        }
////        //    }
////        ////    
////        //}
////
////    }
////    else {
////       
////            ObjectManager::CycleActivePlayer();
////            std::cout << "[+] LocalPlayer address:" << std::hex << localPlayer << std::endl;
////           
////    }
////}
////
////void ObjectManager::TestObjectManager()
////{
////    ObjectManager::CycleObjects(true);  // Refresh and cycle through objects
////
////    // Check if local player is found
////    auto localPlayer = GlobalVars::LocalPlayer;
////    if (localPlayer && localPlayer->isValid())
////    {
////        auto unitPos = localPlayer->GetUnitPosition();      // Assume returns {x, y, z} or similar
////        auto namePos = localPlayer->GetObjectNamePosition();
////
////        printf("[+] LocalPlayer address: %p, Character name: %s, Facing: %f\n"
////            "    Unit position vector: %f %f %f, Name Position vector: %f %f %f\n",
////            localPlayer,
////            localPlayer->GetObjectName(),
////            localPlayer->GetFacing(),
////            unitPos.x, unitPos.y, unitPos.z,
////            namePos.x, namePos.y, namePos.z);
////    }
////    else
////    {
////        std::cout << "Local Player not found." << std::endl;
////    }
////
////    ////// Print all objects in the object list
////    //for (const auto& obj : GlobalVars::Objects)
////    //{
////    //    std::cout << "Object GUID: " << obj.first
////    //        << ", Type: " << static_cast<int>(obj.second->GetType()) << ", Name:" << obj.second->GetObjectName() << std::endl;
////    //}
////}