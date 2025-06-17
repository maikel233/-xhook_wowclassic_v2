#pragma once

#include "../Utils/Singleton.h"
#include <imgui.h>
#include "WObject.h" // Ensure this includes the definition for WObject
#include "Utils/ColorVar.h"

namespace Draw
{
    class Renderer : public Singleton<Renderer>
    {
        friend class Singleton<Renderer>;

    protected:
        Renderer();
        ~Renderer();

    public:
        void Initialize();
        void BeginScene();
        void EndScene();
        void PreDraw();
        void DrawObjects(WObject* entity, const HealthColorVar& color);

    private:
        ImFont* m_pFont = nullptr;
    };
}

#define g_sRenderer Draw::Renderer::GetInstance()
