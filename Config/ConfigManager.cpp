#include "ConfigManager.h"


using json = nlohmann::json;

void ConfigManager::SaveConfig(std::string filename) {
    const std::string extension = ".json"; // Use .json as the file extension

    // Check if the filename already has the correct extension
    if (filename.size() < extension.size() ||
        filename.substr(filename.size() - extension.size()) != extension) {
        filename += extension; // Append .json if it's missing
    }

    json config;

    // Save ESP settings
    config["ESP"]["Enabled"] = Setting::ESP::Enabled;
    config["ESP"]["TraceLine"] = Setting::ESP::TraceLine;
    config["ESP"]["Ally"] = Setting::ESP::Ally;
    config["ESP"]["Enemy"] = Setting::ESP::Enemy;
    config["ESP"]["Distance"] = Setting::ESP::Distance;
    config["ESP"]["Distance2"] = Setting::ESP::Distance2;

    // Save Camera settings
    config["Camera"]["Enable"] = Setting::Camera::Enable;
    config["Camera"]["ZoomOut"] = Setting::Camera::Camera_zoomout;
    config["Camera"]["ZoomIn"] = Setting::Camera::Camera_zoomin;
    config["Camera"]["FOV"] = Setting::Camera::Camera_fov;

    // Save Radar settings
    config["Radar"]["Enabled"] = Setting::Radar::Enabled;
    config["Radar"]["Zoom"] = Setting::Radar::zoom;
    config["Radar"]["IconsScale"] = Setting::Radar::iconsScale;

    // Save JSON to file
    std::ofstream file(filename);
    if (file.is_open()) {
        file << config.dump(4); // Pretty print
        file.close();
        ImGui::AddNotification("[Config]", "Config saved to: " + filename, ImVec4(0.5f, 0.0f, 1.0f, 1.0f), 5.0f);
        std::cout << "Config saved to " << filename << std::endl;
    }
    else {
        ImGui::AddNotification("[Config]", "Failed to save config to: " + filename, ImVec4(0.5f, 0.0f, 1.0f, 1.0f), 5.0f);
        std::cerr << "Failed to save config to " << filename << std::endl;
    }
}

void ConfigManager::LoadConfig(const std::string& inputFilename) {
    const std::string extension = ".json"; // Use .json as the file extension

    // Convert filename to std::string if it's not already
    std::string filename = std::string(inputFilename); // Ensure it's a proper std::string

    // Check if the filename already has the correct extension
    if (filename.size() < extension.size() ||
        filename.substr(filename.size() - extension.size()) != extension) {
        filename += extension; // Append .json if it's missing
    }

    std::ifstream file(filename);
    if (!file.is_open()) {
        ImGui::AddNotification("[Config]", "Failed to open config file: " + filename, ImVec4(0.5f, 0.0f, 1.0f, 1.0f), 5.0f);
        std::cerr << "Failed to open config file: " << filename << std::endl;
        return;
    }
    json config;
    file >> config;

    // Load ESP settings
    if (config.contains("ESP")) {
        Setting::ESP::Enabled = config["ESP"]["Enabled"].get<bool>();
        Setting::ESP::TraceLine = config["ESP"]["TraceLine"].get<bool>();
        Setting::ESP::Ally = config["ESP"]["Ally"].get<bool>();
        Setting::ESP::Enemy = config["ESP"]["Enemy"].get<bool>();
        Setting::ESP::Distance = config["ESP"]["Distance"].get<float>();
        Setting::ESP::Distance2 = config["ESP"]["Distance2"].get<float>();
    }

    // Load Camera settings
    if (config.contains("Camera")) {
        Setting::Camera::Enable = config["Camera"]["Enable"].get<bool>();
        Setting::Camera::Camera_zoomout = config["Camera"]["ZoomOut"].get<float>();
        Setting::Camera::Camera_zoomin = config["Camera"]["ZoomIn"].get<float>();
        Setting::Camera::Camera_fov = config["Camera"]["FOV"].get<float>();
    }

    // Load Radar settings
    if (config.contains("Radar")) {
        Setting::Radar::Enabled = config["Radar"]["Enabled"].get<bool>();
        Setting::Radar::zoom = config["Radar"]["Zoom"].get<float>();
        Setting::Radar::iconsScale = config["Radar"]["IconsScale"].get<float>();
    }

    file.close();
    std::cout << "Config loaded from " << filename << std::endl;
    ImGui::AddNotification("[Config]", "Config loaded from: " + filename, ImVec4(0.5f, 0.0f, 1.0f, 1.0f), 5.0f);
}
