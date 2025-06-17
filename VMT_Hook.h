#pragma once

#include "FC.h"

#ifndef VMT_HOOK_H
#define VMT_HOOK_H

namespace VMT
{
    inline int   FilledRecords = 0;

#pragma bss_seg(push, ".hkdata")
    inline PVOID HookData[10000];
#pragma bss_seg(pop)
}

class VMT_Hook
{
private:
    PVOID* TblEnc = nullptr;
    DWORD  Size = 0;

    __forceinline bool InExecMemory(PVOID Addr, DWORD64 ModBase, PIMAGE_NT_HEADERS NtHeader)
    {
        PIMAGE_SECTION_HEADER Sect = IMAGE_FIRST_SECTION(NtHeader);
        for (DWORD Cnt = 0; Cnt < NtHeader->FileHeader.NumberOfSections; Cnt++, Sect++)
        {
            if ((Sect->Characteristics & IMAGE_SCN_MEM_EXECUTE) &&
                ((DWORD64)Addr >= (ModBase + Sect->VirtualAddress)) &&
                ((DWORD64)Addr < (ModBase + Sect->VirtualAddress + Sect->Misc.VirtualSize)))
            {
                return true;
            }
        }
        return false;
    }

public:
    template <typename T>
    __forceinline VMT_Hook(const char* Module, T Class)
    {
        DWORD64 ModBase = (DWORD64)GetModuleBase(Module);
        Size = 0;

        PVOID* VFTable = *(PVOID**)Class;
        PIMAGE_NT_HEADERS NtHeader =
            (PIMAGE_NT_HEADERS)(ModBase + ((PIMAGE_DOS_HEADER)ModBase)->e_lfanew);

        while (InExecMemory(VFTable[Size], ModBase, NtHeader))
        {
            Size++;
        }

        auto* VFT_New = &VMT::HookData[VMT::FilledRecords];
        __movsq((PDWORD64)VFT_New, (const PDWORD64)VFTable, Size);

        // Replace the class's VFTable pointer
        *(PVOID**)Class = VFT_New;

        // Possibly store an encrypted pointer
        TblEnc = (PVOID*)EPtr(VFT_New);

        // Advance global "FilledRecords"
        VMT::FilledRecords += Size;
    }

    // Template SetupHook
    template <typename T>
    __forceinline void SetupHook(T* Original, PVOID Hook, int Index)
    {
        PVOID* Tbl = (PVOID*)EPtr(TblEnc);
        *Original = (T)Tbl[Index];
        Tbl[Index] = Hook;
    }
};

#endif // VMT_HOOK_H
