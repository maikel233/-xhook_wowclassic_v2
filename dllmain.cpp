
#include "EncStr.h"
#include "FC.h"
#include "Utils/BuildInfo.h"
#include "GlobalVars.h"
#include "Hooks.h"
#include "Offsets.h"
#include "ObjectManager.h"
#include "Utils/Utils.h"
#include "Camera.h"
//#include <conio.h> // For _getch()


bool bRunning = true;

DWORD WINAPI ObjectManagerLoop(LPVOID lpParam)
{
    while (bRunning)
    {
        // Call CycleObjects with refresh = false to keep cycling objects periodically
        ObjectManager::CycleObjects(false);

        // You can add a delay (e.g., 100 milliseconds) to prevent excessive CPU usage
     /*   Sleep(100);*/
    }
    return 0;
}


void MainInit() {
   // SetUnhandledExceptionFilter(Utils::VectoredHandler);
     GlobalVars::g_hModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
     FC::SetSpoofStub(FC::FindPattern_Wrapper(E("FF 27")));

     GlobalVars::GameVersion = GetBuildVersion_FileVersion();
     std::wcout << L"Detected game version: " << GlobalVars::GameVersion << L"\n";


     //// Supported versions
     //const std::vector<std::wstring> supportedVersions = {
     //    L"11.0.7.58238",  // Retail
     //    L"4.4.1.57141",   // Classic PTR
     //    L"1.0.0"          // SOD servers 
     //};

     //// Check if the detected version is in the list of supported versions
     //if (std::find(supportedVersions.begin(), supportedVersions.end(), GlobalVars::GameVersion) == supportedVersions.end()) {
     //    std::wcerr << L"Unsupported game version: " << GlobalVars::GameVersion << L". Press any key to quit...\n";
     //    _getch(); // Wait for a key press before exiting
     //    return;   // Exit early if the version is not supported
     //}

     Offsets::InitStaticOffsets();



     if (ObjectManager::InGame) {

        
         ObjectManager::TestObjectManager();
         // Create a new thread for the ObjectManager loop
         CreateThread(NULL, 0, ObjectManagerLoop, NULL, 0, NULL);

        // We should loop -> Check for invalid objs and add new objs.
        // ObjectManager::TestObjectManager();
        // ObjectManager::Test();
      //   int i = Utils::getEmptySlots();

       //  ObjectManager::CycleObjects(false);
       //  ObjectManager::Test();

        if (WoW::camera::GCamera == nullptr) WoW::camera::Init(); 
     }

    FindSwapChains(0);
    HookRenderHook(GetRealSwapChain());
    HookResize(GetRealSwapChain());      
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
     
#if DebugConsole
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
#endif
        MainInit();      
        return true;
    }
    return false;
}