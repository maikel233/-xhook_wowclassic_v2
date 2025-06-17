#pragma once

#include <imgui.h>
#include "../Settings.h"
#include "../Utils/Vector.h"
#include "../CustomImGui/MenuElements.h"
namespace Setting {
    namespace Radar {
        extern bool name;
        extern bool Player;
        extern bool LocalPlayer;
        extern bool Corpse;
        extern bool Unit;
        extern bool GameObject;
        extern bool Object;
        extern bool Enabled;
        extern bool DrawDeadEntity;

        extern bool HostileUnits;
        extern bool HostilePlayers;

        extern float zoom;
        extern float iconsScale;
        extern float multiply;
    }
}

namespace Draw {
    namespace Radar {
        enum EntityShape_t : int {
            SHAPE_CIRCLE,
            SHAPE_SQUARE,
            SHAPE_TRIANGLE,
            SHAPE_TRIANGLE_UPSIDEDOWN
        };

        //Vector2D WorldToRadar(const Vector3 location, const Vector3 origin, float Player_rotation, int width, float scale = 16.f);
        void SquareConstraint(ImGuiSizeCallbackData* data);
        float RadianToDegree(float Rotation);
        void DrawObj(WObject* localplayer, WObject* entity, ImColor color, ImDrawList* draw_list, ImVec2 winpos, ImVec2 winsize);
        void RenderWindow(const std::vector<Icon>& icons);
    }
}
