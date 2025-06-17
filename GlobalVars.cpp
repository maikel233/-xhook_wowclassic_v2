#include "GlobalVars.h"
//#include "CustomImGui/MenuElements.h"

namespace GlobalVars
{
    bool hooked = false;
    WObject* LocalPlayer = 0;
    std::map<std::string, WObject*> Objects = {};
    std::map<std::string, WObject*> invalidObjects = {};
    std::wstring GameVersion = {};

    //struct addrinfo* result = nullptr;
    //struct addrinfo* ptr = nullptr;
    //struct addrinfo hints2 = {};

    int iResult = 0;

    uintptr_t g_hModuleBase = NULL;
    uintptr_t g_pModuleEnd = NULL;
    bool g_bInutet = false;

    bool ImGui_Initialised = false;
    HWND g_hWindow = nullptr;
    bool ShowMenu = false;

    int swapchaincount = 0;
    IDXGISwapChain* Swapchains[20] = { nullptr };
    IDXGISwapChain* g_pSwapChain = nullptr;

    // Maximum number of swapchains we will store.
    int MAX_SWAPCHAINS = 4;

    // For debugging or other usage
    bool bFoundAllSwapchains = false;


    std::vector<Icon> icons = {};
    ID3D11ShaderResourceView* logoTexture = NULL; // Global variable for the logo texture
}

namespace DirectX11Interface
{
    ID3D11Device* Device = nullptr;
    ID3D11DeviceContext* DeviceContext = nullptr;
    ID3D11RenderTargetView* RenderTargetView = nullptr;
}
