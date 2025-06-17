#pragma once

#include <string>
#include <fstream>
#include <source_location>
#include <windows.h>
#include "../WItem.h"
#include "../WObject.h"
#include "Colors.h"
// Define the path where logs will be written
#define LOGGER_PATH "log.txt"

namespace Utils
{
    std::string to_string(unsigned long code);

    bool RegisterVectoredHandler();
    // Function declaration for logger
    void logger(std::string message, bool force = false, const std::source_location& location = std::source_location::current());
    LONG NTAPI VectoredHandler(EXCEPTION_POINTERS* ExceptionInfo);
    void* Empty();  // Declaration for the empty function

    std::vector<WItem*> GetAllBackPackItems();
    std::vector<WItem*> GetAllBagItems();
    std::vector<WItem*> GetAllItems();
    int getEmptySlots();
    void PrintAllItems(std::vector<WItem*> ItemsArr);


    // Returns the current epoch time in milliseconds
    long GetEpochTime();
    // Generates a rainbow color based on the provided speed
    ImColor GetRainbowColor(float speed);
    // Returns a color corresponding to the given health percentage
    Color GetHealthColor(int hp);
    // Returns a color corresponding to the health of the specified player
    Color GetHealthColor(const WObject* player);
    // Retrieves the health of the specified entity as a string
    std::string GetHealth(WObject* entity);


    //test
    WObject* getUnitByName(std::string name);

    ImColor GetClassColor(WObject* unit);

    bool ValidCoord(WObject* entity);

    std::string GetObjType(WObject* entity);
}
