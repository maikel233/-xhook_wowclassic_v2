#pragma once
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <d3d11.h> // Ensure this is included for ID3D11ShaderResourceView
#include "CustomImGui/MenuElements.h"
#include "WObject.h"
// Forward declaration of Icon
struct Icon;

#define WRITABLE (PAGE_READWRITE | PAGE_GRAPHICS_READWRITE | PAGE_GRAPHICS_EXECUTE_READ | PAGE_GRAPHICS_EXECUTE_READWRITE | PAGE_EXECUTE_READ | PAGE_READONLY | PAGE_GRAPHICS_READONLY | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)

namespace GlobalVars
{
    extern bool hooked;
    extern std::map<std::string, WObject*> Objects;
    extern std::map<std::string, WObject*> invalidObjects;
    extern WObject* LocalPlayer;
    extern std::wstring GameVersion;
    extern int iResult;
    extern int recvbuflen;
    extern uintptr_t g_hModuleBase;
    extern uintptr_t g_pModuleEnd;
    extern bool g_bInutet;
    extern bool ImGui_Initialised;
    extern bool ShowMenu;

    extern int swapchaincount;
    extern IDXGISwapChain* Swapchains[20];
    extern IDXGISwapChain* g_pSwapChain;
    extern HWND g_hWindow;
    extern int MAX_SWAPCHAINS;
    extern bool bFoundAllSwapchains;

    extern std::vector<Icon> icons;  // Now the compiler knows 'Icon' is a struct
    extern ID3D11ShaderResourceView* logoTexture;
}

namespace DirectX11Interface
{
    extern ID3D11Device* Device;
    extern ID3D11DeviceContext* DeviceContext;
    extern ID3D11RenderTargetView* RenderTargetView;
}
