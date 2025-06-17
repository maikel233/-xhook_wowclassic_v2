#pragma once
#include <windows.h>
#include <string>
#include <vector>
#include <iostream>

// Instruct the linker to include Version.lib
#pragma comment(lib, "Version.lib")

inline std::wstring GetBuildVersion_FileVersion()
{
    // 1) Get the path to the running process's main module
    wchar_t exePath[MAX_PATH] = {};
    DWORD length = GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    if (length == 0 || length == MAX_PATH) { return L"Error getting module file name."; }

    // 2) Query version info size
    DWORD dummy = 0;
    DWORD szVersion = GetFileVersionInfoSizeW(exePath, &dummy);
    if (szVersion == 0) { return L"Error getting version info size."; }

    // 3) Allocate buffer
    std::vector<BYTE> versionInfo(szVersion);

    // 4) Read the version info
    if (!GetFileVersionInfoW(exePath, 0, szVersion, versionInfo.data())) {  return L"Error reading version info."; }

    // 5) Extract fixed file info
    VS_FIXEDFILEINFO* pFileInfo = nullptr;
    UINT sizeFileInfo = 0;
    if (!VerQueryValueW(versionInfo.data(), L"\\",
        reinterpret_cast<LPVOID*>(&pFileInfo),
        &sizeFileInfo) || !pFileInfo)
    {
        return L"Error querying fixed file info.";
    }

    // 6) Extract major.minor.revision.build
    WORD major = HIWORD(pFileInfo->dwFileVersionMS);
    WORD minor = LOWORD(pFileInfo->dwFileVersionMS);
    WORD revision = HIWORD(pFileInfo->dwFileVersionLS);
    WORD build = LOWORD(pFileInfo->dwFileVersionLS);

    // 7) Convert to a human-readable string
    std::wstring result = std::to_wstring(major) + L"." +
        std::to_wstring(minor) + L"." +
        std::to_wstring(revision) + L"." +
        std::to_wstring(build);
    return result;
}