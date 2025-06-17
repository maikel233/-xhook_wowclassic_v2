#include "ImGuiNotifications.h"

#define IM_PI                           3.14159265358979323846f

namespace ImGui
{
    static std::vector<Notification> notifications;

    static float Lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    void AddNotification(const std::string& title, const std::string& text, const ImVec4& color, float lifetime)
    {
        ImVec2 startPos = ImVec2(-300.0f, 10.0f); // Start outside screen
        ImVec2 targetPos = ImVec2(30.0f, 10.0f + notifications.size() * 70.0f); // Stacked position
        notifications.push_back({ title, text, color, lifetime, lifetime, startPos, targetPos, true });
    }

    void ImGui::RenderNotifications()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImDrawList* drawList = ImGui::GetForegroundDrawList();
        const float notificationWidth = 300.0f;
        const float notificationHeight = 60.0f;

        for (size_t i = 0; i < notifications.size(); ++i)
        {
            Notification& notif = notifications[i];

            // Update position for smooth animation
            if (notif.isActive)
            {
                notif.position.x = Lerp(notif.position.x, notif.targetPos.x, 10.0f * io.DeltaTime);
                notif.position.y = Lerp(notif.position.y, notif.targetPos.y, 10.0f * io.DeltaTime);
            }

            // Calculate alpha for fade-out effect
            float alpha = notif.timer / notif.lifetime;                  // Normal fade for background and stripe
            float textAlpha = std::min(1.0f, powf(alpha, 0.5f));         // Slower fade for text using a curve (slower near the end)

            // Define gradient colors (start and end)
            ImVec4 gradientStart = ImVec4(0.1f, 0.1f, 0.5f, 0.8f * alpha); // Dark blue
            ImVec4 gradientEnd = ImVec4(0.0f, 0.0f, 0.2f, 0.8f * alpha);   // Darker blue

            // Get screen coordinates for gradient rectangle
            ImVec2 rectMin = notif.position;
            ImVec2 rectMax = ImVec2(notif.position.x + notificationWidth, notif.position.y + notificationHeight);

            // Draw gradient background
            drawList->AddRectFilledMultiColor(
                rectMin,
                rectMax,
                ImGui::GetColorU32(gradientStart),
                ImGui::GetColorU32(gradientStart),
                ImGui::GetColorU32(gradientEnd),
                ImGui::GetColorU32(gradientEnd));

            // Draw blue stripe on the left
            drawList->AddRectFilled(
                rectMin,
                ImVec2(rectMin.x + 5, rectMax.y),
                ImGui::GetColorU32(ImVec4(0.2f, 0.4f, 1.0f, alpha))); // Bright blue stripe

            // Render title with slower fade
            ImVec2 textPos = ImVec2(rectMin.x + 15.0f, rectMin.y + 10.0f);
            drawList->AddText(textPos, ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, textAlpha)), notif.title.c_str());

            // Render text with slower fade
            drawList->AddText(ImVec2(textPos.x, textPos.y + 20), ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, textAlpha * 0.8f)), notif.text.c_str());

            // Render circular timer
            float radius = 8.0f;
            float timerAngle = (notif.timer / notif.lifetime) * 2.0f * IM_PI;
            ImVec2 circleCenter = ImVec2(rectMax.x - 20, (rectMin.y + rectMax.y) / 2);
            drawList->AddCircleFilled(circleCenter, radius, ImGui::GetColorU32(ImVec4(0.2f, 0.2f, 0.2f, alpha)));
            drawList->PathArcTo(circleCenter, radius, -IM_PI / 2, -IM_PI / 2 + timerAngle, 16);
            drawList->PathStroke(ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, alpha)), 0, 2.0f);

            // Update timer
            notif.timer -= io.DeltaTime;
            if (notif.timer <= 0.0f)
            {
                notif.isActive = false;
            }
        }

        // Remove inactive notifications and update positions
        notifications.erase(std::remove_if(notifications.begin(), notifications.end(), [](const Notification& notif) {
            return !notif.isActive;
            }), notifications.end());

        // Update target positions for remaining notifications
        for (size_t i = 0; i < notifications.size(); ++i)
        {
            notifications[i].targetPos = ImVec2(30.0f, 10.0f + i * 70.0f);
        }
    }


    bool BeginNotificationPopup(const char* str_id, const ImVec4& color, float timer, float* remaining_time)
    {
        // Simplified implementation for direct popup handling
        ImGuiContext& g = *GImGui;
        ImGuiID id = g.CurrentWindow->GetID(str_id);

        if (!IsPopupOpen(id, ImGuiPopupFlags_None))
        {
            OpenPopup(str_id);
            *remaining_time = timer;
        }

        if (!ImGui::BeginPopupEx(id, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings))
        {
            return false;
        }

        return true;
    }

    void RenderNotificationPopupContent(const char* title, const char* text, const ImVec4& color, float timer, float remaining_time)
    {
        ImGui::TextColored(color, "%s", title);
        ImGui::TextWrapped("%s", text);
    }
}
