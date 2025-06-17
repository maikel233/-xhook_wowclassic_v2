#include "Draw.h"
#include "Settings.h"
#include "GlobalVars.h"
#include "Camera.h"
#include "Utils/ScriptFunctions.h"
#include "GameMethods.h"
#include "CGWorldFrame.h"  

// Draw namespace implementations
namespace Draw {
    ImFont* m_pFont = nullptr;
    bool InitFont = false;

    void Initialize() {
        if (!InitFont) {
            ImGuiIO& io = ImGui::GetIO();
            m_pFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13);
            InitFont = true;
        }
    }


void BeginScene() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
    ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
    ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);
}

//
//// Function to render bones using ImGui
//void RenderBones(__int64 a1, __int64 a2)
//{
//    std::vector<Bone> bones;
//    if (!GameMethods::GetBonePositions(a1, a2, bones))
//        return;
//
//    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
//
//    for (size_t i = 0; i < bones.size(); i++)
//    {
//        Vector2 screenPos = WoW::camera::WorldToScreenv2(bones[i].position);
//
//        if (screenPos.x == 0.0f && screenPos.y == 0.0f)
//            continue;
//
//        // Render bone point
//        drawList->AddCircleFilled(ImVec2(screenPos.x, screenPos.y), 3.0f, IM_COL32(255, 0, 0, 255));
//
//        // Connect to next bone (Assuming valid hierarchy)
//        if (i < bones.size() - 1)
//        {
//            Vector2 nextScreenPos = WoW::camera::WorldToScreenv2(bones[i + 1].position);
//            if (nextScreenPos.x != 0.0f && nextScreenPos.y != 0.0f)
//            {
//                drawList->AddLine(ImVec2(screenPos.x, screenPos.y), ImVec2(nextScreenPos.x, nextScreenPos.y), IM_COL32(0, 255, 0, 255), 1.5f);
//            }
//        }
//    }
//}


void Draw2DBox(WObject* entity, ImU32 color, bool useDynamicHeight = false) {
    // Get ImGui window
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (!window) return;

    // Get the entity's position
    Vector3 entityPos = entity->GetUnitPosition();

    // Calculate the height of the box
    float boxHeight;
    if (useDynamicHeight) {
        float nameplateZ = entity->GetObjectNamePosition().z;
        boxHeight = nameplateZ - entityPos.z; // Dynamic height based on nameplate position
    }

    else {
        boxHeight = 7.5f; // Static height
    }

    // Set a fixed width for the box
    float boxWidth = 3.5f;

    // Calculate the top and bottom world positions
    Vector3 entityTop = entityPos;
    entityTop.z += boxHeight;

    // Convert world positions to screen-space
    Vector2 screenBottom = WoW::camera::WorldToScreenv2(entityPos);
    Vector2 screenTop = WoW::camera::WorldToScreenv2(entityTop);

    // Validate screen positions
    if (!screenBottom.isValid() || !screenTop.isValid())
        return;

    // Compute box corners in screen-space
    float screenBoxWidth = (screenBottom.y - screenTop.y) * 0.6f; // Aspect ratio for the box width
    ImVec2 topLeft = ImVec2(screenTop.x - screenBoxWidth / 2.0f, screenTop.y);
    ImVec2 bottomRight = ImVec2(screenTop.x + screenBoxWidth / 2.0f, screenBottom.y);

    // Draw the 2D box
    window->DrawList->AddRect(topLeft, bottomRight, color, 0.0f, ImDrawFlags_RoundCornersNone, 1.5f);
}
/**
 * Draws a 3D box around the entity's world-space bounding box.
 *
 * @param entity Pointer to the entity (WObject).
 * @param color  The color to draw the box.
 */
void Draw3DBox(WObject* entity, ImU32 color)
{
    // Get ImGui window
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (!window) return;
    if (!entity) return;

    // Get the entity's world position and dimensions
    Vector3 entityPos = entity->GetUnitPosition();

    float NamePlate = entity->GetObjectNamePosition().z - entity->GetUnitPosition().z;
  
    float height;
    if (entity->IsLocalPlayer()) {
        height = NamePlate/* - entity->GetCollisionHeight()*/;
    }
    else if (entity->IsGameObject()) {
        height = NamePlate - 3.5f; //to
    }
    else {
        height = NamePlate - 3.5f; //to
    }

    //TODO
    float width = 3.5;   // Width of the entity


    // Define the 8 corners of the 3D box
    Vector3 boxCorners[8] = {
        // Bottom face
        { entityPos.x - width / 2, entityPos.y - width / 2, entityPos.z },
        { entityPos.x + width / 2, entityPos.y - width / 2, entityPos.z },
        { entityPos.x + width / 2, entityPos.y + width / 2, entityPos.z },
        { entityPos.x - width / 2, entityPos.y + width / 2, entityPos.z },

        // Top face
        { entityPos.x - width / 2, entityPos.y - width / 2, entityPos.z + height },
        { entityPos.x + width / 2, entityPos.y - width / 2, entityPos.z + height },
        { entityPos.x + width / 2, entityPos.y + width / 2, entityPos.z + height },
        { entityPos.x - width / 2, entityPos.y + width / 2, entityPos.z + height }
    };

    // Convert corners to screen-space
    Vector2 screenCorners[8];
    for (int i = 0; i < 8; ++i)
    {
        screenCorners[i] = WoW::camera::WorldToScreenv2(boxCorners[i]);
        if (screenCorners[i].isInvalid())
            return; // Skip drawing if any corner is invalid or off-screen





    }

    // Draw lines for the bottom face
    window->DrawList->AddLine(ImVec2(screenCorners[0].x, screenCorners[0].y), ImVec2(screenCorners[1].x, screenCorners[1].y), color, 1.0f);
    window->DrawList->AddLine(ImVec2(screenCorners[1].x, screenCorners[1].y), ImVec2(screenCorners[2].x, screenCorners[2].y), color, 1.0f);
    window->DrawList->AddLine(ImVec2(screenCorners[2].x, screenCorners[2].y), ImVec2(screenCorners[3].x, screenCorners[3].y), color, 1.0f);
    window->DrawList->AddLine(ImVec2(screenCorners[3].x, screenCorners[3].y), ImVec2(screenCorners[0].x, screenCorners[0].y), color, 1.0f);

    // Draw lines for the top face  
    window->DrawList->AddLine(ImVec2(screenCorners[4].x, screenCorners[4].y), ImVec2(screenCorners[5].x, screenCorners[5].y), color, 1.0f);
    window->DrawList->AddLine(ImVec2(screenCorners[5].x, screenCorners[5].y), ImVec2(screenCorners[6].x, screenCorners[6].y), color, 1.0f);
    window->DrawList->AddLine(ImVec2(screenCorners[6].x, screenCorners[6].y), ImVec2(screenCorners[7].x, screenCorners[7].y), color, 1.0f);
    window->DrawList->AddLine(ImVec2(screenCorners[7].x, screenCorners[7].y), ImVec2(screenCorners[4].x, screenCorners[4].y), color, 1.0f);

    // Draw vertical lines connecting the bottom and top faces
    for (int i = 0; i < 4; ++i)
    {
        window->DrawList->AddLine(ImVec2(screenCorners[i].x, screenCorners[i].y), ImVec2(screenCorners[i + 4].x, screenCorners[i + 4].y), color, 1.0f);
    }
}



void DrawObjects(WObject* entity, const HealthColorVar& Colors) {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window) {
        // Retrieve the world positions of the entity and the local player
        Vector3 entityWorldPos = entity->GetUnitPosition();
        Vector3 localPlayerWorldPos = GlobalVars::LocalPlayer->GetUnitPosition();

        // Convert world positions to screen positions using the updated WorldToScreen function
        Vector2 entityOnScreen = WoW::camera::WorldToScreenv2(entity->GetUnitPosition());
        Vector2 localPlayerOnScreen = WoW::camera::WorldToScreenv2(GlobalVars::LocalPlayer->GetUnitPosition());

        if (entityOnScreen.isInvalid() || localPlayerOnScreen.isInvalid())
        {
            // std::cout << "One or both positions are invalid or off-screen. Skipping drawing.\n";
            return;
        }

        // Check line of sight if the setting is enabled
        if (Setting::ESP::TraceLine && !WoW::camera::TraceLine(GlobalVars::LocalPlayer, entityWorldPos, IntersectFlags::LINEOFSIGHT))
            return;

        //int TypeID = static_cast<int>(entity->GetType());

        //// Assign color for player-made objects
        //if (*entity->GetOwner() == *Globals::LocalPlayer->GetGuid()) {
        //    ImColor ownerColor(1.4f, 0.1f, 0.0f, 1.0f);
        //    window->DrawList->AddCircle(ImVec2(entityOnScreen.x, entityOnScreen.y), 10, ownerColor, 12, 1.0f);
        //}

        // Draw line between local player and entity if enabled
        if (Setting::ESP::Lines) {
            window->DrawList->AddLine(ImVec2(localPlayerOnScreen.x, localPlayerOnScreen.y), ImVec2(entityOnScreen.x, entityOnScreen.y), Colors.color, 1);      
        }

        if (Setting::ESP::DrawBox) {
            Draw3DBox(entity, IM_COL32(0, 255, 0, 255)); // Green color for the 3D box
            //  Draw2DBox(entity, IM_COL32(255, 0, 0, 255), false);
             //Draw2DBox(entity, IM_COL32(255, 0, 0, 255), true);
        }

        if (Setting::ESP::Race) {
            //std::string race = Utils::GetRace(entity);
           // window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y), Colors.color, race.c_str());
        }
      
        if (Setting::ESP::Health) {   
          std::string healthStr = "HP: " + Utils::GetHealth(entity);
std::cout << "[DEBUG] Health String: " << healthStr << std::endl;

window->DrawList->AddText(
    ImVec2(entityOnScreen.x, entityOnScreen.y - 30.0f),
    Colors.color, 
    healthStr.c_str()
);
        }

     
        if (Setting::ESP::Lvl) {
            std::string levelStr = "LVL: " + std::to_string(entity->GetUnitLevel(1));
            window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y - 20.0f), Colors.color, levelStr.c_str());     
        }

        // Additional drawing logic for units
        if (entity->IsUnit()) {
            // Draw GUID string if enabled
            if (Setting::ESP::GuidStr) {
                std::string guidStr = entity->GetGuid()->toString();
                window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y - 30.0f), Colors.color, guidStr.c_str());
            }

            // Draw distance if enabled
            if (Setting::ESP::Distance) {
                float distance = GlobalVars::LocalPlayer->GetUnitPosition().DistanceTo(entityWorldPos);
                std::string distanceStr = "Dist: " + std::to_string(distance);
                window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y - 10.0f), Colors.color, distanceStr.c_str());
            }
        }

        // Draw names if enabled
        if (Setting::ESP::Names) {
   
            if (entity->IsPlayer() || entity->IsLocalPlayer()) {
                window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y - 40.0f), Utils::GetClassColor(entity), entity->GetObjectName());
            }
            else if (entity->IsUnit()) {
                window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y - 40.0f), Colors.color, entity->GetObjectName());
            }
            else if (entity->IsGameObject()) {
                window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y - 40.0f), Colors.color, entity->GetObjectName());
            }
        }


        // Additional drawing logic for units and players
        if (entity->IsUnit() || entity->IsPlayer()) {
            // Highlight target if it's the current target
           /* if (GlobalVars::LocalPlayer->TargetGuid() == entity->GetGuid()) {
                ImColor targetColor(1.4f, 0.1f, 0.0f, 1.0f);
                window->DrawList->AddCircle(ImVec2(entityOnScreen.x, entityOnScreen.y), 10, targetColor, 12, 1.0f);
            }*/

            //// Draw race if enabled
            //if (Setting::ESP::Race) {
            //  //  std::string race = Utils::GetRace(entity);
            //  //  window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y), Colors.color, race.c_str());
            //      // Draw box with dynamic height (based on nameplate)
            //    Draw2DBox(entity, IM_COL32(255, 0, 0, 255), true);

            //}

            //// Draw health if enabled
            //if (Setting::ESP::Health) {
            // /*   std::string healthStr = "HP: " + Utils::GetHealth(entity);
            //    window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y - 30.0f), Colors.color, healthStr.c_str());*/
            //    // Draw 3D box around the entity
            //    Draw3DBox(entity, IM_COL32(0, 255, 0, 255)); // Green color for the 3D box
            //}

            //// Draw level if enabled
            //if (Setting::ESP::Lvl) {
            //  /*  std::string levelStr = "LVL: " + std::to_string(entity->GetUnitLevel(1));
            //    window->DrawList->AddText(ImVec2(entityOnScreen.x, entityOnScreen.y - 20.0f), Colors.color, levelStr.c_str());*/


            //    Draw2DBox(entity, IM_COL32(255, 0, 0, 255), false);

            //}

            // Draw energy and mana for players if enabled
            /*if (entity->IsPlayer() && Setting::ESP::EnergyAndMana) {
                std::string energyManaStr = entity->getPowerString() + Utils::GetPower(entity);
                window->DrawList->AddText(ImVec2(entityOnScreen.x + 100, entityOnScreen.y - 30.0f), Colors.color, energyManaStr.c_str());
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

void PreDraw()
{
    if (!Setting::ESP::Enabled || !GlobalVars::LocalPlayer)
        return;

    for (const auto& [guid, Object] : GlobalVars::Objects)
    {
        if (!Object || !Object->isValid())
            continue;


        if (!Object->IsAnyObj())
            continue;


        if (Object->IsPlayer() && !Setting::ESP::Player)
            continue;

        if (Object->IsLocalPlayer() && !Setting::ESP::LocalPlayer)
            continue;

        if (Object->IsUnit() && !Setting::ESP::Unit)
            continue;

        if (Object->IsGameObject() && !Setting::ESP::GameObject)
            continue;

        if (Object->IsDynamicObject() && !Setting::ESP::DynamicObject)
            continue;

        if (Object->IsCorpse() && !Setting::ESP::Corpse)
            continue;

        // Ensure coordinates are valid
        if (!Utils::ValidCoord(Object))
            continue;


        ImColor color;
        if (Object->IsUnit())
        {
            /*  if (object->IsDead() && !Setting::ESP::DrawDeadEntity)
                  continue;*/

            if (Setting::ESP::HostileUnits) {
                if (ScriptFunctions::IsUnitEnemy(Object)) {
                    if (!Setting::ESP::HostileUnits)
                        continue;
                }
            }

            color = Setting::ESP::UnitColor.getColor(Object);
        }

        else if (Object->IsPlayer())
        {
            if (Setting::ESP::HostileUnits) {
                if (ScriptFunctions::IsUnitEnemy(Object)) {
                    if (!Setting::ESP::HostileUnits)
                        continue;
                }
            }
            

            color = Setting::ESP::PlayerColor.getColor(Object);
        }
        else if (Object->IsGameObject()) {
            color = Setting::ESP::GameObjectColor.getColor();
        }
        else if (Object->IsCorpse()) {
            color = Setting::ESP::CorpseColor.getColor();
        }

        DrawObjects(Object, color);
    }
}


void EndScene() {
    PreDraw();

    ImGuiWindow* windowGui = ImGui::GetCurrentWindow();
    if (windowGui) {
        windowGui->DrawList->PushClipRectFullScreen();
        std::string displayInfo = "Project:X-HOOK for World of Warcraft";
        windowGui->DrawList->AddText(ImVec2(5, 0), ImColor(27.0f / 255.0f, 167.0f / 255.0f, 231.0f / 255.0f, 1.0f), displayInfo.c_str());
        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
    }
}

void RenderTextWithDynamicSize(const char* text, ImVec2 position, ImU32 color, float distance) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    float font_size = 12.0f;
    if (distance > 70) font_size = 10.0f;
    ImGui::PushFont(ImGui::GetFont());
    ImGui::SetWindowFontScale(font_size / 12.0f);
    draw_list->AddText(position, color, text);
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopFont();
}
}
