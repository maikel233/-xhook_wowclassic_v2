#include "ImGuiCustomWidgets.h"
#include <imgui_internal.h>

namespace ImGui
{

    // Top menu button implementation
    bool TopMenu(const char* label, bool selected, ImTextureID icon, const ImVec2& iconSize, bool isFirst, bool isLast)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        // Standardize button dimensions for consistency
        float buttonWidth = 120.0f; // Fixed button width
        float buttonHeight = 40.0f; // Fixed button height
        float iconPadding = 8.0f;   // Padding between icon and text

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImVec2(buttonWidth, buttonHeight);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y)); // Explicit component-wise addition
        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        // Proceed with the rest of the function logic...


        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

        if (hovered || held)
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

        // Draw the button background
        ImU32 bgColor = selected ? ImColor(41, 64, 112) : (hovered ? ImColor(71, 94, 142) : ImColor(24, 31, 42, 255));
        window->DrawList->AddRectFilled(bb.Min, bb.Max, bgColor, 8, selected ? (isFirst && isLast ? ImDrawFlags_RoundCornersAll
            : isFirst ? ImDrawFlags_RoundCornersLeft
            : isLast ? ImDrawFlags_RoundCornersRight
            : ImDrawFlags_RoundCornersNone)
            : ImDrawFlags_RoundCornersAll);

        // Render the icon
        ImVec2 iconPos = ImVec2(bb.Min.x + 10, bb.Min.y + (buttonHeight - iconSize.y) / 2);
        if (icon)
        {
            window->DrawList->AddImage(icon, iconPos, ImVec2(iconPos.x + iconSize.x, iconPos.y + iconSize.y));
        }

        // Render the label
        ImVec2 textPos = ImVec2(iconPos.x + iconSize.x + iconPadding, bb.Min.y + (buttonHeight - label_size.y) / 2);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, 255 / 255.f));
        ImGui::RenderText(textPos, label);
        ImGui::PopStyleColor();

        return pressed;
    }

    bool ImGui::SideMenu(const char* label, bool selected, ImTextureID icon, const ImVec2& iconSize)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(label);
        const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

        // Calculate dynamic button width based on the window's content region
        float buttonWidth = ImGui::GetContentRegionAvail().x; //
        float buttonHeight = 40.0f; // Fixed button height

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = ImVec2(buttonWidth, buttonHeight);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(bb, id))
            return false;

        bool hovered, held;
        bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

        if (hovered || held)
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

        // Draw button background and stripe for selected state
        ImU32 stripeColor = ImColor(200, 50, 50, 255); // Red stripe
        if (selected)
        {
            window->DrawList->AddRectFilled(ImVec2(bb.Min.x - 2, bb.Min.y), ImVec2(bb.Min.x + 8, bb.Max.y), stripeColor);
            window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(41, 64, 112), 8, ImDrawFlags_RoundCornersLeft);
        }
        else
        {
            ImU32 bgColor = hovered ? ImColor(71, 94, 142) : ImColor(24, 31, 42, 255);
            window->DrawList->AddRectFilled(bb.Min, bb.Max, bgColor, 8, ImDrawFlags_RoundCornersLeft);
        }

        // Render the icon
        ImVec2 iconPos = ImVec2(bb.Min.x + 10, bb.Min.y + (40.0f - iconSize.y) / 2);
        if (icon)
        {
            window->DrawList->AddImage(icon, iconPos, ImVec2(iconPos.x + iconSize.x, iconPos.y + iconSize.y));
        }

        // Render the label
        ImVec2 textPos = ImVec2(iconPos.x + iconSize.x + 8.0f, bb.Min.y + (40.0f - label_size.y) / 2);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(229 / 255.f, 229 / 255.f, 229 / 255.f, 255 / 255.f));
        ImGui::RenderText(textPos, label);
        ImGui::PopStyleColor();

        return pressed;
    }



    // Custom checkbox implementation
    bool ImGui::CustomCheckbox(const char* label, bool* v)
    {
        ImGuiIO& io = GetIO();
        ImDrawList* draw_list = GetWindowDrawList();
        ImGuiStyle& style = GetStyle();

        const ImVec2 label_size = CalcTextSize(label, NULL, true);
        const float square_sz = GetFrameHeight(); // Square size matches frame height
        const ImVec2 pos = GetCursorScreenPos();
        const ImVec2 square_bb_min = pos;
        const ImVec2 square_bb_max = ImVec2(pos.x + square_sz, pos.y + square_sz);
        const ImVec2 text_bb_min = ImVec2(square_bb_max.x + style.ItemInnerSpacing.x, pos.y + style.FramePadding.y);
        const ImVec2 text_bb_max = ImVec2(text_bb_min.x + label_size.x, pos.y + label_size.y);

        ItemSize(ImVec2(square_sz + style.ItemInnerSpacing.x + label_size.x, label_size.y + style.FramePadding.y * 2.0f), style.FramePadding.y);

        if (!ItemAdd(ImRect(square_bb_min, text_bb_max), GetID(label)))
            return false;

        bool hovered, held;
        bool pressed = ButtonBehavior(ImRect(square_bb_min, square_bb_max), GetID(label), &hovered, &held);

        if (pressed)
            *v = !(*v);

        // Background color of the checkbox
        const ImU32 col_bg = GetColorU32((*v) ? ImVec4(0.0f, 0.7f, 1.0f, 1.0f) : ImVec4(0.8f, 0.8f, 0.8f, 1.0f)); // Cyan for checked, gray for unchecked
        draw_list->AddRectFilled(square_bb_min, square_bb_max, col_bg, style.FrameRounding);

        // Draw white checkmark if checked
        if (*v)
        {
            const float pad = square_sz * 0.2f; // Padding for the checkmark
            ImVec2 p1 = ImVec2(square_bb_min.x + pad, square_bb_min.y + square_sz * 0.5f);
            ImVec2 p2 = ImVec2(square_bb_min.x + square_sz * 0.4f, square_bb_max.y - pad);
            ImVec2 p3 = ImVec2(square_bb_max.x - pad, square_bb_min.y + pad);
            draw_list->AddLine(p1, p2, GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), 2.0f); // White checkmark line 1
            draw_list->AddLine(p2, p3, GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), 2.0f); // White checkmark line 2
        }

        // Render the label next to the checkbox
        RenderText(text_bb_min, label);

        return pressed;
    }


    // Custom slider float implementation
    bool CustomSliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, float power)
    {
        ImGuiStyle& style = GetStyle();
        PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.4f, 0.6f, 1.0f)); // Cyan frame background
        PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.0f, 0.6f, 0.8f, 1.0f)); // Hovered cyan
        PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.0f, 0.8f, 1.0f, 1.0f)); // Active cyan
        PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.2f, 0.8f, 1.0f, 1.0f)); // Grabber color

        bool value_changed = SliderFloat(label, v, v_min, v_max, format, power);

        PopStyleColor(4);
        return value_changed;
    }

    void DrawSidebarDivider(float sidebarWidth, float startY) {
        ImVec2 windowPos = ImGui::GetWindowPos();     // Get top-left corner of the window
        float windowHeight = ImGui::GetWindowHeight(); // Get full height of the window

        // Draw a vertical line starting below the logo (startY) and ending at the bottom of the window
        ImGui::GetWindowDrawList()->AddLine(
            ImVec2(windowPos.x + sidebarWidth, windowPos.y + startY),               // Start point (below the logo)
            ImVec2(windowPos.x + sidebarWidth, windowPos.y + windowHeight),         // End point (bottom of the window)
            ImGui::GetColorU32(ImVec4(0.2f, 0.2f, 0.2f, 1.0f)),                     // Divider color
            3.0f // Line thickness
        );
    }



    void DrawCustomTitleBar(const char* title) {
        const float titleBarHeight = 30.0f;
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

        // Draw title bar background (flat dark color)
        ImGui::GetWindowDrawList()->AddRectFilled(
            ImVec2(windowPos.x, windowPos.y),
            ImVec2(windowPos.x + windowSize.x, windowPos.y + titleBarHeight),
            ImGui::GetColorU32(ImVec4(0.1f, 0.1f, 0.1f, 1.0f)) // Dark background color
        );

        // Draw title text centered
        ImGui::SetCursorPosY((titleBarHeight - ImGui::GetFontSize()) / 2.0f); // Center vertically
        ImGui::SetCursorPosX((windowSize.x - ImGui::CalcTextSize(title).x) / 2.0f); // Center horizontally
        ImGui::Text("%s", title);

        // Optional close button on the right side
       // ImGui::SameLine(windowSize.x - 50.0f); // Position close button on the right
       // if (ImGui::Button("X")) {
            // Handle close action (e.g., set a flag to close the window)

     //   }

        // Add separator below the title bar for visual separation
        ImGui::SetCursorPosY(titleBarHeight);
        ImGui::Separator();
    }

}
