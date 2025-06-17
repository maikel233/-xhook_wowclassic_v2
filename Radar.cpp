#include "Radar.h"

// Settings variables
bool Setting::Radar::name = false;
bool Setting::Radar::Player = false;
bool Setting::Radar::LocalPlayer = false;
bool Setting::Radar::Corpse = false;
bool Setting::Radar::Unit = false;
bool Setting::Radar::GameObject = false;
bool Setting::Radar::Object = false;
bool Setting::Radar::Enabled = false;
bool Setting::Radar::DrawDeadEntity = false;

bool Setting::Radar::HostileUnits = false;
bool Setting::Radar::HostilePlayers = false;

float Setting::Radar::zoom = 1.f;
float Setting::Radar::iconsScale = 4.5f;
float Setting::Radar::multiply = 4.5f;

// Radar drawing functions
namespace Draw {
    namespace Radar {

        Vector2D WorldToRadar(const Vector3 location, const Vector3 origin, float Player_rotation, int width, float scale) {
            // Function logic remains the same
            float x_diff = location.x - origin.x;
            float y_diff = location.y - origin.y;

            int iRadarRadius = width;

            float flOffset = atanf(y_diff / x_diff);
            flOffset *= 180;
            flOffset /= M_PI;

            if ((x_diff < 0) && (y_diff >= 0))
                flOffset = 180 + flOffset;
            else if ((x_diff < 0) && (y_diff < 0))
                flOffset = 180 + flOffset;
            else if ((x_diff >= 0) && (y_diff < 0))
                flOffset = 360 + flOffset;

            y_diff = -1 * (sqrtf((x_diff * x_diff) + (y_diff * y_diff)));
            x_diff = 0;

            flOffset = Player_rotation - flOffset;

            flOffset *= M_PI;
            flOffset /= 180;

            float xnew_diff = x_diff * cosf(flOffset) - y_diff * sinf(flOffset);
            float ynew_diff = x_diff * sinf(flOffset) + y_diff * cosf(flOffset);

            xnew_diff /= scale;
            ynew_diff /= scale;

            xnew_diff = (iRadarRadius / 2) + (int)xnew_diff;
            ynew_diff = (iRadarRadius / 2) + (int)ynew_diff;

            // Clamp x & y
            if (xnew_diff > iRadarRadius)
                xnew_diff = iRadarRadius - 4;
            else if (xnew_diff < 4)
                xnew_diff = 4;

            if (ynew_diff > iRadarRadius)
                ynew_diff = iRadarRadius;
            else if (ynew_diff < 4)
                ynew_diff = 0;

            return Vector2D(xnew_diff, ynew_diff);
        }

        void SquareConstraint(ImGuiSizeCallbackData* data) {
            data->DesiredSize = ImVec2(max(data->DesiredSize.x, data->DesiredSize.y), max(data->DesiredSize.x, data->DesiredSize.y));
        }

        float RadianToDegree(float Rotation) {
            return (float)(Rotation * (180 / M_PI));
        }

          void DrawObj(WObject* localplayer, WObject* entity, ImColor color, ImDrawList* draw_list, ImVec2 winpos, ImVec2 winsize) {
              int shape = -1;

              Vector3 localPos = localplayer->GetUnitPosition();
              Vector3 playerPos = entity->GetUnitPosition();
              Vector3 forward = entity->GetDirection2(); // Probably invalid pretty sure

              float Player_rotation = RadianToDegree(localplayer->GetFacing());
              Vector2D screenpos = WorldToRadar(entity->GetUnitPosition(), localplayer->GetUnitPosition(), Player_rotation, winsize.x, Setting::Radar::zoom);

              if (playerPos.z + 64.0f < localPos.z)
                  shape = EntityShape_t::SHAPE_TRIANGLE_UPSIDEDOWN;
              else if (playerPos.z - 64.0f > localPos.z)
                  shape = EntityShape_t::SHAPE_TRIANGLE;
              else
                  shape = EntityShape_t::SHAPE_CIRCLE;

              float scale = Setting::Radar::iconsScale;
              Vector3 dirArrowVec = playerPos + (forward * 2 * Setting::Radar::zoom * scale);
              Vector2D dirArrowPos = WorldToRadar(dirArrowVec, localplayer->GetUnitPosition(), Player_rotation, winsize.x, Setting::Radar::zoom);
              Vector2D line = dirArrowPos - screenpos;

              float arrowWidth = scale;
              float arrowTheta = 45.f;
              float length = sqrtf(powf(line.x, 2.f) + powf(line.y, 2.f));

              Vector2D arrowBase = dirArrowPos - (arrowWidth / (2 * (tanf(arrowTheta) / 2) * length)) * line;
              Vector2D normal = Vector2D(-line.y, line.x);
              Vector2D left = arrowBase + arrowWidth / (2 * length) * normal;
              Vector2D right = arrowBase + -arrowWidth / (2 * length) * normal;

              draw_list->AddTriangleFilled(ImVec2(winpos.x + left.x, winpos.y + left.y),
                  ImVec2(winpos.x + right.x, winpos.y + right.y),
                  ImVec2(winpos.x + dirArrowPos.x, winpos.y + dirArrowPos.y),
                  ImColor(230, 230, 230));

              if (Setting::Radar::name) {
                  draw_list->AddText(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y), color, entity->GetObjectName());
              }

              if (entity->IsGameObject() && Setting::Radar::GameObject) {
                  shape = EntityShape_t::SHAPE_SQUARE;
              }

              switch (shape) {
              case EntityShape_t::SHAPE_CIRCLE:
                  draw_list->AddCircleFilled(ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y), scale, color);
                  break;
              case EntityShape_t::SHAPE_SQUARE:
                  draw_list->AddRectFilled(ImVec2(winpos.x + screenpos.x - scale, winpos.y + screenpos.y - scale),
                      ImVec2(winpos.x + screenpos.x + scale, winpos.y + screenpos.y + scale),
                      color, 0.0f, 0);
                  break;
              case EntityShape_t::SHAPE_TRIANGLE:
                  draw_list->AddTriangleFilled(ImVec2(winpos.x + screenpos.x + scale, winpos.y + screenpos.y + scale),
                      ImVec2(winpos.x + screenpos.x - scale, winpos.y + screenpos.y + scale),
                      ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y - scale),
                      color);
                  break;
              case EntityShape_t::SHAPE_TRIANGLE_UPSIDEDOWN:
                  draw_list->AddTriangleFilled(ImVec2(winpos.x + screenpos.x - scale, winpos.y + screenpos.y - scale),
                      ImVec2(winpos.x + screenpos.x + scale, winpos.y + screenpos.y - scale),
                      ImVec2(winpos.x + screenpos.x, winpos.y + screenpos.y + scale),
                      color);
                  break;
              }
          }
        void RenderWindow(const std::vector<Icon>& icons) {

            //ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiSetCond_FirstUseEver);
            ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX), SquareConstraint);


            if (ImGui::Begin("Radar", &Setting::Radar::Enabled,
               /* ImGuiWindowFlags_NoResize | */ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
                ImGuiWindowFlags_NoTitleBar)) {

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 winpos = ImGui::GetWindowPos();
                ImVec2 winsize = ImGui::GetWindowSize();

                const float titleBarHeight = 25.0f;
                const ImU32 titleBarColor = IM_COL32(153, 0, 0, 255);     // Dark red for title bar
                const ImU32 gridLineColor = IM_COL32(80, 80, 80, 255);    // Gray grid lines

                // 1. Find the "home" icon in the icons vector
                auto iconIt = std::find_if(icons.begin(), icons.end(), [&](const Icon& icon) {
                    return icon.displayName == "Home";
                    });

                // 2. Draw title bar (solid dark red)
                draw_list->AddRectFilled(winpos, ImVec2(winpos.x + winsize.x, winpos.y + titleBarHeight),
                    titleBarColor);

                // 3. Draw radar title on the left
                ImGui::SetCursorPos(ImVec2(8.0f, 4.0f)); // Adjust text position
                ImGui::Text("Radar");

                // 4. Draw home icon on the right side of the title bar if found
                if (iconIt != icons.end()) {
                    ImGui::SameLine(winsize.x - 24.0f); // Position icon to the right
                    ImGui::Image((ImTextureID)iconIt->texture, ImVec2(16, 16)); // Render the home icon
                }

                // 5. Draw radar background (solid black)
                draw_list->AddRectFilled(ImVec2(winpos.x, winpos.y + titleBarHeight),
                    ImVec2(winpos.x + winsize.x, winpos.y + winsize.y),
                    IM_COL32(0, 0, 0, 255));

                // 6. Draw grid lines (2x2 grid)
                const int numLines = 2;
                float cellSize = (winsize.y - titleBarHeight) / numLines;

                for (int i = 1; i < numLines; i++) {
                    // Vertical line (X-axis)
                    draw_list->AddLine(ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + titleBarHeight),
                        ImVec2(winpos.x + winsize.x * 0.5f, winpos.y + winsize.y),
                        gridLineColor, 1.0f);

                    // Horizontal line (Y-axis)
                    draw_list->AddLine(ImVec2(winpos.x, winpos.y + titleBarHeight + i * cellSize),
                        ImVec2(winpos.x + winsize.x, winpos.y + titleBarHeight + i * cellSize),
                        gridLineColor, 1.0f);
                }

                WObject* localPlayer = (WObject*)GlobalVars::LocalPlayer;
                if (!localPlayer)
                {
                    ImGui::End();
                    return;
                }

                float scale = Setting::Radar::iconsScale;

                for (auto& [guid, Object] : GlobalVars::Objects)
                {

                    if (!Object)
                        continue;

                    if (!Object->isValid())
                        continue;

                    if (!Object->IsAnyObj())
                        continue;

                    ImColor color;

                    if (Object->IsPlayer() && Setting::Radar::Player)
                    {

                        WObject* player = (WObject*)Object;

                       /* if ((player->IsDead()) && !Setting::Radar::DrawDeadEntity)
                            continue;*/

                        /*if (Utils::IsUnitEnemy(player) && !Setting::Radar::HostilePlayers)
                            continue;*/

                        color = ImColor(11, 74, 122);//Setting::Radar::PlayerColor.Color(player);
                       // color = ColorSettings::Radar::PlayerColor.Color(player);

                        DrawObj(localPlayer, player, color, draw_list, winpos, winsize);
                    }

                    else if (Object->IsUnit() && Setting::Radar::Unit) {

                        WObject* Unit = (WObject*)Object;

                        if (Unit == localPlayer)
                            continue;

                      /*  if (Unit->IsDead() && !Setting::Radar::DrawDeadEntity)
                            continue;*/

                   /*     if (GameUtils::IsUnitEnemy(Unit) && !Setting::Radar::HostileUnits)
                            continue;*/

                        //color = ColorSettings::Radar::UnitColor.Color(Unit);
                        color = ImColor(1, 34, 52);
                        DrawObj(localPlayer, Unit, color, draw_list, winpos, winsize);
                    }
                    else if (Object->IsGameObject() && Setting::Radar::GameObject) {

                        WObject* GameObj = (WObject*)Object;

                        /*if (!GameMethods::CGGameObject_C_IsLocked(entity)) {
                            color = Setting::Radar::UnlockedGameObjectColor.Color();
                        }
                        else {
                            color = Setting::Radar::GameObjectColor.Color();
                        }*/

                        //color = ColorSettings::Radar::GameObjectColor.Color();
                        color = ImColor(11, 04, 122);
                        DrawObj(localPlayer, GameObj, color, draw_list, winpos, winsize);
                    }
                }

                ImGui::End();
            }
        }
    }
}