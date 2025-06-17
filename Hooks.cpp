#include "Hooks.h"
#include "Offsets.h"
#include "ObjectManager.h"

// Definitions of extern variables
PresentFn       oPresent = nullptr;
//PlayerHookFn    PlayerHookOriginal = nullptr;
ResizeBuffersfn oResize = nullptr;

typedef NTSTATUS(NTAPI* tNtReadVirtualMemory)(
    IN HANDLE ProcessHandle,
    IN PVOID BaseAddress,
    OUT PVOID Buffer,
    IN ULONG NumberOfBytesToRead,
    OUT PULONG NumberOfBytesReaded);

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


// In this .cpp, you can define all the big hooking logic functions that used 
// to be in that giant header.

static bool IsValidPtr_Internal(uint64_t ptr)
{
    // An internal helper if needed, or rely on the template in the .h
    return (ptr >= 0x10000 && ptr < 0x7FFFFFFFFFFF);
}

IDXGISwapChain* GetRealSwapChain()
{
    DWORD offy = *(DWORD*)(FindPattern(E("8B ? ? ? ? ? 48 8B 01 48 8D 55"), E("dxgi")) + 2);
    for (int i = 0; i < GlobalVars::swapchaincount; i++)
    {
        IDXGISwapChain* Current = GlobalVars::Swapchains[i];
        __try
        {
            uintptr_t TestAddy = *(DWORD64*)((DWORD64)Current + offy);
            if (IsValidPtr(TestAddy))
                return Current;
        }
        __except (1)
        {
            continue;
        }
    }
    return nullptr;
}

DWORD __stdcall FindSwapChains(HANDLE test)
{
#if DebugConsole
    Print("Start FindSwapChain\n");
#endif // DebugConsole
    MEMORY_BASIC_INFORMATION mbi;
    uintptr_t temp = 0;
    ULONG BytesReaded = NULL;
    char val[64];
    uintptr_t dwStart = 0x100000;
    uintptr_t dwVal = RVA((uintptr_t)FindPattern(E("48 8D 05 ? ? ? ? 48 89 01 48 8D 05 ? ? ? ? 48 89 41 08 48 8D 05 ? ? ? ? 48 89 41 10 48 8D 05 ? ? ? ? 48 89 41 58 48 8D 05 ? ? ? ? 48 89 41 60 48 8D 05 ? ? ? ? 48 89 41 68 48 8D 05 ? ? ? ? 48 89 41 70 48 8D 05 ? ? ? ? 48 89 41 78 48 8D 05 ? ? ? ? 48 89 81 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 81 ? ? ? ? 48 B8 ? ? ? ? ? ? ? ? 48 89 41 40 E8 ? ? ? ?"), E("dxgi")), 7);
    tNtReadVirtualMemory pNtReadVirtualMemory = (tNtReadVirtualMemory)GetProcAddress(GetModuleHandle("ntdll"), "NtReadVirtualMemory");
   
    while (1)
    {
        VirtualQuery((void*)dwStart, &mbi, sizeof(mbi));
        if (mbi.State & MEM_COMMIT && mbi.Protect & WRITABLE)
        {
            for (uintptr_t i = dwStart; i <= (uintptr_t)mbi.BaseAddress + mbi.RegionSize; i += 8)
            {
                if (pNtReadVirtualMemory(GetCurrentProcess(), (void*)i, &temp, 8, &BytesReaded) == 0)
                {
                    if (temp == dwVal)
                    {
                        GlobalVars::Swapchains[GlobalVars::swapchaincount] = (IDXGISwapChain*)i;
                        GlobalVars::swapchaincount++;

#if DebugConsole
                        Print("Found SwapChain at 0x%x vtable 0x%x\n", i, temp);
#endif // DebugConsole

                        // Exit the loop once a SwapChain is found
                        return 1;
                    }
                }
            }
            dwStart += mbi.RegionSize;
        }
        else
        {
            dwStart = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
        }

        if (dwStart > 0x7fffffeffff)
        {
#if DebugConsole
            Print("End Founding SwapChain\n");
#endif // DebugConsole
            break;
        }
    }
}

void HookRenderHook(IDXGISwapChain* SwapChain)
{
    GlobalVars::g_pSwapChain = SwapChain;
    DWORD Offy = *(DWORD*)(FindPattern(E("8B ? ? ? ? ? 48 8B 01 48 8D 55"), E("dxgi")) + 2);
    void* pClass = (void*)(*(DWORD64*)((DWORD64)SwapChain + Offy));

    // Create the hook
    VMT_Hook D3D(E("d3d11"), pClass);

    D3D.SetupHook(
        reinterpret_cast<void**>(&oPresent),
        reinterpret_cast<void*>(Present),
        13
    );
}

HRESULT Resize_hk(IDXGISwapChain* pSwapChain,
    UINT BufferCount,
    UINT Width,
    UINT Height,
    DXGI_FORMAT NewFormat,
    UINT SwapChainFlags)
{
    if (DirectX11Interface::RenderTargetView)
    {
        DirectX11Interface::DeviceContext->OMSetRenderTargets(0, 0, 0);
        DirectX11Interface::RenderTargetView->Release();
    }

    HRESULT hr = oResize(
        pSwapChain,
        BufferCount,
        Width,
        Height,
        NewFormat,
        SwapChainFlags);

    ID3D11Texture2D* pBuffer = nullptr;
    GlobalVars::g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);

    DirectX11Interface::Device->CreateRenderTargetView(pBuffer, NULL, &DirectX11Interface::RenderTargetView);
    pBuffer->Release();

    DirectX11Interface::DeviceContext->OMSetRenderTargets(1, &DirectX11Interface::RenderTargetView, NULL);

    // Set up the viewport.
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)Width;
    vp.Height = (FLOAT)Height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0.f;
    vp.TopLeftY = 0.f;
    DirectX11Interface::DeviceContext->RSSetViewports(1, &vp);

    return hr;
}

void HookResize(IDXGISwapChain* SwapChain)
{
    VMT_Hook d3d("dxgi", SwapChain);
    d3d.SetupHook(
        reinterpret_cast<void**>(&oResize),
        reinterpret_cast<void*>(Resize_hk),
        13
    );
}

// WndProc hooking
static WNDPROC OriginalWndProcHandler = nullptr;

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (GlobalVars::ShowMenu)
    {
        ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
        return true;
    }
    return CallWindowProc(OriginalWndProcHandler, hwnd, uMsg, wParam, lParam);
}

void HookWndProc()
{
    static bool bHooked = false;
    if (!bHooked)
    {
        auto tid = FCA(user32, GetWindowThreadProcessId, GlobalVars::g_hWindow, nullptr);
        bHooked = true;
        SpoofCall(SetWindowsHookExW, WH_GETMESSAGE, WndProc, nullptr, tid);
    }
}

void SetWnd()
{
    static bool bSetted = false;
    if (!bSetted)
    {
        DXGI_SWAP_CHAIN_DESC swapchain_desc{ 0 };
        VCall(GlobalVars::g_pSwapChain, 12, &swapchain_desc);
        GlobalVars::g_hWindow = swapchain_desc.OutputWindow;
        bSetted = true;
    }
}

// The actual Present hook
void __fastcall Present(PVOID a1, PVOID a2)
{

    __try
    {
        SetWnd();
        HookWndProc();

        if (!GlobalVars::ImGui_Initialised)
        {
            if (SUCCEEDED(GlobalVars::g_pSwapChain->GetDevice(__uuidof(ID3D11Device),
                (void**)&DirectX11Interface::Device)))
            {
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

                DirectX11Interface::Device->GetImmediateContext(&DirectX11Interface::DeviceContext);

                ID3D11Texture2D* BackBuffer = nullptr;
                GlobalVars::g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
                DirectX11Interface::Device->CreateRenderTargetView(BackBuffer, NULL, &DirectX11Interface::RenderTargetView);
                BackBuffer->Release();


                ImGui_ImplWin32_Init(GlobalVars::g_hWindow);
                ImGui_ImplDX11_Init(DirectX11Interface::Device, DirectX11Interface::DeviceContext);
                ImGui_ImplDX11_CreateDeviceObjects();

                ImGuiViewport* main_viewport = ImGui::GetMainViewport();
                main_viewport->PlatformHandleRaw = GlobalVars::g_hWindow;

                OriginalWndProcHandler = (WNDPROC)(SetWindowLongPtrA(GlobalVars::g_hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc));
                GlobalVars::ImGui_Initialised = true;
            }
        }

        // Example code from your old Present hook

        if (GetAsyncKeyState(VK_INSERT) & 1)
            GlobalVars::ShowMenu = !GlobalVars::ShowMenu;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::GetIO().MouseDrawCursor = GlobalVars::ShowMenu;

        Draw::BeginScene();
        Draw::EndScene();

        // Load Icons
        if (GlobalVars::logoTexture == NULL) { LoadEmbeddedLogoD3D11(); }
        if (GlobalVars::icons.empty()) { LoadIconsFromMemory(GlobalVars::icons); }

        // 1) You can do your object loops, drawing, etc.
        //ObjectManager::LoopFuncs();

       


        // 2) If showing menu, render it
        if (GlobalVars::ShowMenu)
        {       
            RenderMenu(GlobalVars::icons);
            Draw::Radar::RenderWindow(GlobalVars::icons);
        }

        ImGui::EndFrame();
        ImGui::Render();

        DirectX11Interface::DeviceContext->OMSetRenderTargets(1, &DirectX11Interface::RenderTargetView, NULL);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
    __except (1)
    {
        // swallow exceptions
    }

    // call original
    SpoofCall(oPresent, a1, a2);
}








