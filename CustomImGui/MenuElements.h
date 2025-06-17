#pragma once
#ifndef MENUELEMENTS_H
#define MENUELEMENTS_H

#include <vector>
#include <string>
#include <imgui.h>
#include <d3d11.h>

#include "stb/stb_image.h"
#include <glad/glad.h>
#include <iostream>
#include <filesystem>
#include "nanosvg/nanosvg.h"
#include "nanosvg/nanosvgrast.h"

#include "../Settings.h"
#include <map>
#include "../Config/ConfigManager.h"
#include <unordered_map>
#include "ImGuiNotifications.h"
#include "ImGuiCustomWidgets.h"
#include "../GlobalVars.h"

// Declare the icons as extern
extern unsigned char user[854];
extern unsigned char menubars[209];
extern unsigned char info[1024];
extern unsigned char home[611];
extern unsigned char globe[1835];
extern unsigned char gear[1096];
extern unsigned char crosshair[534];
extern unsigned char questionsign[800];

// Function prototypes
struct EmbeddedIconInfo
{
    const char* name;
    const char* displayName;
    const unsigned char* data;
    size_t dataSize;
};

struct Icon
{
    std::string name;
    std::string displayName;
    ID3D11ShaderResourceView* texture;
};

bool LoadIconsFromMemory(std::vector<Icon>& icons);
bool LoadEmbeddedLogoD3D11();
void RenderMenu(const std::vector<Icon>& icons);
void SetupImGuiStyle();

#endif // MENUELEMENTS_H



////#pragma once
////#ifndef MENUELEMENTS_H
////#define MENUELEMENTS_H
////
////#include <vector>
////#include <string>
////#include <imgui.h>
////#include <d3d11.h>
////
////#include "stb/stb_image.h"
////#include <glad/glad.h>
////#include <iostream>
////#include <filesystem>
////#include "nanosvg/nanosvg.h"
////#include "nanosvg/nanosvgrast.h"
////
////////#include "ConfigManager.h"
////#include "../Settings.h"
////#include <map>
////#include "../Config/ConfigManager.h"
////#include <unordered_map>
//////Custom stuff
////#include "ImGuiNotifications.h"
////#include "ImGuiCustomWidgets.h"
////#include "../GlobalVars.h"
////
//////start of our icons
////#include "..//assets/icons/logo.c"
////#include "..//assets/icons/user.c"
////#include "..//assets/icons/menu.c"
////#include "..//assets/icons/info.c"
////#include "..//assets/icons/home.c"
////#include "..//assets/icons/globe.c"
////#include "..//assets/icons/gear.c"
////#include "..//assets/icons/crosshair.c"
////#include "..//assets/icons/question-sign.c"
/////*************************************************************
//// * STRUCTS
//// *************************************************************/
////
//// // (1) Info about each embedded icon
////struct EmbeddedIconInfo
////{
////    const char* name;           // internal name (e.g., "gear-solid")
////    const char* displayName;    // user-friendly name (e.g., "Settings")
////    const unsigned char* data;  // pointer to the embedded PNG bytes
////    size_t dataSize;            // size of the PNG data array
////};
////
////// (2) The final icon structure used in the UI
//////     Here, 'texture' is a D3D11 SRV pointer
////struct Icon
////{
////    std::string name;                   // internal name (e.g., "gear-solid")
////    std::string displayName;            // "Settings"
////    ID3D11ShaderResourceView* texture;  // D3D11 SRV
////};
////
////bool LoadIconsFromMemory(std::vector<Icon>& icons);
////bool LoadEmbeddedLogoD3D11();
////void RenderMenu(const std::vector<Icon>& icons);
////void SetupImGuiStyle();
////#endif // MENUELEMENTS_H
