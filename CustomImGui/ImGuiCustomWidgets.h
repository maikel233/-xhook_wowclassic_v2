#ifndef IMGUI_CUSTOM_WIDGETS_H
#define IMGUI_CUSTOM_WIDGETS_H

#include "imgui.h"

namespace ImGui
{
    // Custom checkbox
    IMGUI_API bool CustomCheckbox(const char* label, bool* v);

    // Custom slider with cyan theme
    IMGUI_API bool CustomSliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);

    // Top menu button
    IMGUI_API bool TopMenu(const char* label, bool selected, ImTextureID icon, const ImVec2& iconSize, bool isFirst, bool isLast);

    // Side menu button
    IMGUI_API bool SideMenu(const char* label, bool selected, ImTextureID icon, const ImVec2& iconSize);


    void DrawCustomTitleBar(const char* title);

    void DrawSidebarDivider(float sidebarWidth, float startY);
}

#endif // IMGUI_CUSTOM_WIDGETS_H
