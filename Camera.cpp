#include "Camera.h"
#include "Offsets.h"         // If Offsets::Base and Offsets::CameraMgr are declared here
#include "ImGui/imgui.h"     // If using ImGui for DisplaySize
#include <iostream>          // For std::cout if needed
#include "GameMethods.h"
#include <DirectXMath.h>
namespace WoW
{

    //18C camera goes up.
    //1FC  WorldFrame:ClearAllPoint
    //25C ckamera_MaxZoom
    //260 camera_CurrentZoom
    //2BC Camera_up
    // Static member definition
    CameraMgr* camera::GCamera = nullptr;

    void camera::Init()
    {
        // Acquire the camera manager pointer dynamically
        uintptr_t cameraBaseAddr = *reinterpret_cast<uintptr_t*>(Offsets::Offset_CameraMgr);
        auto* cameraMgr = reinterpret_cast<CameraMgr*>(cameraBaseAddr);
        GCamera = cameraMgr;

        // Use POffset::CameraPointer for the dynamic offset
        uintptr_t dynamicOffset = Offsets::Offset_CameraPtr; // Update this with your offset logic

        // Retrieve the CameraMgrPtr
        CameraMgrPtr* cameraPtr = cameraMgr->GetCameraPtr();

        if (cameraPtr) { std::cout << "[+] FOV: " << cameraPtr->GetFOV() << std::endl; }
        else {  std::cerr << "[-] Failed to retrieve CameraPtr!" << std::endl; }
        std::cout << "[+] CameraMgr address: 0x" << std::hex << cameraMgr << std::dec << std::endl;
    }

    
    bool camera::TraceLine(WObject* object, const Vector3& target, IntersectFlags intersectFlags)
    {
        if (!object)
            return false;

        // Acquire start and end positions
        Vector3 start = object->GetUnitPosition();
        Vector3 end = target;

        // Initialize the parameters structure
        TraceLineParams params;
        params.start = start;
        params.end = end;
        params.hit = Vector3{ 0.f, 0.f, 0.f }; // Initialize hit position
        params.distance = 1.0f;                // Initial distance
        params.flags = intersectFlags;         // Set intersection flags

        // Invoke the new intersection function
        bool collision = GameMethods::Invoke<bool>(
            Offsets::Offset_WorldFrame_Intersect,                     // New function offset
            GameMethods::Invoke<int64_t>(Offsets::Offset_WorldFrame_GetWorld), // GetWorld() as first parameter (a1)
            reinterpret_cast<int64_t>(&params),               // Pointer to params structure (a2)
            static_cast<int64_t>(intersectFlags)             // Additional parameter (a3), adjust as needed
        );

        // 'collision' indicates if something was hit
        // Return true if line-of-sight is clear (no collision)
        return !collision;
    }

    void camera::setfloattest(float test) {
        // Ensure camera is initialized
        if (!GCamera)
            camera::Init();

        // Check if we still failed to get a camera or cameraptr
        if (!GCamera || !GCamera->GetCameraPtr())
            return;

        CameraMgrPtr* pCamera = GCamera->GetCameraPtr();

        pCamera->SetFOV(test);
    }


    Vector2 camera::WorldToScreenv2(const Vector3& pos)
    {
        // Ensure camera is initialized
        if (!GCamera)
            camera::Init();

        // Check if we still failed to get a camera or cameraptr
        if (!GCamera || !GCamera->GetCameraPtr())
            return Vector2{ 0.f, 0.f };

        CameraMgrPtr* pCamera = GCamera->GetCameraPtr();

        // Use ImGui for screen dimensions
        ImGuiIO& io = ImGui::GetIO();
        RECT rc{ 0, 0, (LONG)io.DisplaySize.x, (LONG)io.DisplaySize.y };

        // Compute difference from camera pos
        Vector3 difference{ pos.x - pCamera->GetCameraPosition().x,
                            pos.y - pCamera->GetCameraPosition().y,
                            pos.z - pCamera->GetCameraPosition().z };

        // Dot product with forward vector to see if it's behind the camera
        float product =
            difference.x * pCamera->GetMatrix().M11 +
            difference.y * pCamera->GetMatrix().M12 +
            difference.z * pCamera->GetMatrix().M13;

        // If behind camera, discard
        if (product < 0.0f)
            return Vector2{ 0.f, 0.f };

        // Invert the camera matrix
        Matrix3x3 inverse = pCamera->GetMatrix().Inverse();

        // Transform difference into camera space
        Vector3 view{
            inverse.M11 * difference.x + inverse.M21 * difference.y + inverse.M31 * difference.z,
            inverse.M12 * difference.x + inverse.M22 * difference.y + inverse.M32 * difference.z,
            inverse.M13 * difference.x + inverse.M23 * difference.y + inverse.M33 * difference.z
        };

        // Reorient to typical screen axes
        Vector3 cameraSpace{ -view.y, -view.z, view.x };

        // Screen center
        Vector2 screenCenter{
            (rc.right - rc.left) * 0.5f,
            (rc.bottom - rc.top) * 0.5f
        };

        // Aspect ratio scaling - these multipliers are guesswork from your original code
        float fovX = (pCamera->GetFOV() * 55.0f) * 0.5f;
        float fovY = (pCamera->GetFOV() * 35.0f) * 0.5f;
        Vector2 aspect{
            screenCenter.x / tanf(fovX * M_DEG2RAD),
            screenCenter.y / tanf(fovY * M_DEG2RAD)
        };

        // Calculate final screen position
        Vector2 screenPos{
            screenCenter.x + (cameraSpace.x * aspect.x / cameraSpace.z),
            screenCenter.y + (cameraSpace.y * aspect.y / cameraSpace.z)
        };

        // Check if the point is within screen bounds
        if (screenPos.x < 0.f || screenPos.y < 0.f ||
            screenPos.x >(float)rc.right || screenPos.y >(float)rc.bottom)
        {
            return Vector2{ 0.f, 0.f };
        }

        return screenPos;
    }
}
