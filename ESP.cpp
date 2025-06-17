#include "ESP.h"
#include "../Settings.h" // Ensure this includes the definition for Settings
#include "../GlobalVars.h"  // Ensure this includes the definition for Globals
#include "../Utils/Utils.h"    // Ensure this includes utility functions like GetClassColor
//#include "nav.h"      // Ensure this includes navigation waypoints
#include "../GameMethods.h" // Ensure this includes game method invocations
#include "../Camera.h"
#include "../Utils/ScriptFunctions.h"
#include "../Utils/ColorVar.h"

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

//namespace Draw
//{
//    Renderer::Renderer() = default;
//    Renderer::~Renderer() = default;
//
//    void Renderer::Initialize()
//    {
//        if (!m_pFont)
//        {
//            ImGuiIO& io = ImGui::GetIO();
//            m_pFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.0f);
//        }
//    }
//
//    void Renderer::BeginScene()
//    {
//        ImGuiIO& io = ImGui::GetIO();
//        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
//        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
//        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
//        ImGui::Begin("##Backbuffer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
//        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
//        ImGui::SetWindowSize(io.DisplaySize, ImGuiCond_Always);
//    }
//
//  
//    //void Renderer::PreDraw()
//    //{
//    //    if (!Setting::ESP::Enabled || !GlobalVars::LocalPlayer)
//    //        return;
//
//    //    for (const auto& [guid, object] : GlobalVars::Objects)
//    //    {
//    //        if (!object || !object->isValid())
//    //            continue;
//
//    //        int typeID = static_cast<int>(object->GetType());
//    //        if (typeID != static_cast<int>(TypeId::CGUnit) &&
//    //            typeID != static_cast<int>(TypeId::CGPlayer) &&
//    //            typeID != static_cast<int>(TypeId::CGGameObject) &&
//    //            typeID != static_cast<int>(TypeId::CGCorpse))
//    //            continue;
//
//    //        if (!Utils::ValidCoord(object))
//    //            continue;
//
//    //        ImColor color;
//    //        if (object->IsUnit())
//    //        {
//    //          /*  if (object->IsDead() && !Setting::ESP::DrawDeadEntity)
//    //                continue;*/
//
//    //            if (ScriptFunctions::IsUnitEnemy(object))
//    //            {
//    //                if (typeID == static_cast<int>(TypeId::CGUnit) && !Setting::ESP::HostileUnits)
//    //                    continue;
//    //                if (typeID == static_cast<int>(TypeId::CGPlayer) && !Setting::ESP::HostileUnits)
//    //                    continue;
//    //            }
//
//    //            color = Setting::ESP::UnitColor.getColor(object);
//    //        }
//    //        else if (object->IsPlayer())
//    //        {
//    //            color = Setting::ESP::PlayerColor.getColor(object);
//    //        }
//    //        else if (object->IsGameObject())
//    //        {
//    //            color = Setting::ESP::GameObjectColor.getColor();
//    //        }
//    //        else if (object->IsCorpse())
//    //        {
//    //            color = Setting::ESP::CorpseColor.getColor();
//    //        }
//
//    //        DrawObjects(object, color);
//    //    }
//    //}
//
//    void Renderer::EndScene()
//    {
//     //   PreDraw();
//
//        ImGuiWindow* window = ImGui::GetCurrentWindow();
//        window->DrawList->PushClipRectFullScreen();
//
//        window->DrawList->AddText(ImVec2(5, 0), ImColor(0, 162, 232), "X-HOOK for World of warcraft");
//
//        ImGui::End();
//        ImGui::PopStyleColor();
//        ImGui::PopStyleVar(2);
//    }
//}