#ifndef IMGUI_NOTIFICATIONS_H
#define IMGUI_NOTIFICATIONS_H

#include <imgui.h>
#include <vector>
#include <string>
#include <cmath>
#include <imgui_internal.h>

namespace ImGui
{
    struct Notification
    {
        std::string title;
        std::string text;
        ImVec4 color;
        float timer;         // Time remaining
        float lifetime;      // Total lifetime
        ImVec2 position;     // Current position for animation
        ImVec2 targetPos;    // Target position for animation
        bool isActive;       // Whether the notification is active
    };

    // API Functions
    IMGUI_API void AddNotification(const std::string& title, const std::string& text, const ImVec4& color, float lifetime);
    IMGUI_API void RenderNotifications();
    IMGUI_API bool BeginNotificationPopup(const char* str_id, const ImVec4& color, float timer, float* remaining_time);
    IMGUI_API void RenderNotificationPopupContent(const char* title, const char* text, const ImVec4& color, float timer, float remaining_time);
}

#endif // IMGUI_NOTIFICATIONS_H
