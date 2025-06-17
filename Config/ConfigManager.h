#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <nlohmann/json.hpp>

#include "../Settings.h"
#include "../CustomImGui/ImGuiNotifications.h"
#include <fstream>
#include <iostream>


class ConfigManager {
public:
    void SaveConfig(std::string filename);
    void LoadConfig(const std::string& inputFilename);
};

#endif // CONFIG_MANAGER_H

