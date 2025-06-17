#include "VMT_Hook.h"
#include "FC.h"
// ---------------------------------------------------------------------------
// Define the extern VMT variables exactly once
// ---------------------------------------------------------------------------
namespace VMT
{
    int   FilledRecords = 0;

#pragma bss_seg(push, ".hkdata")
    void* HookData[10000];
#pragma bss_seg(pop)
}


// ---------------------------------------------------------------------------
// Private method: check if a pointer is in an executable section
// ---------------------------------------------------------------------------
bool VMT_Hook::InExecMemory(void* Addr, uint64_t ModBase, PIMAGE_NT_HEADERS NtHeader)
{
    PIMAGE_SECTION_HEADER Sect = IMAGE_FIRST_SECTION(NtHeader);
    for (DWORD Cnt = 0; Cnt < NtHeader->FileHeader.NumberOfSections; Cnt++, Sect++) {
        if ((Sect->Characteristics & IMAGE_SCN_MEM_EXECUTE) &&
            ((DWORD64)Addr >= (ModBase + Sect->VirtualAddress)) &&
            ((DWORD64)Addr < (ModBase + Sect->VirtualAddress + Sect->Misc.VirtualSize))) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// Constructor (non-template)
// ---------------------------------------------------------------------------
VMT_Hook::VMT_Hook(const char* Module, void* pClass)
{
    // 1) Get the module base
    uint64_t ModBase = (uint64_t)GetModuleBase(Module);

    // 2) Reset our size
    Size = 0;

    // 3) Interpret pClass as a pointer to a VFTable pointer
    void** VFTable = *(void***)pClass;

    // 4) Get NT headers from the module base
    PIMAGE_NT_HEADERS NtHeader =
        reinterpret_cast<PIMAGE_NT_HEADERS>(ModBase +
            reinterpret_cast<PIMAGE_DOS_HEADER>(ModBase)->e_lfanew);

    // 5) Count how many entries in VFTable are in executable memory
    while (InExecMemory(VFTable[Size], ModBase, NtHeader))
    {
        Size++;
    }

    // 6) Copy the original VFTable into HookData at offset VMT::FilledRecords
    void** NewVFT = &((void**)VMT::HookData)[VMT::FilledRecords];
    __movsq(
        reinterpret_cast<unsigned long long*>(NewVFT),
        reinterpret_cast<const unsigned long long*>(VFTable),
        Size
    );

    // 7) Replace the class's VFTable pointer with the new one
    *(void***)pClass = NewVFT;

    // 8) Possibly store it in an "encrypted" form
    TblEnc = (void**)EPtr(NewVFT);

    // 9) Advance the global hook-data index
    VMT::FilledRecords += Size;
}

// ---------------------------------------------------------------------------
// SetupHook (non-template)
// ---------------------------------------------------------------------------
void VMT_Hook::SetupHook(void** Original, void* Hook, int Index)
{
    // Decrypt or fix up the pointer if needed
    void** pVFT = (void**)EPtr(TblEnc);

    // Save the original function pointer
    *Original = pVFT[Index];

    // Overwrite with our hook
    pVFT[Index] = Hook;
}
