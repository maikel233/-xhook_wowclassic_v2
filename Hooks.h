#pragma once
#ifndef HOOK_STUFF_H
#define HOOK_STUFF_H

//#include "pch.h"  // Or any other needed headers

// If you require these macros in multiple files, keep them here or in a shared header
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

// Forward declarations or includes for DirectX types
#include <d3d11.h>  // for ID3D11* (if needed)
#include <dxgi.h>   // for IDXGISwapChain, DXGI_FORMAT, etc.

// Forward declarations for anything else used in these functions
// Example:
#include "GlobalVars.h"
#include "VMT_Hook.h"  // If you define your hooking class in another header

#include "Draw.h"
#include "CustomImGui/MenuElements.h"
#include "Radar.h"
#include <imgui_impl_dx11.h>
#include "FC.h"
#include <imgui_impl_win32.h>

// Typedefs for function pointers
typedef void(__fastcall* PresentFn)(PVOID a1, PVOID a2);
typedef void(__fastcall* PlayerHookFn)(uintptr_t, uintptr_t, uintptr_t);
typedef HRESULT(__stdcall* ResizeBuffersfn)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

// Extern so we define them once in .cpp
extern PresentFn       oPresent;
extern PlayerHookFn    PlayerHookOriginal;
extern ResizeBuffersfn oResize;

// Functions
void __fastcall Present(PVOID a1, PVOID a2);


IDXGISwapChain* GetRealSwapChain();
DWORD __stdcall FindSwapChains(HANDLE test);

// Render Hook
void HookRenderHook(IDXGISwapChain* SwapChain);

// Resize Hook
HRESULT Resize_hk(
    IDXGISwapChain* pSwapChain,
    UINT BufferCount,
    UINT Width,
    UINT Height,
    DXGI_FORMAT NewFormat,
    UINT SwapChainFlags
);
void HookResize(IDXGISwapChain* SwapChain);

// WndProc hooking
LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void HookWndProc();

// Example for setting window from swapchain
void SetWnd();

// Additional helpers used in your code
template <typename Type>
static bool IsValidPtr(Type ptr)
{
    return ((uint64_t)(ptr) >= 0x10000 && ptr && (long long)ptr < 0x7FFFFFFFFFFF);
}
#endif // HOOK_STUFF_H