#include "Utils.h"
#include <iostream>
#include "../WItem.h"
#include "../GameMethods.h"
#include "../GlobalVars.h"
#include "../WContainer.h"
#include <mutex>
#include "../Offsets.h"

namespace Utils
{


    std::string to_string(unsigned long code) {
        std::cout << "Exception Code: 0x" << std::hex << code << std::endl;
        return "Exception Code: " + std::to_string(code);
    }

    bool Utils::RegisterVectoredHandler() {
        // Add the Vectored Exception Handler at the highest priority (1)
        PVOID handler = AddVectoredExceptionHandler(1, VectoredHandler);
        if (handler == nullptr) {
            std::cerr << "Failed to add Vectored Exception Handler." << std::endl;
            return false;
        }

        std::cout << "Vectored Exception Handler registered successfully." << std::endl;
        return true;
    }

    LONG NTAPI VectoredHandler(EXCEPTION_POINTERS* ExceptionInfo)
    {
        // Check for software breakpoint (0x80000003) or divide by zero (0xC0000094)
        if (ExceptionInfo->ExceptionRecord->ExceptionCode == 0x80000003)
        {
            // Get the instruction pointer (RIP)
            uintptr_t rip = ExceptionInfo->ContextRecord->Rip;

            // Compare RIP with known function addresses
            if (rip == Offsets::Offset_Spell_C_CastSpell)
            {
                // Extract function arguments (example for x64 calling convention)
                uintptr_t arg1 = ExceptionInfo->ContextRecord->Rcx;
                uintptr_t arg2 = ExceptionInfo->ContextRecord->Rdx;
                uintptr_t arg3 = ExceptionInfo->ContextRecord->R8;
                uintptr_t arg4 = ExceptionInfo->ContextRecord->R9;

                // Log the function call
                std::cout << "Spell_C_CastSpell called with args: "
                    << std::hex << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << std::endl;
            }

            // Redirect execution to avoid crashing
            ExceptionInfo->ContextRecord->Rip = (uintptr_t)Empty;
            return EXCEPTION_CONTINUE_EXECUTION;
        }
        else if (ExceptionInfo->ExceptionRecord->ExceptionCode == 0xC0000094) // Divide by zero
        {
            ExceptionInfo->ContextRecord->Rip = (uintptr_t)Empty;
            return EXCEPTION_CONTINUE_EXECUTION;
        }

        return EXCEPTION_CONTINUE_SEARCH;
    }

    ////////LONG NTAPI VectoredHandler(EXCEPTION_POINTERS* ExceptionInfo)
    ////////{
    ////////    if (ExceptionInfo->ExceptionRecord->ExceptionCode != 0x80000003 && ExceptionInfo->ExceptionRecord->ExceptionCode != 0xC0000094)
    ////////    {
    ////////        MessageBoxA(nullptr, "Fatal Exception!", to_string(ExceptionInfo->ExceptionRecord->ExceptionCode).c_str(), MB_OK);
    ////////        EXCEPTION_CONTINUE_SEARCH;
    ////////    }
    ////////    else
    ////////    {
    ////////        if (ExceptionInfo->ExceptionRecord->ExceptionCode == 0xC0000094)
    ////////        {
    ////////            //	ExceptionInfo->ContextRecord->Rip = (uint64_t)LuaCall;
    ////////            ExceptionInfo->ContextRecord->Rip = (uintptr_t)Empty;
    ////////            return EXCEPTION_CONTINUE_EXECUTION;
    ////////        }
    ////////    }

    ////////    return EXCEPTION_CONTINUE_SEARCH;
    ////////}

    //// Exception Handler
    //LONG NTAPI VectoredHandler(EXCEPTION_POINTERS* ExceptionInfo) {
    //    auto exceptionCode = ExceptionInfo->ExceptionRecord->ExceptionCode;

    //    // Handle Access Violations
    //    if (exceptionCode == EXCEPTION_ACCESS_VIOLATION) {  // 0xC0000005
    //        std::cout << "ACCESS_VIOLATION at address: 0x"
    //            << std::hex << (uintptr_t)ExceptionInfo->ExceptionRecord->ExceptionAddress
    //            << ", attempted to access: 0x"
    //            << std::hex << ExceptionInfo->ExceptionRecord->ExceptionInformation[1]
    //            << std::endl;

    //        // ExceptionInformation[0] == 0: Read access violation
    //        // ExceptionInformation[0] == 1: Write access violation
    //        // ExceptionInformation[0] == 8: Execute access violation
    //        if (ExceptionInfo->ExceptionRecord->ExceptionInformation[0] == 0) {
    //            std::cout << "Read access violation detected, attempting to skip." << std::endl;
    //            // Redirect execution to 'Empty' to skip the faulty instruction
    //            ExceptionInfo->ContextRecord->Rip = (uintptr_t)Empty;
    //            return EXCEPTION_CONTINUE_EXECUTION;
    //        }

    //        std::cout << "Unhandled access violation, continuing search for another handler." << std::endl;
    //        return EXCEPTION_CONTINUE_SEARCH;
    //    }

    //    // Handle Breakpoints and Division-by-Zero
    //    if (exceptionCode == EXCEPTION_BREAKPOINT || exceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO) {  // 0x80000003 or 0xC0000094
    //        if (exceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO) {  // 0xC0000094
    //            // Display a message box to inform about the divide-by-zero
    //            MessageBoxA(nullptr, "DIVIDE BY ZERO", "Error", MB_OK | MB_ICONERROR);

    //            // Set Rip to 'Empty' to skip the faulty instruction
    //            ExceptionInfo->ContextRecord->Rip = (uintptr_t)Empty;

    //            // Continue execution
    //            return EXCEPTION_CONTINUE_EXECUTION;
    //        }

    //        // If handling breakpoints is needed, add logic here
    //        // Currently, we're not handling breakpoints beyond the existing logic
    //    }

    //    // For all other exceptions, continue searching for other handlers
    //    return EXCEPTION_CONTINUE_SEARCH;
    //}

   



    void* Empty() {
        return nullptr;
    }


    void logger(std::string message, bool force, const std::source_location& location)
    {
        if (true) {
            std::string funcName = std::string(location.function_name()) + ":";
            std::string Line = std::to_string(location.line()) + ": ";
            std::string data = funcName + Line + message + "\n";
            std::ofstream f(LOGGER_PATH, std::ios::app);
            f << data;
            f.close();
        }

#if Logger || Force
        std::string funcName = std::string(location.function_name()) + ":";
        std::string Line = std::to_string(location.line()) + ": ";
        std::string data = funcName + Line + message + "\n";
        std::ofstream f(LOGGER_PATH, std::ios::app);
        f << data;
        f.close();
#endif
    }



    std::vector<WItem*> GetAllBackPackItems() {
#if Logger
        Utils::logger("start");
#endif
        std::vector<WItem*> ItemsArr;
        for (int i = 0; i < 16; i++)
        {
            auto ItemGuid = GlobalVars::LocalPlayer->GetInventory()->GetBackPackSlotByID(i);
            char guidStr[MAX_PATH];
            GameMethods::GuidToString(&ItemGuid, guidStr);
            auto entity = (WItem*)GlobalVars::Objects[guidStr];
            if (entity->isValid())
            {
                ItemsArr.push_back(entity);
            }
        }
#if Logger
        Utils::logger("end");
#endif
        return ItemsArr;
    }


    std::vector<WItem*> GetAllBagItems() {
#if Logger
        Utils::logger("start");
#endif
        std::vector<WItem*> ItemsArr;
        for (int i = 0; i < 4; i++)
        {
            auto ContainerGuid = GlobalVars::LocalPlayer->GetInventory()->GetBagByID(i);
            char guidStr[MAX_PATH];
            GameMethods::GuidToString(&ContainerGuid, guidStr);
            auto entity = (WContainer*)GlobalVars::Objects[guidStr];
            if (entity->isValid()) {
                for (int j = 0; j < entity->GetSlots(); j++)
                {
                    auto ItemGuid = entity->GetSlotById(j);
                    GameMethods::GuidToString(&ItemGuid, guidStr);
                    auto Item = (WItem*)GlobalVars::Objects[guidStr];
                    if (Item->isValid())
                    {
                        ItemsArr.push_back(Item);
                    }
                }
            }
        }
#if Logger
        Utils::logger("end");
#endif
        return ItemsArr;
    }

    std::vector<WItem*> GetAllItems() {
#if Logger
        Utils::logger("start");
#endif
        std::vector<WItem*> BackpackItemsArr = GetAllBackPackItems();
        std::vector<WItem*> BagItemArr = GetAllBagItems();

        std::vector<WItem*> AllItemsArr;

        AllItemsArr.insert(AllItemsArr.begin(), BackpackItemsArr.begin(), BackpackItemsArr.end());
        AllItemsArr.insert(AllItemsArr.begin(), BagItemArr.begin(), BagItemArr.end());
#if Logger
        Utils::logger("end");
#endif
        return AllItemsArr;

    }

    int getEmptySlots() {
#if Logger
        Utils::logger("start");
#endif
        int bagsSlots = 0;
        int backpackSlots = 16;
        int fullSlots = GetAllItems().size();

        for (int i = 0; i < 4; i++)
        {
            auto ContainerGuid = GlobalVars::LocalPlayer->GetInventory()->GetBagByID(i);
            char guidStr[MAX_PATH];
            GameMethods::GuidToString(&ContainerGuid, guidStr);
            auto entity = (WItem*)GlobalVars::Objects[guidStr];
            if (entity->isValid()) {
                bagsSlots += entity->ContainerCount();
            }
        }
#if Logger
        Utils::logger("end");
#endif
        printf("BagSlots:%i BackPackSlots:%i FullSlots:%i\n", bagsSlots, backpackSlots, fullSlots);
        return (bagsSlots + backpackSlots) - fullSlots;
    }

    void PrintAllItems(std::vector<WItem*> ItemsArr) {
#if Logger
        Utils::logger("start");
#endif
        for (int i = 0; i < ItemsArr.size(); i++)
        {
            auto ItemTable = GameMethods::GetItemCacheEntry(ItemsArr[i]->GetID());
            std::cout << "ItemPointer: " << ItemsArr[i]->Ptr() << ", Item Name: " << std::dec << ItemsArr[i]->GetObjectName() << ", Item SellPrice: " << ItemTable->GetSellPrice() << ", Item Quality: " << ItemTable->GetQuality() << std::endl;
        }
#if Logger
        Utils::logger("end");
#endif
    }


    WObject* getUnitByName(std::string name) {
#if Logger
        Utils::logger("start");
#endif
        if (!GlobalVars::Objects.empty()) {
            for (auto& [guid, o] : GlobalVars::Objects)
            {
                if (o->isValid() && o->GetType() == TypeId::CGUnit /*&& !o->isInvisEnt()*/) {
                    //  std::cout << "ObjName: " << o->GetObjectName() << std::endl;
                    if (std::string(o->GetObjectName()) == name)
                    {
                        //std::cout << o->GetObjectName() << std::endl;
#if Logger
                        Utils::logger("end");
#endif
                        return o;
                    }
                }
            }
        }
#if Logger
        Utils::logger("end");
#endif
        return 0;
    }

    // Function to get a rainbow color based on speed
    ImColor GetRainbowColor(float speed) {
        long now = GetTickCount64();
        float hue = (now % static_cast<int>(1.0f / speed)) * speed;
        return ImColor::HSV(hue, 1.0f, 1.0f);
    }

    // Function to get health-based color
    Color GetHealthColor(int hp) {
        return Color(
            min(510 * (100 - hp) / 100, 255),
            min(510 * hp / 100, 255),
            25
        );
    }

    // Overloaded function to get health-based color from a player object
    Color GetHealthColor(const WObject* player) {
        uint32_t health = player->GetHealth();
        uint32_t maxHealth = player->GetMaxHealth();

        return Color(
            min(510 * (maxHealth - health) / maxHealth, 255),
            min(510 * health / maxHealth, 255),
            25
        );
    }

    std::string GetHealth(WObject* Entity) {
        if (!Entity) return "N/A"; // Prevent crashes

        std::string HealthStr;
        if (Entity->IsUnit() || Entity->IsPlayer() || Entity->IsLocalPlayer()) {
            HealthStr = std::to_string(Entity->GetHealth()) + "/" + std::to_string(Entity->GetMaxHealth());
        }
        return HealthStr;
    }

   


    ImColor GetClassColor(WObject* unit) {
    	int RaceID = unit->GetClassID();
    	ImColor Class;

    	if (RaceID == WoWClass::None) { Class = ImColor(0.0f, 0.0f, 0.0f, 1.0f); }
    	else if (RaceID == WoWClass::Warrior) { Class = ImColor(0.78f, 0.61f, 0.43f, 1.0f); }
    	else if (RaceID == WoWClass::Paladin) { Class = ImColor(0.96f, 0.55f, 0.73f, 1.0f); }
    	else if (RaceID == WoWClass::Hunter) { Class = ImColor(0.67f, 0.83f, 0.45f, 1.0f); }
    	else if (RaceID == WoWClass::Rogue) { Class = ImColor(1.0f, 0.96f, 0.41f, 1.0f); }
    	else if (RaceID == WoWClass::Priest) { Class = ImColor(1.0f, 1.0f, 1.0f, 1.0f); }
    	else if (RaceID == WoWClass::DeathKnight) { Class = ImColor(0.77f, 0.12f, 0.23f, 1.0f); }
    	else if (RaceID == WoWClass::Shaman) { Class = ImColor(0.00f, 0.44f, 0.87f, 1.0f); }
    	else if (RaceID == WoWClass::Mage) { Class = ImColor(0.25f, 0.78f, 0.92f, 1.0f); }
    	else if (RaceID == WoWClass::Warlock) { Class = ImColor(0.53f, 0.53f, 0.93f, 1.0f); }
    	else if (RaceID == WoWClass::Monk) { Class = ImColor(0.53f, 0.53f, 0.93f, 1.0f); }
    	else if (RaceID == WoWClass::Druid) { Class = ImColor(1.0f, 0.49f, 0.04f, 1.0f); }
    	else { Class = ImColor(1.0f, 0.49f, 1.04f, 1.0f); }

    	return Class;
    }

    bool ValidCoord(WObject* entity) {
        Vector3 position = entity->GetUnitPosition();

        // Check if the position is at the origin
        if (position.IsZero()) {
            return false;
        }

        // Check if the distance from the origin exceeds the threshold
        if (position.Length() >= 100000.0f) {
            return false;
        }

        return true;
    }


    std::string GetObjType(WObject* entity) {
#if Logger
        Utils::logger("start");
#endif
        int TypeID = (int)entity->GetType();
        std::string Object;
        if (TypeID == (int)TypeId::CGActivePlayer) { Object = E("CGActivePlayer"); }
        else if (TypeID == (int)TypeId::CGPlayer) { Object = E("CGPlayer"); }
        else if (TypeID == (int)TypeId::CGUnit) { Object = E("CGUnit"); }
        else if (TypeID == (int)TypeId::CGGameObject) { Object = E("CGGameObj"); }
        else if (TypeID == (int)TypeId::CGCorpse) { Object = E("CGCorpse"); }
        else if (TypeID == (int)TypeId::CGDynamicObject) { Object = E("CGDynamicObj"); }
        else if (TypeID == (int)TypeId::CGObject) { Object = E("CGObj"); }
        else { Object = E(""); }
#if Logger
        Utils::logger("end");
#endif
        return Object;
    }

}
