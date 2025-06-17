#pragma once

#include <cstdint>          // For standard integer types
#include <Windows.h>        // If you need RECT (or remove if using another struct)
#include "Utils/Vector.h"   // Vector2, Vector3, Matrix3x3
//#include "Settings/Settings.h"  // If you need Settings::Hacks usage
#include "Constants.h"      // If you need Offsets, IntersectFlags, etc.
#include "WObject.h"        // For TraceLine usage with WObject
#include "Offsets.h"
// If you have your own custom degrees-to-radians constant, keep it here:
#ifndef M_DEG2RAD
#define M_DEG2RAD 0.017453292519943295769236907684886f
#endif

class CameraMgrPtr
{
public:
    Vector3 GetCameraPosition() const
    {
        return *reinterpret_cast<const Vector3*>(reinterpret_cast<uintptr_t>(this) + 0x0010);
    }

    Matrix3x3 GetMatrix() const
    {
        // Offset for Matrix3x3
        return *reinterpret_cast<const Matrix3x3*>(reinterpret_cast<uintptr_t>(this) + 0x001C);
    }

    float GetFOV() const
    {
        // Offset for FOV
        return *reinterpret_cast<const float*>(reinterpret_cast<uintptr_t>(this) + 0x0040);
    }

    void SetFOV(float newFOV) {
        *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(this) + 0x0040) = newFOV;
    }

    //18C camera goes up.
    //1FC  WorldFrame:ClearAllPointstr
    //25C ckamera_MaxZoom
    //260 camera_CurrentZoom
    //2BC Camera_up
};

class CameraMgr
{
public:
    CameraMgrPtr* GetCameraPtr() const {
        return *reinterpret_cast<CameraMgrPtr**>(reinterpret_cast<uintptr_t>(this) + Offsets::Offset_CameraPtr);
    }
};

struct TraceLineParams {
    Vector3 start;      // Starting position
    Vector3 end;        // Target position
    Vector3 hit;        // Output hit position
    float distance;     // Output distance
    IntersectFlags flags; // Intersection flags
    // Add any additional fields if required based on further analysis
};

namespace WoW
{
    /**
     * camera:
     * Provides static methods to initialize camera pointers,
     * convert world coordinates to screen coordinates, and trace lines.
     */
    class camera
    {
    public:
        // Holds the global camera pointer once Init() is called
        static CameraMgr* GCamera;

        // Initialize the camera pointer from game memory
        static void Init();

       // Vector3 ScreenToWorld(float x, float y, float screenWidth, float screenHeight, WObject* object, IntersectFlags intersectFlags);
       // static std::pair<Vector2, bool> WorldToScreen(const Vector3& worldPosition);

        static void setfloattest(float test);

        // Raycast or intersection check (line-of-sight style)
        static bool TraceLine(WObject* object, const Vector3& target, IntersectFlags intersectFlags);
        static Vector2 WorldToScreenv2(const Vector3& pos);
    };
}
