#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include <string>
#include "../WObject.h"

// Draw namespace
namespace Draw {
    extern ImFont* m_pFont;
    extern bool InitFont;

   // void RenderBones(__int64 a1, __int64 a2);
    void Draw2DBox(WObject* entity, ImU32 color, bool useDynamicHeight);
    void Draw3DBox(WObject* entity, ImU32 color);

    void Initialize();
    void BeginScene();
    void EndScene();
    void PreDraw();
  //  void DrawObjects(WObject* localplayer, WObject* entity, ImColor color, ImDrawList* draw_list);
    void RenderTextWithDynamicSize(const char* text, ImVec2 position, ImU32 color, float distance);

   // bool inBlackList(WItem* item, std::vector<std::string> blackList);
   // bool inBlackList(WObject* o, std::vector<std::string> blackList);
}
