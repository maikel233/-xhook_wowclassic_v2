#include "MenuElements.h"

//#include "../ObjectManager.h"
//end of our icons

#include "..//assets/icons/logo.c"
#include "..//assets/icons/user.c"
#include "..//assets/icons/menu.c"
#include "..//assets/icons/info.c"
#include "..//assets/icons/home.c"
#include "..//assets/icons/globe.c"
#include "..//assets/icons/gear.c"
#include "..//assets/icons/crosshair.c"
#include "..//assets/icons/question-sign.c"

#include "../Offsets.h"
#include "../ObjectManager.h"
#include "../WItem.h"
#include "../GameMethods.h"
#include "../Utils/Utils.h"
#include "../Camera.h"
#include "../visuals/EntityList.h"
#include <unordered_set>

#include "../Core/SpellBook.h"
#include "../VMT_Hook.h"
//#include "../Utils/Utils.cpp"

bool Setting::ESP::Enabled = false;
bool Setting::ESP::Lines = true;
bool Setting::ESP::DrawBox = true;
bool Setting::ESP::GuidStr = true;
bool Setting::ESP::Names = true;
bool Setting::ESP::UnitRank = true;
bool Setting::ESP::Lvl = false;
bool Setting::ESP::Health = false;
bool Setting::ESP::Power = false;
bool Setting::ESP::HostilePlayers = false;
bool Setting::ESP::HostileUnits = false;
bool Setting::ESP::Ally = true;
bool Setting::ESP::Enemy = true;
bool Setting::ESP::Unit = true;
bool Setting::ESP::TraceLine = false;
bool Setting::ESP::Player = false;
bool Setting::ESP::LocalPlayer = false;
bool Setting::ESP::DrawDeadEntity = false;
bool Setting::ESP::Object = false;
bool Setting::ESP::GameObject = false;
bool Setting::ESP::DynamicObject = false;
bool Setting::ESP::Race = false;
bool Setting::ESP::Horde, Setting::ESP::Alliance = false;
bool Setting::ESP::Corpse = false;
bool Setting::ESP::WayPoints = false;

float Setting::Camera::Camera_zoomout = 0.0f;
float Setting::Camera::Camera_zoomin = 0.0f;
float Setting::Camera::Camera_fov = 90.0f;      // Default FOV value
bool Setting::Camera::Enable = false;

float ftest = 1.0f;
float ftest2 = 4.5f;
float ftest3 = 4.5f;
bool a = false;
bool b = true;
float Camera_zoomout = 0, Camera_zoomin = 0, Camera_fov = 40.0f;
bool showESPPopupFilters = false;
bool showRadarPopupFilters = false;

//Test vals
float Setting::ESP::Distance = 25.f;
float Setting::ESP::Distance2 = 25.f;


static float customCameraValue = 1.5f; // Default valu


// Translate old colors into the new system
const ImVec4 COLOR_SIDEBAR = ImVec4(35.0f / 255.0f, 28.0f / 255.0f,30.0f / 255.0f, 1.0f);
const ImVec4 COLOR_MAIN_CONTENT = ImVec4(14.0f / 255.0f, 18.0f / 255.0f, 23.0f / 255.0f, 1.0f); // Main content background (from old main background)
const ImVec4 COLOR_GROUPBOX = ImVec4(31.0f / 255.0f, 45.0f / 255.0f, 66.0f / 255.0f, 1.0f); // Groupbox or section separators (from old horizontal and bottom bars)
const ImVec4 COLOR_BUTTON = ImVec4(27.0f / 255.0f, 75.0f / 255.0f, 118.0f / 255.0f, 1.0f); // Button or highlighted bar color
const ImVec4 COLOR_BUTTON_HOVER = ImVec4(31.0f / 255.0f, 45.0f / 255.0f, 66.0f / 255.0f, 1.0f); // Button hover effect
const ImVec4 COLOR_BUTTON_ACTIVE = ImVec4(45.0f / 255.0f, 75.0f / 255.0f, 118.0f / 255.0f, 1.0f); // Button active color
const ImVec4 COLOR_TEXT = ImVec4(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 1.0f); // Text color (white)
const ImVec4 COLOR_TEXT_DISABLED = ImVec4(136.0f / 255.0f, 136.0f / 255.0f, 134.0f / 255.0f, 1.0f); // Disabled text color (gray)
const ImVec4 COLOR_TITLEBAR = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); // A dark gray color
const ImVec4 COLOR_TOP_BAR = ImVec4(0.12f, 0.14f, 0.18f, 1.0f); // Dark gray-blue color

void SetupImGuiStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // General Styling
    style.WindowRounding = 5.0f; // Rounded corners for windows
    style.FrameRounding = 4.0f; // Rounded corners for widgets
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding = 4.0f;

    style.WindowPadding = ImVec2(8, 8);
    style.FramePadding = ImVec2(4, 3);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 4);

    // Colors
    colors[ImGuiCol_WindowBg] = COLOR_MAIN_CONTENT; // Top menu & main content background
    colors[ImGuiCol_Border] = ImVec4(0.2f, 0.2f, 0.2f, 0.5f); // Border color
    colors[ImGuiCol_FrameBg] = COLOR_GROUPBOX; // Groupbox background
    colors[ImGuiCol_FrameBgHovered] = COLOR_BUTTON_HOVER; // Hovered groupbox background
    colors[ImGuiCol_FrameBgActive] = COLOR_BUTTON_ACTIVE; // Active groupbox background

    colors[ImGuiCol_TitleBg] = COLOR_MAIN_CONTENT; // Title background
    colors[ImGuiCol_TitleBgCollapsed] = COLOR_MAIN_CONTENT;
    colors[ImGuiCol_TitleBgActive] = COLOR_MAIN_CONTENT;

    colors[ImGuiCol_MenuBarBg] = COLOR_MAIN_CONTENT; // Menu bar background

    colors[ImGuiCol_Button] = COLOR_BUTTON; // Button color
    colors[ImGuiCol_ButtonHovered] = COLOR_BUTTON_HOVER; // Button hover
    colors[ImGuiCol_ButtonActive] = COLOR_BUTTON_ACTIVE; // Button active

    colors[ImGuiCol_Header] = COLOR_BUTTON; // Header color
    colors[ImGuiCol_HeaderHovered] = COLOR_BUTTON_HOVER; // Header hover
    colors[ImGuiCol_HeaderActive] = COLOR_BUTTON_ACTIVE; // Header active

    colors[ImGuiCol_Tab] = COLOR_GROUPBOX; // Tab background
    colors[ImGuiCol_TabHovered] = COLOR_BUTTON_HOVER; // Tab hover
    colors[ImGuiCol_TabActive] = COLOR_BUTTON; // Tab active
    colors[ImGuiCol_TabUnfocused] = COLOR_GROUPBOX; // Unfocused tab background
    colors[ImGuiCol_TabUnfocusedActive] = COLOR_BUTTON; // Active unfocused tab

    colors[ImGuiCol_Text] = COLOR_TEXT; // Text color
    colors[ImGuiCol_TextDisabled] = COLOR_TEXT_DISABLED; // Disabled text color
    colors[ImGuiCol_TextSelectedBg] = COLOR_BUTTON_HOVER; // Highlighted text background

    colors[ImGuiCol_CheckMark] = COLOR_BUTTON; // Checkbox checkmark
    colors[ImGuiCol_SliderGrab] = COLOR_BUTTON_HOVER; // Slider grab
    colors[ImGuiCol_SliderGrabActive] = COLOR_BUTTON_ACTIVE; // Active slider grab
    // Adjust remaining colors as needed
}

static EmbeddedIconInfo embeddedIcons[] = {
    { "globe-solid",       "Open World",  globe,     sizeof(globe)     },
    { "bars-solid",        "Dashboard",   menubars,  sizeof(menubars)  },
    { "crosshairs-solid",  "Aim",         crosshair, sizeof(crosshair) },
    { "gear-solid",        "Settings",    gear,      sizeof(gear)      },
    { "house-solid",       "Home",        home,      sizeof(home)      },
    { "user-solid",        "Profile",     user,      sizeof(user)      },
    // If you want to include the "info" icon as well:
    { "info-solid",        "Info",        info,      sizeof(info)      },
    { "questionsign-solid","questionsign",questionsign,sizeof(questionsign)}
};


// Global state to track active category and subcategory
static std::string activeCategory = "Open World";
static std::string activeSubcategory = "Visuals";

// Sidebar hover and selected colors
ImVec4 sidebarHoverColor = ImVec4(0.25f, 0.25f, 0.50f, 1.0f);
ImVec4 sidebarSelectedColor = ImVec4(0.35f, 0.35f, 0.65f, 1.0f);
ImVec4 groupBoxColor = ImVec4(0.18f, 0.18f, 0.28f, 1.0f);

std::map<std::string, std::string> topCategoryIconMap = {
    {"Open World", "globe-solid"},
    {"Dungeons", "bars-solid"},
    {"Gathering", "crosshairs-solid"},
    {"Quests", "house-solid"},
    {"Settings", "gear-solid"}
};


// Category to subcategory map
std::map<std::string, std::vector<std::string>> categorySubcategoryMap = {
    {"Open World", {"Visuals", "Environment"}},
    {"Dungeons", {"Maps", "Enemies"}},
    {"Settings", {"EntityList", "Other"}}
};

// Optional: Directly associate subcategories with icons (if needed)
std::map<std::string, std::string> subcategoryIconMap = {
    {"Visuals", "globe-solid"},
    {"Environment", "globe-solid"}, // Reusing the same icon
    {"Maps", "bars-solid"},
    {"Enemies", "crosshairs-solid"},
    {"Graphics", "gear-solid"},
    {"Audio", "gear-solid"}
};


bool LoadIconsFromMemory(std::vector<Icon>& icons)
{

    ID3D11Device* device = DirectX11Interface::Device;
    if (!device)
    {
        std::cerr << "[ERROR] D3D11 device is NULL.\n";
        return false;
    }

    icons.clear();

    int iconCount = static_cast<int>(sizeof(embeddedIcons) / sizeof(embeddedIcons[0]));
    for (int i = 0; i < iconCount; i++)
    {
        const auto& iconInfo = embeddedIcons[i];

        // Decode the embedded image (PNG) with stb_image
        int width = 0, height = 0, channels = 0;
        unsigned char* data = stbi_load_from_memory(
            iconInfo.data,
            static_cast<int>(iconInfo.dataSize),
            &width, &height, &channels,
            4 // force RGBA
        );

        if (!data)
        {
            std::cerr << "[ERROR] Failed to load icon: " << iconInfo.displayName << "\n";
            std::cerr << "        STB reason: "
                << (stbi_failure_reason() ? stbi_failure_reason() : "Unknown") << "\n";
            continue;
        }

        // Describe a 2D texture
        D3D11_TEXTURE2D_DESC texDesc = {};
        texDesc.Width = width;
        texDesc.Height = height;
        texDesc.MipLevels = 1;
        texDesc.ArraySize = 1;
        texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        texDesc.SampleDesc.Count = 1;
        texDesc.Usage = D3D11_USAGE_DEFAULT;
        texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        texDesc.CPUAccessFlags = 0;
        texDesc.MiscFlags = 0;

        // Initial data
        D3D11_SUBRESOURCE_DATA initData = {};
        initData.pSysMem = data;
        initData.SysMemPitch = width * 4; // RGBA = 4 bytes/pixel

        // Create the texture
        ID3D11Texture2D* pTexture2D = nullptr;
        HRESULT hr = device->CreateTexture2D(&texDesc, &initData, &pTexture2D);
        if (FAILED(hr))
        {
            std::cerr << "[ERROR] CreateTexture2D() failed. HRESULT=0x"
                << std::hex << hr << std::dec << "\n";
            stbi_image_free(data);
            continue;
        }



        // Create shader resource view (SRV) for the texture
        ID3D11ShaderResourceView* pSRV = nullptr;
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = texDesc.Format;
        srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = 1;

        hr = device->CreateShaderResourceView(pTexture2D, &srvDesc, &pSRV);
        // We can release the texture reference; the SRV holds it internally.
        pTexture2D->Release();

        if (FAILED(hr))
        {
            std::cerr << "[ERROR] CreateShaderResourceView() failed. HRESULT=0x"
                << std::hex << hr << std::dec << "\n";
            stbi_image_free(data);
            continue;
        }

        // Free CPU image data
        stbi_image_free(data);

        // Store in our Icon struct
        Icon newIcon;
        newIcon.name = iconInfo.name;        // "globe-solid"
        newIcon.displayName = iconInfo.displayName; // "Open World"
        newIcon.texture = pSRV; // The SRV pointer

        icons.push_back(newIcon);

        std::cout << "[DEBUG] Loaded icon: " << iconInfo.displayName
            << " (" << width << "x" << height << "), SRV=" << pSRV << "\n";
    }

    return true;
}


bool LoadEmbeddedLogoD3D11()
{
    // Quick debug print
    std::cout << "[DEBUG] LoadEmbeddedLogoD3D11() called..." << std::endl;

    ID3D11Device* device = DirectX11Interface::Device;

    if (!device)
    {
        std::cerr << "[ERROR] D3D11 device is NULL." << std::endl;
        return false;
    }

    // If we already have a texture, release it first
    if (GlobalVars::logoTexture)
    {
        GlobalVars::logoTexture->Release();
        GlobalVars::logoTexture = NULL;
    }

    // Validate embedded data
    if (!Logo || Logo_size == 0)
    {
        std::cerr << "[ERROR] Invalid embedded PNG data or size is zero." << std::endl;
        return false;
    }

    // 1. Load the image from memory with stb_image
    int width = 0, height = 0, channels = 0;
    unsigned char* data = stbi_load_from_memory(Logo, Logo_size, &width, &height, &channels, 4);
    if (!data)
    {
        std::cerr << "[ERROR] stbi_load_from_memory() failed to load embedded PNG." << std::endl;
        std::cerr << "[STB] Reason: " << (stbi_failure_reason() ? stbi_failure_reason() : "Unknown") << std::endl;
        return false;
    }

    std::cout << "[DEBUG] Loaded PNG in memory. Width=" << width
        << ", Height=" << height << ", Channels(Forced RGBA)=4." << std::endl;

    // 2. Fill in a D3D11 texture description
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = static_cast<UINT>(width);
    desc.Height = static_cast<UINT>(height);
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // RGBA 8-bit
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;  // No CPU access needed
    desc.MiscFlags = 0;  // No special flags

    // 3. Prepare subresource data
    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;
    initData.SysMemPitch = static_cast<UINT>(width * 4);  // 4 bytes per pixel (RGBA)

    // 4. Create the texture
    ID3D11Texture2D* pTexture2D = nullptr;
    HRESULT hr = device->CreateTexture2D(&desc, &initData, &pTexture2D);
    if (FAILED(hr))
    {
        std::cerr << "[ERROR] CreateTexture2D() failed. HRESULT=" << std::hex << hr << std::dec << std::endl;
        stbi_image_free(data);
        return false;
    }

    // 5. Create the shader resource view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = desc.Format;
    srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = 1;

    hr = device->CreateShaderResourceView(pTexture2D, &srvDesc, &GlobalVars::logoTexture);
    // We can release the texture reference here because SRV will keep it alive internally.
    pTexture2D->Release();

    if (FAILED(hr))
    {
        std::cerr << "[ERROR] CreateShaderResourceView() failed. HRESULT=" << std::hex << hr << std::dec << std::endl;
        stbi_image_free(data);
        return false;
    }

    // 6. Free the image data after the texture is created
    stbi_image_free(data);

    std::cout << "[DEBUG] LoadEmbeddedLogoD3D11() succeeded. logoTexture=" << GlobalVars::logoTexture << std::endl;
    return true;
}


// Helper function to render custom group boxes
void RenderGroupBox(const char* title, ImVec2 size, void (*content)()) {

    ImGui::PushStyleColor(ImGuiCol_ChildBg, COLOR_GROUPBOX); // Top menu & main content background
    ImGui::BeginChild(title, size, true, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::Text(title); // Title for the group box
    ImGui::Separator(); // Separator below title
    if (content) {
        content(); // Render the content inside the group box
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

// Callback functions for group box content
void RenderGroupBox1Content() {
    ImGui::Text("Group Box 1 Content");
}

void RenderGroupBoxPreviewContent() {
    ImGui::BulletText("1st trim.");
    ImGui::BulletText("2nd trim.");
    ImGui::BulletText("3rd trim.");
    ImGui::BulletText("4th trim.");
}

void RenderGroupBox2Content() {
    ImGui::Text("Group Box 2 Content");
}

static float friendlyBoxColor[3] = { 0.0f, 1.0f, 0.0f }; // Green
static float enemyBoxColor[3] = { 1.0f, 0.0f, 0.0f }; // Red
static float weaponBoxColor[3] = { 1.0f, 1.0f, 0.0f }; // Yellow

int ShadowBolt = 0;


typedef int(__fastcall* OriginalFunction)(void* thisPtr, int arg1, float arg2);
OriginalFunction oFunction;

typedef void(__fastcall* PlayerHookFn)(uintptr_t, uintptr_t, uintptr_t);
PlayerHookFn PlayerHookOriginal = nullptr;




void __fastcall PlayerHook(uintptr_t thisptr, uintptr_t a2, uintptr_t a3)
{

    Print("%i", GlobalVars::LocalPlayer->GetHealth());
    
   
    SpoofCall(PlayerHookOriginal, thisptr, a2, a3);
}



void RenderESPTab() {
    static bool showESPPopupFilters = false; // ESP Popup state
    static bool showRadarPopupFilters = false; // Radar Popup state

    // Begin the layout with columns
    ImGui::Columns(2, nullptr, false); // Two columns, no border resizing

    // ESP GroupBox in the first column
    RenderGroupBox("ESP", ImVec2(ImGui::GetColumnWidth() - 16.0f, 400), []() {

        ImGui::Checkbox("Enable ESP", &Setting::ESP::Enabled);

        ImGui::Text("ESP Drawings:");


        ImGui::Checkbox("Names", &Setting::ESP::Names);
        ImGui::Checkbox("Health", &Setting::ESP::Health);
        // ImGui::Checkbox("Power", &espPower);
        ImGui::Checkbox("Level", &Setting::ESP::Lvl);
        ImGui::Checkbox("Race", &Setting::ESP::Race);
        ImGui::Checkbox("Lines", &Setting::ESP::Lines);
        ImGui::Checkbox("DrawBox", &Setting::ESP::DrawBox);

        ImGui::Checkbox("GUID", &Setting::ESP::GuidStr);
        ImGui::Checkbox("Enemy", &Setting::ESP::Enemy);
        ImGui::Checkbox("HostilePlayers", &Setting::ESP::HostilePlayers);
        ImGui::Checkbox("HostileUnits", &Setting::ESP::HostileUnits);
        ImGui::Checkbox("Playerss", &Setting::ESP::Player);
        ImGui::Checkbox("Units", &Setting::ESP::Unit);
        ImGui::Checkbox("Obj", &Setting::ESP::Object);
        ImGui::Checkbox("GameObj", &Setting::ESP::GameObject);
        ImGui::Checkbox("DynObj", &Setting::ESP::DynamicObject);
        ImGui::Checkbox("LocalPlayer", &Setting::ESP::LocalPlayer);
        ImGui::Checkbox("TraceLine", &Setting::ESP::TraceLine);
        // ImGui::Checkbox("WayPoints", &espWaypoints);

        if (ImGui::Button("Save config")) {
            ConfigManager test;
            test.SaveConfig("test");
        }

        if (ImGui::Button("Test flags")) {
            if (GlobalVars::LocalPlayer->IsDead()) { Print("Yes im death"); }
            else { Print("Yes im not death"); }
            if (GlobalVars::LocalPlayer->IsGhost()) { Print("Yes im a ghost"); }
            else { Print("Yes im not a ghost");}

        }


        ////if (ImGui::Button("Test GetSpellIdByName"))
        ////{
        ////    std::cout << std::dec << pSpellBook::GetSpellIdByName(Setting::Menu::SpellName) << std::endl;
        ////}


        /*  if (ImGui::Button("Test Dismount"))
          {
              Funcs::Dismount(GlobalVars::LocalPlayer);
          }*/

        ImGui::InputInt("Spell Id", &Setting::Menu::g1);
        if (ImGui::Button("Setup VMT"))
        {
            VMT_Hook Plhook(nullptr, GlobalVars::LocalPlayer);
            Plhook.SetupHook(&PlayerHookOriginal, PlayerHook, 88);
        }

        if (ImGui::Button("TEST AWE"))
        {
            const char* spellName = "Frostbolt"; // Replace with the spell name you want to test
            int spellId = GameMethods::GetSpellIdByName(spellName);

            if (spellId != -1) {
                Print("Success! Spell ID for %s is %d.\n", spellName, spellId);
            }
            else {
                Print("Failed to retrieve spell ID for %s.\n", spellName);
            }
        }


        if (ImGui::Button("Test pSpellBook findSpellSlot"))
        {
            int32_t spellSlot = pSpellBook::FindSlotBySpellId(133);
            Print("Before %i", spellSlot);
            if (spellSlot < 0)
                return;
            Print("After %i", spellSlot);
        }

      
        if (ImGui::Button("Test Gamemethods::FindSpellSLot"))
        {
            int32_t spellSlot = GameMethods::FindSlotBySpellId(133);
            Print("Before %i", spellSlot);
            if (spellSlot < 0)
                return;
            Print("After %i", spellSlot);
        }


        if (ImGui::Button("CastSpell test"))
        {


            for (auto& [guid, Object] : GlobalVars::Objects)
            {

                if (!Object)
                    continue;

                if (!Object->isValid())
                    continue;

                if (!Object->IsUnit())
                    continue;

                if (strcmp(Object->GetObjectName(), "Blackrock Worg") == 0)
                {

                   // printf("[DISTCHECK] GetMinMaxSpellRange\n");
                   // float_t minstop = 0;
                   // float_t maxstop = 0;
                   //GameMethods::Spell_C_GetMinMaxSpellRange(133, &minstop, &maxstop, Object->GetGuid());
                  //  printf("[DISTCHECK] After GetMinMaxSpellRange %f %f\n", minstop, maxstop);
                    pSpellBook::CastSpell(Object, 133, "Frostbolt");
                }


            }



        }

        //if (ImGui::Button("Test  range value"))
        //{
        //    //std::vector<float> range = GameMethods::SpellMinMaxRange(GameMethods::GetSpellIdByName("Wildfire Bomb"));
        //   // printf("Range of spell %d: Min = %f, Max = %f\n", range[0], range[1]);
        //}


        if (ImGui::Button("Test do we have spellpower"))
        {
            if (!pSpellBook::Spell_C_HaveSpellPower(133)) {
                Print("No mana");
                return;
            }
            else {
                Print("We have mana");
            }
        }
        if (ImGui::Button("Test DoIknowTHisSPell"))
        {
            if (!pSpellBook::IsSpellKnown(133)) {
                Print("Nope");
                return;
            }
            else {
                Print("Yes we know that");
            }
        }
        if (ImGui::Button("Test cooldown Frostbolt"))
        {
            printf("[CASTSPELL] GetSpellDuration\n");
            int64_t duration = 0, startTime = 0, modRate = 1;
            pSpellBook::Spell_C_GetSpellCooldown(133, &duration, &startTime, &modRate);
            int CastDuration = startTime + duration - (int)GameMethods::getCurrentTime();
            //int CastDuration = startTime + duration - (int)GameMethods::getCurrentTime();

            /*auto count = (int)ObjectManager::getCurrentTime();
            auto result = start + duration - count;*/

            Print("duration: %i, startTime: %i, modrate %i, CastDuration: %i", duration, startTime, modRate, CastDuration);

            if (duration > 0 || startTime > 0) {
                return;
            }
        }


        /*  if (ImGui::Button("Test Dismount"))
          {
              Funcs::Dismount(GlobalVars::LocalPlayer);
          }*/

        static char spellInput[64] = "";
        ImGui::InputText("Spell Name##111", spellInput, IM_ARRAYSIZE(spellInput));

        //if (ImGui::Button("Find Spell")) {
        //    const char* spellName = "Fireball";

        //    // Example of dynamically calling SpellBook_FindSpellByName with updated dynamic offset
        //    int64_t spellId = GameMethods::SpellBook_FindSpellByName(spellName);

        //    std::cout << "Spell ID: " << spellId << std::endl;

        //}



        ImGui::InputInt("Spell Ids", &Setting::Menu::g1);
        if (ImGui::Button("Test CastSpellv2"))
        {
            pSpellBook::CastSpell(GlobalVars::LocalPlayer, Setting::Menu::g1, "");
        }
       /* if (ImGui::Button("Test  range value1"))
        {
            std::vector<float> range = GameMethods::SpellMinMaxRange(GameMethods::GetSpellIdByName("Wildfire Bomb"));
            Print("Range of spell: %f", range);
        }*/
        if (ImGui::Button("Can we?"))
        {

          /*  for (auto& [guid, Object] : GlobalVars::Objects)
            {

                if (!Object)
                    continue;

                if (!Object->isValid())
                    continue;

                if (!Object->IsUnit())
                    continue;


                if (Object->GetGuid() != GlobalVars::LocalPlayer->GetGuid()) {

                    float_t min = 0;
                    float_t max = 0;
                    GameMethods::Spell_C_GetMinMaxSpellRange(GameMethods::GetSpellIdByName("Wildfire Bomb"), &min, &max, Object->GetGuid());


                    if (GlobalVars::LocalPlayer->GetUnitPosition().DistanceTo(Object->GetUnitPosition()) >= max)
                    {

                        Print("Cant range: min %f  Range max: %f", min, max);
                        return;
                    }
                    Print("Can reachrange: min %f  Range max: %f", min, max);


                }

            }*/


        }
        





    //if (ImGui::Button(E("TEST_2"))) {
    //    auto quest = GlobalVars::LocalPlayer->GetActiveQuestById(62);
    //    std::cout << Leveling::Objective(62).isGoalComplete(quest) << std::endl;

    //    std::cout << GlobalVars::LocalPlayer->GetPosition().toString() << std::endl;
    //}

        if (ImGui::Button("Try ObjMgr LP")) {
            if (ObjectManager::InGame()) {

                ObjectManager::TestObjectManager();



            }

        }

        if (ImGui::Button("Test2")) {
            if (ObjectManager::InGame()) {

                ObjectManager::Test();


            }

        }

        if (ImGui::Button("Print info")) {
            WObject* localPlayer = GlobalVars::LocalPlayer;
            if (localPlayer && localPlayer->isValid()) {

                std::cout << "[+] LocalPlayer address:" << std::hex << localPlayer << std::endl;

                auto unitPos = localPlayer->GetUnitPosition();      // Assume returns {x, y, z} or similar
                auto namePos = localPlayer->GetObjectNamePosition();

                printf("[+] LocalPlayer address: %p, Character name: %s, Facing: %f, Character lvl: %i\n"
                    "    Unit position vector: %f %f %f, Name Position vector: %f %f %f\n",
                    localPlayer,
                    localPlayer->GetObjectName(),
                    localPlayer->GetFacing(),
                    localPlayer->GetUnitLevel(1),
                    unitPos.x, unitPos.y, unitPos.z,
                    namePos.x, namePos.y, namePos.z);
            }        
        }


        // Add a textbox for user to input their own custom camera value
        ImGui::InputFloat("Custom Camera Value", &customCameraValue);

        // Button to apply custom value
        if (ImGui::Button("Set Custom Camera")) {
            WoW::camera::setfloattest(customCameraValue);
        }

        if (ImGui::Button(E("Dump Backpack")))
        {
            auto items = Utils::GetAllItems();
            for (int i = 0; i < items.size(); ++i) {
                auto item = items[i];
                std::cout << "entity: " << item << " GetItemChacheEntry: " << GameMethods::GetItemCacheEntry(item->GetID()) << " Name: " << item->GetObjectName() << " Price: " << GameMethods::GetItemCacheEntry(item->GetID())->GetSellPrice() << " Quality: " << GameMethods::GetItemCacheEntry(item->GetID())->GetQuality() << std::endl;
            }
            for (int i = 0; i < 16; i++) {
                if (!GlobalVars::LocalPlayer->GetInventory()->GetBackPackSlotByID(i).isEmpty()) {
                    auto g2 = GlobalVars::LocalPlayer->GetInventory()->GetBackPackSlotByID(i);
                    char guidStr[MAX_PATH];
                    GameMethods::GuidToString(&g2, guidStr);

                    /*std::cout << std::dec << g2.i[0]<<", " << g2.i[1] << ", " << g2.i[2] << ", " << g2.i[3] << std::endl;*/
                    auto entity = (WItem*)GlobalVars::Objects[guidStr];
                    std::cout << "entity: " << entity << " GetItemCacheEntry: " << GameMethods::GetItemCacheEntry(entity->GetID()) << std::endl;
                }
            }
        }
    
        // Render all notifications
        ImGui::RenderNotifications();

        // Render ESP Popup
        if (showESPPopupFilters) {
            if (ImGui::BeginPopup("ESPFilterPopup")) {
                ImGui::Text("Filters:");
                ImGui::Checkbox("LocalPlayer", &Setting::ESP::LocalPlayer);
                ImGui::SameLine();
                ImGui::Checkbox("Players", &Setting::ESP::Player);
                ImGui::SameLine();
                ImGui::Checkbox("Npc", &Setting::ESP::Unit);
                ImGui::SameLine();
                ImGui::Checkbox("Corpse", &Setting::ESP::Corpse);

                ImGui::Checkbox("DeadEntitys", &Setting::ESP::DrawDeadEntity);
                ImGui::SameLine();
                ImGui::Text("Hostile filter:");

                if (ImGui::Button("Close")) {
                    ImGui::CloseCurrentPopup();
                    showESPPopupFilters = false;
                }

                ImGui::EndPopup();
            }
        }
        });

    ImGui::NextColumn(); // Move to the next column

    // Radar GroupBox in the second column
    RenderGroupBox("Radar", ImVec2(ImGui::GetColumnWidth() - 20.0f, 400), []() {
        static bool enableRadar = true;
        ImGui::Checkbox("Enable Radarv1", &enableRadar);

        if (ImGui::CustomCheckbox("Enable Radarv2", &enableRadar)) {
            ImGui::Text("Radar state changed: %s", enableRadar ? "Enabled" : "Disabled");
        }

        ImGui::Text("Radar Drawings:");
        static bool radarNames = true, radarLines = true;

        ImGui::Checkbox("Name", &radarNames);
        ImGui::Checkbox("Lines", &radarLines);

        ImGui::Text("Radar Zoom:");
        static float radarZoom = 1.0f;
        ImGui::SliderFloat("##RadarZoom", &radarZoom, 0.1f, 10.0f, "%.1f");

        if (ImGui::CustomSliderFloat("Radar Zoomv2", &radarZoom, 0.1f, 10.0f, "%.1f")) {
            ImGui::Text("Radar Zoom: %.1f", radarZoom);
        }

        ImGui::Text("Icons Scale:");
        static float iconsScale = 4.5f;
        ImGui::SliderFloat("##IconsScale", &iconsScale, 0.1f, 10.0f, "%.1f");

        ImGui::Text("Filters:");
        ImGui::Checkbox("LocalPlayer", &Setting::Radar::LocalPlayer);
        ImGui::SameLine();
        ImGui::Checkbox("Players", &Setting::Radar::Player);
        ImGui::SameLine();
        ImGui::Checkbox("Npc", &Setting::Radar::Unit);
        ImGui::SameLine();
        ImGui::Checkbox("Corpse", &Setting::Radar::Corpse);

        ImGui::Checkbox("Draw name", &Setting::Radar::name);

        ImGui::Checkbox("DeadEntitys", &Setting::Radar::DrawDeadEntity);
        ImGui::Text("Hostile filter:");

        //if (ImGui::Button("Filters")) {
        //    showRadarPopupFilters = true; // Open Radar popup
        //}




        //// Render Radar Popup
        //if (showRadarPopupFilters) {
        //    if (ImGui::BeginPopup("RadarFilterPopup")) {
        //        ImGui::Text("Filters:");
        //        ImGui::Checkbox("LocalPlayer", &Setting::Radar::LocalPlayer);
        //        ImGui::SameLine();
        //        ImGui::Checkbox("Players", &Setting::Radar::Player);
        //        ImGui::SameLine();
        //        ImGui::Checkbox("Npc", &Setting::Radar::Unit);
        //        ImGui::SameLine();
        //        ImGui::Checkbox("Corpse", &Setting::Radar::Corpse);

        //        ImGui::Checkbox("DeadEntitys", &Setting::Radar::DrawDeadEntity);
        //        ImGui::Text("Hostile filter:");

        //        if (ImGui::Button("Close")) {
        //            ImGui::CloseCurrentPopup();
        //            showRadarPopupFilters = false;
        //        }

        //        ImGui::EndPopup();
        //    }
        //}
        });


    ImGui::Columns(1); // End the columns
}

void RenderEntityTab() {
    // Begin the layout with a single column
    ImGui::Columns(1, nullptr, false); // One column, no border resizing

    // ESP GroupBox in the first column
    RenderGroupBox("EntityListViewer", ImVec2(ImGui::GetColumnWidth() - 16.0f, 1200), []() {
        static char search_buffer[256] = "";
        static const char* options[] = {
            "Enumerate Vector3",
            "Enumerate U64",
            "Enumerate Floats",
            "Enumerate ConstChar"
        };
        static int selected_option = 0;
        static WObject* selected_object = nullptr; // Store the selected entity pointer

        // Search input field
        ImGui::InputText("Search", search_buffer, IM_ARRAYSIZE(search_buffer));

        // Dropdown menu for selecting an action
        ImGui::Combo("Select Action", &selected_option, options, IM_ARRAYSIZE(options));

        // Button to execute the selected action
        if (ImGui::Button("Execute Action") && selected_object) {
            // Ensure a valid selected object before calling methods
            switch (selected_option) {
            case 0:
                selected_object->EnumerateVtableVector3();
                break;
            case 1:
                selected_object->EnumerateVtableU64();
                break;
            case 2:
                selected_object->EnumerateVtableFloats();
                break;
            case 3:
                selected_object->EnumerateVtableConstChar();
                break;
            default:
                break;
            }
        }

        ImGui::CustomCheckbox("Players", &Setting::EntityList::Player);
        ImGui::SameLine();
        ImGui::CustomCheckbox("LocalPlayer", &Setting::EntityList::LocalPlayer);
        ImGui::SameLine();
        ImGui::CustomCheckbox("Units", &Setting::EntityList::Unit);
        ImGui::SameLine();
        ImGui::CustomCheckbox("GameObjects", &Setting::EntityList::GameObject);
        ImGui::SameLine();
        ImGui::CustomCheckbox("DynamicObjects", &Setting::EntityList::DynamicObject);
        ImGui::SameLine();
        ImGui::CustomCheckbox("Corpses", &Setting::EntityList::Corpse);

        ImGui::Columns(5);
        ImGui::Separator();

        // Column headers
        ImGui::Text("Type");
        ImGui::NextColumn();
        ImGui::Text("Name");
        ImGui::NextColumn();
        ImGui::Text("Coords");
        ImGui::NextColumn();
        ImGui::Text("Ptr");
        ImGui::NextColumn();
        ImGui::Text("Distance");
        ImGui::NextColumn();

        ImGui::Separator();

        WObject* localplayer = (WObject*)GlobalVars::LocalPlayer;
        if (!localplayer) return;

        // Unordered set to track unique object pointers
        std::unordered_set<uint64_t> displayed_pointers;

        for (auto& [guid, Object] : GlobalVars::Objects) {
            if (!Object || !Object->isValid()) continue;

            // Ensure the object is a valid entity
            if (!Object->IsAnyObj())
                continue;

            // Filtering settings in a clearer order
            if (Object->IsPlayer() && !Setting::EntityList::Player)
                continue;

            if (Object->IsLocalPlayer() && !Setting::EntityList::LocalPlayer)
                continue;

            if (Object->IsUnit() && !Setting::EntityList::Unit)
                continue;

            if (Object->IsGameObject() && !Setting::EntityList::GameObject)
                continue;

            if (Object->IsDynamicObject() && !Setting::EntityList::DynamicObject)
                continue;

            if (Object->IsCorpse() && !Setting::EntityList::Corpse)
                continue;

            // Ensure coordinates are valid
            if (!Utils::ValidCoord(Object))
                continue;

            // Ensure object pointer is not already displayed
            if (displayed_pointers.find(Object->Ptr()) != displayed_pointers.end())
                continue; // Skip this object if its pointer is already displayed

            // Add the object pointer to the set
            displayed_pointers.insert(Object->Ptr());

            // Search filtering
            if (strstr(Object->GetObjectName(), search_buffer) == NULL) continue;

            Setting::EntityList::ObjType = Utils::GetObjType(Object);
            Setting::EntityList::cObjType = Setting::EntityList::ObjType.c_str();

            ImGui::Separator();

            ImGui::PushID(Object->Ptr()); // Ensure unique ID

            if (ImGui::Selectable(Object->GetObjectName(), selected_object == Object, ImGuiSelectableFlags_SpanAllColumns)) {
                selected_object = Object;
            }

            ImGui::SameLine();
            if (ImGui::Button("Copy Ptr")) {
                std::string ptrStr = std::to_string(Object->Ptr());
                ImGui::SetClipboardText(ptrStr.c_str()); // Copy to clipboard
            }

            ImGui::PopID(); // Pop ID to prevent conflicts

            ImGui::NextColumn();
            ImGui::Text("%s", Setting::EntityList::cObjType);
            ImGui::NextColumn();

            ImGui::Text("X:%f Y:%f Z:%f R:%f",
                Object->GetUnitPosition().x, Object->GetUnitPosition().y,
                Object->GetUnitPosition().z, Object->GetFacing());
            ImGui::NextColumn();

            ImGui::Text("%p", Object->Ptr());
            ImGui::NextColumn();

            ImGui::Text("%f", Object->GetUnitPosition().DistanceTo(localplayer->GetUnitPosition()));
            ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::Separator();
        });

    ImGui::Columns(1); // End the columns
}


// Render subcategory content dynamically
void RenderSubcategoryContent(const std::string& subcategory) {
    if (subcategory == "Visuals") {
        RenderESPTab();
    }
    else if (subcategory == "EntityList") {
        RenderEntityTab();
    }
}




void RenderSubcategoryMenu(const std::vector<Icon>& icons) {
    auto it = categorySubcategoryMap.find(activeCategory);
    if (it != categorySubcategoryMap.end()) {
        for (const auto& subcategory : it->second) {
            // Fetch the icon for the subcategory
            std::string iconName = subcategoryIconMap[subcategory]; // Map subcategory to its icon
            auto iconIt = std::find_if(icons.begin(), icons.end(), [&](const Icon& icon) {
                return icon.displayName == iconName;
                });

            ImTextureID icon = NULL; // Default to no icon
            if (iconIt != icons.end()) {
                icon = (ImTextureID)iconIt->texture; // Use the icon texture if found
            }

            // Render the subcategory button
            bool isSelected = (activeSubcategory == subcategory);
            if (ImGui::SideMenu(subcategory.c_str(), isSelected, icon, ImVec2(32, 32))) {
                activeSubcategory = subcategory; // Update the selected subcategory
            }
        }
    }
}




const float sidePadding = 10.0f;       // Padding on the left side
const float rightSidePadding = 10.0f;  // Padding on the right side
void RenderTopMenuButtons(const std::vector<Icon>& icons) {
    static std::vector<std::string> topCategories = { "Open World", "Dungeons", "Gathering", "Quests", "Settings" };
    static std::map<std::string, std::string> categorySubtextMap = {
        { "Open World", "Explore vast lands" },
        { "Dungeons", "Tackle challenging dungeon" },
        { "Gathering", "Collect resources efficiently" },
        { "Quests", "Complete tasks for rewards" },
        { "Settings", "Adjust application settings" }
    };

    static std::string activeTopCategory = topCategories[0]; // Default active category

    // Calculate total available width for the buttons
    float totalWidth = ImGui::GetContentRegionAvail().x - sidePadding - rightSidePadding;
    float buttonSpacing = ImGui::GetStyle().ItemSpacing.x;
    float buttonWidth = (totalWidth - (buttonSpacing * (topCategories.size() - 1))) / topCategories.size();

    for (size_t i = 0; i < topCategories.size(); ++i) {
        const std::string& category = topCategories[i];

        // Get the corresponding icon for the category
        std::string iconName = topCategoryIconMap[category]; // Assuming topCategoryIconMap exists
        auto iconIt = std::find_if(icons.begin(), icons.end(), [&](const Icon& icon) {
            return icon.name == iconName;
            });

        if (iconIt == icons.end()) {
            std::cerr << "Error: Icon not found for category: " << category << std::endl;
            continue;
        }

        ImGui::PushID(i);

        // Determine if this is the first or last button
        bool isFirstButton = (i == 0);
        bool isLastButton = (i == topCategories.size() - 1);

        // Adjust the position of the first button to include left padding
        if (isFirstButton) {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + sidePadding);
        }

        // Adjust the width of the last button to ensure right padding
        float adjustedButtonWidth = buttonWidth;
        if (isLastButton) {
            adjustedButtonWidth = totalWidth - (buttonWidth * (topCategories.size() - 1));
        }

        // Render the button with subtext
        bool isSelected = (activeTopCategory == category);
        const char* subtext = categorySubtextMap.count(category) ? categorySubtextMap[category].c_str() : nullptr;

        if (ImGui::CustomStyledButton(
            category.c_str(),
            (ImTextureID)iconIt->texture,
            ImVec2(16, 16),  // Icon size
            isSelected,
            adjustedButtonWidth,
            subtext,         // Subtext for the button
            isFirstButton,
            isLastButton)) {
            activeTopCategory = category;
            activeCategory = category;
            activeSubcategory = categorySubcategoryMap[category].empty() ? "" : categorySubcategoryMap[category][0];
            std::cout << "Selected Top Category: " << category << std::endl;
        }

        ImGui::PopID();

        // Ensure buttons are rendered inline, no gaps
        if (!isLastButton) {
            ImGui::SameLine(0, 0); // Keep buttons touching each other
        }
    }
}


void RenderMenu(const std::vector<Icon>& icons) {
    // Padding values
    const float sidePadding = 10.0f;       // Padding on the left side
    const float rightSidePadding = 10.0f;  // Padding on the right side

    // Window flags for the main menu
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;

    // Style adjustments
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, COLOR_MAIN_CONTENT);



    if (ImGui::Begin("Menu", nullptr, windowFlags)) {

        ImGui::DrawCustomTitleBar("X-HOOK for World of Warcraft");
        // Get the available content region size
        ImVec2 contentRegion = ImGui::GetContentRegionAvail();
        static float sidebarWidth = 200.0f;
        static float sidebarMinWidth = 150.0f;
        static float sidebarMaxWidth = 300.0f;

        // 1. Render the sidebar with logo and search bar
        ImGui::PushStyleColor(ImGuiCol_ChildBg, COLOR_MAIN_CONTENT);
        ImGui::BeginChild("Sidebar", ImVec2(sidebarWidth, contentRegion.y), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        // Render the logo at the top of the sidebar
        if (GlobalVars::logoTexture) {
            ImVec2 logoSize(210, 56); // Adjust size to fit the sidebar
            ImGui::SetCursorPosX((sidebarWidth - logoSize.x) / 2); // Center the logo horizontally
            ImGui::Image((ImTextureID)GlobalVars::logoTexture, logoSize);
        }
        else {
            ImGui::Text("X-HOOK.XYZ"); // Fallback text if the logo fails to load
        }

        // Add a separator below the logo
        ImGui::Separator();

        // Render the search bar below the logo
        ImGui::PushItemWidth(sidebarWidth);
        static char searchBuffer[128] = "";
        if (ImGui::InputTextWithHint("##search", "Search...", searchBuffer, IM_ARRAYSIZE(searchBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            std::cout << "Search: " << searchBuffer << std::endl;
        }
        ImGui::PopItemWidth();

        // Render subcategories
        RenderSubcategoryMenu(icons);

        // Render footer at the bottom of the sidebar
        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 50.0f); // Position footer at the bottom

        // Center the text by calculating its width and positioning it
        const char* footerText1 = "X-HOOK.XYZ";
        const char* footerText2 = "Version 0.1";
        ImVec2 textSize1 = ImGui::CalcTextSize(footerText1);
        ImVec2 textSize2 = ImGui::CalcTextSize(footerText2);

        ImGui::SetCursorPosX((sidebarWidth - textSize1.x) / 2); // Center first line of text
        ImGui::Text("%s", footerText1);

        ImGui::SetCursorPosX((sidebarWidth - textSize2.x) / 2); // Center second line of text
        ImGui::Text("%s", footerText2);

        ImGui::EndChild();
        ImGui::PopStyleColor();
        // Draw vertical divider between sidebar and main content, starting below the title bar
        ImGui::GetWindowDrawList()->AddLine(
            ImVec2(ImGui::GetWindowPos().x + sidebarWidth, ImGui::GetWindowPos().y + 30.0f), // Start point (30.0f below the top to avoid title bar)
            ImVec2(ImGui::GetWindowPos().x + sidebarWidth, ImGui::GetWindowPos().y + ImGui::GetWindowHeight()),
            ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.3f, 1.0f)), // Divider color
            1.5f // Thickness of the line
        );

        // 2. Render the main content
        ImGui::SameLine();
        ImGui::BeginChild("MainContent", ImVec2(0, contentRegion.y), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, COLOR_MAIN_CONTENT);

        // Render top menu buttons (separate line)
        ImGui::Spacing(); // Add spacing for visual separation
        RenderTopMenuButtons(icons); // Render top menu buttons with subtext

        // Render main content layout below the top menu
        RenderSubcategoryContent(activeSubcategory);

        ImGui::PopStyleColor();
        ImGui::EndChild();
    }

    ImGui::End(); // End of main window
    ImGui::PopStyleColor(); // Pop main window background color
    ImGui::PopStyleVar(4);  // Pop window rounding, padding, and border size
}



