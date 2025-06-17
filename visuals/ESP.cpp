#include "ESP.h"
#include "Settings.h" // Ensure this includes the definition for Settings
#include "../GlobalVars.h"  // Ensure this includes the definition for Globals
#include "../Utils/Utils.h"    // Ensure this includes utility functions like GetClassColor
//#include "nav.h"      // Ensure this includes navigation waypoints
#include "GameMethods.h" // Ensure this includes game method invocations
#include "Camera.h"
#include "../Utils/ScriptFunctions.h"
#include "Utils/ColorVar.h"

HealthColorVar Setting::ESP::PlayerColor = ImColor(240, 248, 255);
HealthColorVar Setting::ESP::LocalPlayerColor = ImColor(15, 248, 255);
HealthColorVar Setting::ESP::UnitColor = ImColor(255, 127, 80);
ColorVar Setting::ESP::CorpseColor = ImColor(255, 0, 0);
ColorVar Setting::ESP::GameObjectColor = ImColor(0, 157, 20);
ColorVar Setting::ESP::UnlockedGameObjectColor = ImColor(0, 157, 20);
HealthColorVar Setting::ESP::HordeColor = ImColor(255, 0, 0);
HealthColorVar Setting::ESP::AllianceColor = ImColor(0, 0, 255);
ColorVar Setting::ESP::DynamicObjectColor = ImColor(0, 80, 60);
ColorVar Setting::ESP::ObjectColor = ImColor(0, 157, 20);

namespace Draw
{
    Renderer::Renderer() = default;
    Renderer::~Renderer() = default;

    void Renderer::Initialize()
    {
        if (!m_pFont)
        {
            ImGuiIO& io = ImGui::GetIO();
            m_pFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.0f);
        }
    }

    void Renderer::BeginScene()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetWindowSize(io.DisplaySize, ImGuiCond_Always);
    }

    void Renderer::DrawObjects(WObject* entity, const HealthColorVar& Colors) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window) {
            // Retrieve the world positions of the entity and the local player
            Vector3 entityWorldPos = entity->GetUnitPosition();
            Vector3 localPlayerWorldPos = GlobalVars::LocalPlayer->GetUnitPosition();

            // Convert world positions to screen positions using the updated WorldToScreen function
            auto [entityScreenPos, entityOnScreen] = WoW::camera::WorldToScreen(entityWorldPos);
            auto [localPlayerScreenPos, localPlayerOnScreen] = WoW::camera::WorldToScreen(localPlayerWorldPos);

            // Ensure both positions are on screen
            if (!entityOnScreen || !localPlayerOnScreen)
                return;

            // Check line of sight if the setting is enabled
            if (Setting::ESP::TraceLine && !WoW::camera::TraceLine(GlobalVars::LocalPlayer, entityWorldPos, IntersectFlags::LineOfSight))
                return;

            int TypeID = static_cast<int>(entity->GetType());

            //// Assign color for player-made objects
            //if (*entity->GetOwner() == *Globals::LocalPlayer->GetGuid()) {
            //    ImColor ownerColor(1.4f, 0.1f, 0.0f, 1.0f);
            //    window->DrawList->AddCircle(ImVec2(entityScreenPos.x, entityScreenPos.y), 10, ownerColor, 12, 1.0f);
            //}

            // Draw line between local player and entity if enabled
            if (Setting::ESP::Lines) {
                window->DrawList->AddLine(ImVec2(localPlayerScreenPos.x, localPlayerScreenPos.y), ImVec2(entityScreenPos.x, entityScreenPos.y), Colors.color, 1.0f);
            }

            // Additional drawing logic for units
            if (entity->IsUnit()) {
                // Draw GUID string if enabled
                if (Setting::ESP::GuidStr) {
                    std::string guidStr = entity->GetGuid()->toString();
                    window->DrawList->AddText(ImVec2(entityScreenPos.x, entityScreenPos.y - 30.0f), Colors.color, guidStr.c_str());
                }

                // Draw distance if enabled
                if (Setting::ESP::Distance) {
                    float distance = GlobalVars::LocalPlayer->GetUnitPosition().DistanceTo(entityWorldPos);
                    std::string distanceStr = "Dist: " + std::to_string(distance);
                    window->DrawList->AddText(ImVec2(entityScreenPos.x, entityScreenPos.y - 10.0f), Colors.color, distanceStr.c_str());
                }
            }

            // Draw names if enabled
            if (Setting::ESP::Names) {
                if (entity->GetType() == TypeId::CGPlayer || TypeID == static_cast<int>(TypeId::CGActivePlayer)) {
                    window->DrawList->AddText(ImVec2(entityScreenPos.x, entityScreenPos.y - 40.0f), Utils::GetClassColor(entity), entity->GetObjectName());
                }
                else if (entity->IsUnit()) {
                    window->DrawList->AddText(ImVec2(entityScreenPos.x, entityScreenPos.y - 40.0f), Colors.color, entity->GetObjectName());
                }
                else if (entity->IsGameObject()) {
                    window->DrawList->AddText(ImVec2(entityScreenPos.x, entityScreenPos.y - 40.0f), Colors.color, entity->GetObjectName());
                }
            }

            // Additional drawing logic for units and players
            if (TypeID == static_cast<int>(TypeId::CGUnit) || TypeID == static_cast<int>(TypeId::CGPlayer)) {
                // Highlight target if it's the current target
               /* if (GlobalVars::LocalPlayer->TargetGuid() == entity->GetGuid()) {
                    ImColor targetColor(1.4f, 0.1f, 0.0f, 1.0f);
                    window->DrawList->AddCircle(ImVec2(entityScreenPos.x, entityScreenPos.y), 10, targetColor, 12, 1.0f);
                }*/

                // Draw race if enabled
              /*  if (Setting::ESP::Race) {
                    std::string race = Utils::GetRace(entity);
                    window->DrawList->AddText(ImVec2(entityScreenPos.x, entityScreenPos.y), Colors.color, race.c_str());
                }*/

                // Draw health if enabled
                if (Setting::ESP::Health) {
                    std::string healthStr = "HP: " + Utils::GetHealth(entity);
                    window->DrawList->AddText(ImVec2(entityScreenPos.x, entityScreenPos.y - 30.0f), Colors.color, healthStr.c_str());
                }

                // Draw level if enabled
                if (Setting::ESP::Lvl) {
                    std::string levelStr = "LVL: " + std::to_string(entity->GetUnitLevel(1));
                    window->DrawList->AddText(ImVec2(entityScreenPos.x, entityScreenPos.y - 20.0f), Colors.color, levelStr.c_str());
                }

                // Draw energy and mana for players if enabled
                /*if (entity->IsPlayer() && Setting::ESP::EnergyAndMana) {
                    std::string energyManaStr = entity->getPowerString() + Utils::GetPower(entity);
                    window->DrawList->AddText(ImVec2(entityScreenPos.x + 100, entityScreenPos.y - 30.0f), Colors.color, energyManaStr.c_str());
                }*/
            }

            // Draw waypoints if enabled
            /*if (Settings::Drawing::WayPoints) {
                for (size_t i = 0; i < nav::Waypoints.size(); ++i) {
                    Vector3 waypointPos = nav::Waypoints[i];
                    auto [waypointScreenPos, waypointOnScreen] = WoW::camera::WorldToScreen(waypointPos);
                    if (waypointOnScreen) {
                        std::string waypointStr = "Waypoint: " + std::to_string(i);
                        window->DrawList->AddText(ImVec2(waypointScreenPos.x, waypointScreenPos.y), Colors.color, waypointStr.c_str());
                    }
                }
            }*/
        }
    }


    void Renderer::PreDraw()
    {
        if (!Setting::ESP::Enabled || !GlobalVars::LocalPlayer)
            return;

        for (const auto& [guid, object] : GlobalVars::Objects)
        {
            if (!object || !object->isValid())
                continue;

            int typeID = static_cast<int>(object->GetType());
            if (typeID != static_cast<int>(TypeId::CGUnit) &&
                typeID != static_cast<int>(TypeId::CGPlayer) &&
                typeID != static_cast<int>(TypeId::CGGameObject) &&
                typeID != static_cast<int>(TypeId::CGCorpse))
                continue;

            if (!Utils::ValidCoord(object))
                continue;

            ImColor color;
            if (object->IsUnit())
            {
              /*  if (object->IsDead() && !Setting::ESP::DrawDeadEntity)
                    continue;*/

                if (ScriptFunctions::IsUnitEnemy(object))
                {
                    if (typeID == static_cast<int>(TypeId::CGUnit) && !Setting::ESP::HostileUnits)
                        continue;
                    if (typeID == static_cast<int>(TypeId::CGPlayer) && !Setting::ESP::HostileUnits)
                        continue;
                }

                color = Setting::ESP::UnitColor.getColor(object);
            }
            else if (object->IsPlayer())
            {
                color = Setting::ESP::PlayerColor.getColor(object);
            }
            else if (object->IsGameObject())
            {
                color = Setting::ESP::GameObjectColor.getColor();
            }
            else if (object->IsCorpse())
            {
                color = Setting::ESP::CorpseColor.getColor();
            }

            DrawObjects(object, color);
        }
    }

    void Renderer::EndScene()
    {
        PreDraw();

        ImGuiWindow* window = ImGui::GetCurrentWindow();
        window->DrawList->PushClipRectFullScreen();

        // Additional rendering logic can be added here

        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
    }
}