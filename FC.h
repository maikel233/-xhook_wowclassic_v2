#pragma once
#ifndef FC_MACROS_H
#define FC_MACROS_H

#include "pch.h"
#include "../EncStr.h"
#include <winternl.h>
#include <stdio.h>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
//
//  FC Namespace - "Header-Only" Implementation
//
////////////////////////////////////////////////////////////////////////////////

typedef struct LDR_DATA_TABLE_ENTRY_FIX {
    PVOID Reserved1[2];
    LIST_ENTRY InMemoryOrderLinks;
    PVOID Reserved2[2];
    PVOID DllBase;
    PVOID Reserved3[1];
    ULONG64 SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    PVOID Reserved5[2];
#pragma warning(push)
#pragma warning(disable: 4201)
    union {
        ULONG CheckSum;
        PVOID Reserved6;
    } DUMMYUNIONNAME;
#pragma warning(pop)
    ULONG TimeDateStamp;
};

namespace FC
{
    //////////////////////////////////////////////////////////////////////////////
    //  1) Global Variables
    //////////////////////////////////////////////////////////////////////////////

    // Use 'inline' so that multiple .cpp files including this header 
    // do not cause multiple-definition linker errors (C++17 feature).
    inline PVOID ReturnAddressStubEnc = nullptr;

    //////////////////////////////////////////////////////////////////////////////
    //  2) Spoofer Declaration
    //////////////////////////////////////////////////////////////////////////////
    extern "C" void* _spoofer_stub();

    //////////////////////////////////////////////////////////////////////////////
    //  3) Helper Macros
    //////////////////////////////////////////////////////////////////////////////

#define RVA(Instr, InstrSize) ((DWORD64)(Instr) + InstrSize + *(LONG*)((DWORD64)(Instr) + ((InstrSize) - sizeof(LONG))))
// Macro to extract offset dynamically(the offset could change, e.g., 0x118, 0x555, etc.)
#define GetOffsetFromPattern(Pattern, InstrSize) \
    ( *(LONG*)((uintptr_t)(FindPattern(Pattern)) + (InstrSize)) )  // Extract the offset (e.g., 0x118)

#define ConstStrLen(Str) ((sizeof(Str) - sizeof(Str[0])) / sizeof(Str[0]))
#define ToLower(Char) ((Char >= 'A' && Char <= 'Z') ? (Char + 32) : Char)

//////////////////////////////////////////////////////////////////////////////
//  4) String Compare Template
//////////////////////////////////////////////////////////////////////////////
    template <typename StrType, typename StrType2>
    inline bool StrCmp(StrType Str, StrType2 InStr, bool Two = false)
    {
        if (!Str || !InStr) return false;
        wchar_t c1, c2;
        do {
            c1 = *Str++;
            c2 = *InStr++;
            c1 = ToLower(c1);
            c2 = ToLower(c2);
            if (!c1 && (Two ? !c2 : true))
                return true;
        } while (c1 == c2);
        return false;
    }

    //////////////////////////////////////////////////////////////////////////////
    //  5) CRC16 String Hash Template
    //////////////////////////////////////////////////////////////////////////////
    template <typename StrType>
    constexpr unsigned short HashStr(StrType Data, int Len)
    {
        unsigned short CRC = 0xFFFF;
        while (Len--)
        {
            auto CurChar = *Data++;
            if (!CurChar) break;
            CRC ^= ToLower(CurChar) << 8;
            for (int i = 0; i < 8; i++)
            {
                CRC = (CRC & 0x8000) ? (CRC << 1) ^ 0x8408 : (CRC << 1);
            }
        }
        return CRC;
    }
#define ConstHashStr(Str) [](){ constexpr unsigned short CRC = FC::HashStr(Str, ConstStrLen(Str)); return CRC; }()

    //////////////////////////////////////////////////////////////////////////////
    //  6) Encrypt/Decrypt Pointer
    //////////////////////////////////////////////////////////////////////////////
    template <typename PtrType>
    __forceinline PtrType EPtrImpl(PtrType Ptr)
    {
        union CryptData
        {
            struct { USHORT Key1, Key2, Key3, Key4; };
            ULONG64 Key;
        };
        // Use compile-time hashed strings, e.g. __TIME__, etc.
        CryptData Key{
            ConstHashStr(__TIME__),
            ConstHashStr(__DATE__),
            ConstHashStr(__TIMESTAMP__),
            ConstHashStr(__TIMESTAMP__)
        };
        return (PtrType)((DWORD64)Ptr ^ Key.Key);
    }

    //////////////////////////////////////////////////////////////////////////////
    //  7) Spoof Call Implementation
    //////////////////////////////////////////////////////////////////////////////
    template <typename Ret = void,
        typename First = void*,
        typename Second = void*,
        typename Third = void*,
        typename Fourth = void*,
        typename... Stack>
    __forceinline Ret SpoofCallImpl(
        void* Func,
        First a1 = First{},
        Second a2 = Second{},
        Third a3 = Third{},
        Fourth a4 = Fourth{},
        Stack... args
    )
    {
        struct shell_params { const void* a1; void* a2; void* a3; };
        shell_params CallCtx = { EPtrImpl(ReturnAddressStubEnc), Func, nullptr };

        typedef Ret(*ShellFn)(First, Second, Third, Fourth, PVOID, PVOID, Stack...);
        return ((ShellFn)&FC::_spoofer_stub)(a1, a2, a3, a4, &CallCtx, nullptr, args...);
    }

    //////////////////////////////////////////////////////////////////////////////
    //  8) VFTable Call Implementation
    //////////////////////////////////////////////////////////////////////////////
    template <typename Ret = void, typename... Args>
    __forceinline Ret VCallImpl(PVOID Class, int Index, Args... AddArgs)
    {
        return SpoofCallImpl<Ret>((*(PVOID**)Class)[Index], Class, AddArgs...);
    }

    //////////////////////////////////////////////////////////////////////////////
    //  9) GetModuleBase (Wrapper)
    //////////////////////////////////////////////////////////////////////////////
    template <typename StrType>
    inline PBYTE GetModuleBase_Wrapper(StrType ModuleName)
    {
        PPEB_LDR_DATA Ldr = ((PTEB)__readgsqword(FIELD_OFFSET(NT_TIB, Self)))->ProcessEnvironmentBlock->Ldr; void* ModBase = nullptr;
        for (PLIST_ENTRY CurEnt = Ldr->InMemoryOrderModuleList.Flink; CurEnt != &Ldr->InMemoryOrderModuleList; CurEnt = CurEnt->Flink) {
            LDR_DATA_TABLE_ENTRY_FIX* pEntry = CONTAINING_RECORD(CurEnt, LDR_DATA_TABLE_ENTRY_FIX, InMemoryOrderLinks);
            if (!ModuleName || StrCmp(ModuleName, pEntry->BaseDllName.Buffer, false)) return (PBYTE)pEntry->DllBase;
        } return nullptr;
    }

    //////////////////////////////////////////////////////////////////////////////
    // 10) FindPattern Implementation (Inline)
    //////////////////////////////////////////////////////////////////////////////
    inline PBYTE FindPattern_Wrapper(const char* Pattern, const char* Module = nullptr)
    {
#define InRange(x, a, b) (x >= a && x <= b)
#define GetBits(x) (InRange(x, '0', '9') ? (x - '0') : ((x - 'A') + 0xA))
#define GetByte(x) ((BYTE)(GetBits(x[0]) << 4 | GetBits(x[1])))

        PBYTE ModuleStart = (PBYTE)FC::GetModuleBase_Wrapper(Module);
        if (!ModuleStart) return nullptr;

        auto* NtHeader = (PIMAGE_NT_HEADERS)(ModuleStart + ((PIMAGE_DOS_HEADER)ModuleStart)->e_lfanew);
        PBYTE ModuleEnd = (PBYTE)(ModuleStart + NtHeader->OptionalHeader.SizeOfImage);

        PBYTE FirstMatch = nullptr;
        const char* CurPatt = Pattern;

        for (; ModuleStart < ModuleEnd; ++ModuleStart)
        {
            bool SkipByte = (*CurPatt == '?');
            if (SkipByte || *ModuleStart == GetByte(CurPatt))
            {
                if (!FirstMatch) FirstMatch = ModuleStart;
                SkipByte ? CurPatt += 2 : CurPatt += 3;
                if (CurPatt[-1] == 0)
                    return FirstMatch;
            }
            else if (FirstMatch)
            {
                ModuleStart = FirstMatch;
                FirstMatch = nullptr;
                CurPatt = Pattern;
            }
        }

        //TODO replace with print
#if DebugConsole
        std::cout << ("Pattern failed: %s\n", Pattern); 
#endif
        return nullptr;
    }

    //////////////////////////////////////////////////////////////////////////////
    // 11) SetSpoofStub (Inline)
    //////////////////////////////////////////////////////////////////////////////
    inline void SetSpoofStub(PVOID R15_Stub)
    {
        ReturnAddressStubEnc = EPtrImpl(R15_Stub);
    }

    //////////////////////////////////////////////////////////////////////////////
    // 12) GetExportAddress (Inline)
    //////////////////////////////////////////////////////////////////////////////
    inline PVOID GetExportAddress(PBYTE hDll, const char* Name)
    {
        if (!hDll || !Name) return nullptr;

        auto* NtHeader = (PIMAGE_NT_HEADERS)(hDll + ((PIMAGE_DOS_HEADER)hDll)->e_lfanew);
        auto* ExportDir = (PIMAGE_EXPORT_DIRECTORY)(hDll + NtHeader->OptionalHeader.DataDirectory[0].VirtualAddress);

        for (DWORD i = 0; i < ExportDir->NumberOfNames; i++)
        {
            USHORT Ordinal = ((USHORT*)(hDll + ExportDir->AddressOfNameOrdinals))[i];
            const char* ExpName = (const char*)hDll + ((DWORD*)(hDll + ExportDir->AddressOfNames))[i];
            if (StrCmp(Name, ExpName))
            {
                return (PVOID)(hDll + ((DWORD*)(hDll + ExportDir->AddressOfFunctions))[Ordinal]);
            }
        }
        return nullptr;
    }

} // namespace FC

////////////////////////////////////////////////////////////////////////////////
//
//  Public Macros to Match Your Usage
//
////////////////////////////////////////////////////////////////////////////////

#define EPtr(Ptr)           FC::EPtrImpl(Ptr)
#define GetModuleBase       FC::GetModuleBase_Wrapper
#define FindPattern         FC::FindPattern_Wrapper
#define SpoofCall           FC::SpoofCallImpl
#define VCall               FC::VCallImpl

// Example: If you used FCA(...) macros
#define FCA(Mod, Name, ...) [&]() { \
    static PVOID FAddr = nullptr; \
    if (!FAddr) FAddr = EPtr(FC::GetExportAddress(FC::GetModuleBase_Wrapper(E(#Mod)), E(#Name))); \
    return SpoofCall<decltype(Name(__VA_ARGS__))>(EPtr(FAddr), __VA_ARGS__); \
}()

////////////////////////////////////////////////////////////////////////////////
//
//  Printing Helper (Inline) - optional
//
////////////////////////////////////////////////////////////////////////////////
template<typename... Args>
inline void Print(const char* Format, Args... args)
{
    static bool Once = false;
    if (!Once) {
        // Equivalent to AllocConsole, only do it once
        FCA(kernel32, AllocConsole);
        Once = true;
    }

    char Buff[2048];
    FCA(ntdll, sprintf, Buff, Format, args...);
    int StrLengthOut = FCA(ntdll, strlen, Buff);
    HANDLE Out = FCA(kernel32, GetStdHandle, STD_OUTPUT_HANDLE);
    FCA(kernel32, WriteConsoleA, Out, Buff, StrLengthOut, NULL, NULL);
}

// For debugging macros (dp, hp, sp, etc.):
#define dp(a)      Print("DEC (%d): %d\n", __LINE__, (a))
#define hp(a)      Print("HEX (%d): %p\n", __LINE__, (a))
#define sp(a)      Print("STR (%d): %s\n", __LINE__, (a))

#endif // FC_MACROS_H



















////#pragma once
////#ifndef FC_MACROS_H
////#define FC_MACROS_H
////
////#include <windows.h>
////#include <cstdint>
////#include <type_traits>
////#include "Constants.h"
////
////namespace FC
////{
////
////
////    // Global Variables
////    extern PVOID ReturnAddressStubEnc;
////
////    // External Functions
////    extern "C" void* _spoofer_stub();
////
////    // Static Macro Definitions
////#define RVA(Instr, InstrSize) ((DWORD64)Instr + InstrSize + *(LONG*)((DWORD64)Instr + (InstrSize - sizeof(LONG))))
////#define ConstStrLen(Str) ((sizeof(Str) - sizeof(Str[0])) / sizeof(Str[0]))
////#define ToLower(Char) ((Char >= 'A' && Char <= 'Z') ? (Char + 32) : Char)
////
////// String Comparison Implementation
////    template <typename StrType, typename StrType2>
////    bool StrCmp(StrType Str, StrType2 InStr, bool Two = false) {
////        if (!Str || !InStr) return false;
////        wchar_t c1, c2;
////        do {
////            c1 = *Str++;
////            c2 = *InStr++;
////            c1 = ToLower(c1);
////            c2 = ToLower(c2);
////            if (!c1 && (Two ? !c2 : true)) return true;
////        } while (c1 == c2);
////        return false;
////    }
////
////    // CRC16 String Hash Implementation
////    template <typename StrType>
////    constexpr unsigned short HashStr(StrType Data, int Len) {
////        unsigned short CRC = 0xFFFF;
////        while (Len--) {
////            auto CurChar = *Data++;
////            if (!CurChar) break;
////            CRC ^= ToLower(CurChar) << 8;
////            for (int i = 0; i < 8; i++) {
////                CRC = CRC & 0x8000 ? (CRC << 1) ^ 0x8408 : CRC << 1;
////            }
////        }
////        return CRC;
////    }
////#define ConstHashStr(Str) [](){ constexpr unsigned short CRC = HashStr(Str, ConstStrLen(Str)); return CRC; }()
////    // Encrypt/Decrypt Pointer Implementation
////    template <typename PtrType>
////    __forceinline PtrType EPtrImpl(PtrType Ptr) {
////        union CryptData {
////            struct { USHORT Key1, Key2, Key3, Key4; };
////            ULONG64 Key;
////        };
////        CryptData Key{ ConstHashStr(__TIME__), ConstHashStr(__DATE__), ConstHashStr(__TIMESTAMP__), ConstHashStr(__TIMESTAMP__) };
////        return (PtrType)((DWORD64)Ptr ^ Key.Key);
////    }
////  
////    // Spoof Call Implementation
////    template <typename Ret = void, typename First = void*, typename Second = void*, typename Third = void*, typename Fourth = void*, typename... Stack>
////    __forceinline Ret SpoofCallImpl(void* Func, First a1 = First{}, Second a2 = Second{}, Third a3 = Third{}, Fourth a4 = Fourth{}, Stack... args) {
////        struct shell_params { const void* a1; void* a2; void* a3; };
////        shell_params CallCtx = { EPtrImpl(ReturnAddressStubEnc), Func, nullptr };
////        typedef Ret(*ShellFn)(First, Second, Third, Fourth, PVOID, PVOID, Stack...);
////        return ((ShellFn)&FC::_spoofer_stub)(a1, a2, a3, a4, &CallCtx, nullptr, args...);
////    }
////
////    // VFTable Call Implementation
////    template <typename Ret = void, typename... Args>
////    __forceinline Ret VCallImpl(PVOID Class, int Index, Args... AddArgs) {
////        return SpoofCallImpl<Ret>((*(PVOID**)Class)[Index], Class, AddArgs...);
////    }
////
////    template <typename StrType>
////    PBYTE GetModuleBase_Wrapper(StrType ModuleName) {
////        PPEB_LDR_DATA Ldr = ((PTEB)__readgsqword(FIELD_OFFSET(NT_TIB, Self)))->ProcessEnvironmentBlock->Ldr; void* ModBase = nullptr;
////        for (PLIST_ENTRY CurEnt = Ldr->InMemoryOrderModuleList.Flink; CurEnt != &Ldr->InMemoryOrderModuleList; CurEnt = CurEnt->Flink) {
////            LDR_DATA_TABLE_ENTRY_FIX* pEntry = CONTAINING_RECORD(CurEnt, LDR_DATA_TABLE_ENTRY_FIX, InMemoryOrderLinks);
////            if (!ModuleName || StrCmp(ModuleName, pEntry->BaseDllName.Buffer, false)) return (PBYTE)pEntry->DllBase;
////        } return nullptr;
////    }
////
////    PBYTE FindPattern_Wrapper(const char* Pattern, const char* Module = nullptr);
////
////    void SetSpoofStub(PVOID R15_Stub);
////
////    PVOID GetExportAddress(PBYTE hDll, const char* Name);
////
////    extern PVOID ReturnAddressStubEnc;
////
////
////} // namespace FC
////// Macro Definitions for Function Calls
////#define EPtr(Ptr) FC::EPtrImpl(Ptr)
////#define GetModuleBase FC::GetModuleBase_Wrapper
////
////#define FindPattern FC::FindPattern_Wrapper
////#define SpoofCall FC::SpoofCallImpl
////#define VCall FC::VCallImpl
////  // Macro Implementation
////#define FCA(Mod, Name, ...) [&]() { \
////        static PVOID FAddr = nullptr; \
////        if (!FAddr) FAddr = EPtr(FC::GetExportAddress(FC::GetModuleBase_Wrapper(E(#Mod)), E(#Name))); \
////        return SpoofCall<decltype(Name(__VA_ARGS__))>(EPtr(FAddr), __VA_ARGS__); \
////    }()
////
////template<typename... Args>
////void Print(const char* Format, Args... args)
////{
////    static bool Once = false;
////    if (!Once) {
////        FCA(kernel32, AllocConsole);
////        Once = true;
////    }
////
////    char Buff[2048];
////    FCA(ntdll, sprintf, Buff, Format, args...);
////    int StrLengthOut = FCA(ntdll, strlen, Buff);
////    HANDLE Out = FCA(kernel32, GetStdHandle, STD_OUTPUT_HANDLE);
////    FCA(kernel32, WriteConsoleA, Out, Buff, StrLengthOut, NULL, NULL);
////}
////
////
////#define dp(a) Print(E("DEC (%d): %d\n"), __LINE__, (a))
////#define hp(a) Print(E("HEX (%d): %p\n"), __LINE__, (a))
////#define sp(a) Print(E("STR (%d): %s\n"), __LINE__, (a))
////#define wsp(a) Print(E("STR (%d): %ws\n"), __LINE__, (a))
////#define fp(a) Print(E("FLOAT (%d): %d.%d\n"), __LINE__, (int)(a), (int)(((a) - (int)(a)) * 1000000));
////#define v2p(a) { fp(a.x); fp(a.y); }
////#define v3p(a) { fp(a.x); fp(a.y); fp(a.z); }
////#define dp(a)
////#define hp(a)
////#define sp(a)
////
////
////namespace VMT {
////    inline int FilledRecords = 0;
////#pragma bss_seg(push, ".hkdata")
////    inline PVOID HookData[10000];
////#pragma bss_seg(pop)
////}
////
////class VMT_Hook {
////private:
////    PVOID* TblEnc = nullptr;
////    DWORD Size = 0;
////
////    __forceinline bool InExecMemory(PVOID Addr, DWORD64 ModBase, PIMAGE_NT_HEADERS NtHeader) {
////        PIMAGE_SECTION_HEADER Sect = IMAGE_FIRST_SECTION(NtHeader);
////        for (DWORD Cnt = 0; Cnt < NtHeader->FileHeader.NumberOfSections; Cnt++, Sect++) {
////            if ((Sect->Characteristics & IMAGE_SCN_MEM_EXECUTE) &&
////                ((DWORD64)Addr >= (ModBase + Sect->VirtualAddress)) &&
////                ((DWORD64)Addr < (ModBase + Sect->VirtualAddress + Sect->Misc.VirtualSize))) {
////                return true;
////            }
////        }
////        return false;
////    }
////
////public:
////    template <typename T>
////    inline VMT_Hook(const char* Module, T Class) {
////        DWORD64 ModBase = (DWORD64)GetModuleBase(Module);
////        Size = 0;
////        PVOID* VFTable = *(PVOID**)Class;
////        PIMAGE_NT_HEADERS NtHeader = (PIMAGE_NT_HEADERS)(ModBase + ((PIMAGE_DOS_HEADER)ModBase)->e_lfanew);
////
////        while (InExecMemory(VFTable[Size], ModBase, NtHeader)) {
////            Size++;
////        }
////
////        auto* VFT_New = &VMT::HookData[VMT::FilledRecords];
////        __movsq((PDWORD64)VFT_New, (const PDWORD64)VFTable, Size);
////        *(PVOID**)Class = VFT_New;
////        TblEnc = (PVOID*)EPtr(VFT_New);
////        VMT::FilledRecords += Size;
////    }
////
////    template <typename T>
////    __forceinline void SetupHook(T* Original, PVOID Hook, int Index) {
////        PVOID* Tbl = (PVOID*)EPtr(TblEnc);
////        *Original = (T)Tbl[Index];
////        Tbl[Index] = Hook;
////    }
////};
////
////#endif // FC_MACROS_H