
/*
    - LunaKit DockSpace -

    LunaKit uses the docking branch of ImGui and this class serves to initalize the DockSpace
    This allows placing windows on the edges of the screens like the original anchoring system in older versions of LunaKit

    Check the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation
*/

#pragma once

#include "imgui.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class DevGuiDocking {
public:
    DevGuiDocking(DevGuiManager* parent);

    void update();

private:
    DevGuiManager* mParent = nullptr;
    bool mIsFirstStep = true;

    // Dock points
    ImGuiID mDockSpace;

    ImGuiID mDockUp;
    ImGuiID mDockDown;
    ImGuiID mDockLeft;
    ImGuiID mDockRight;

    ImVec2 mScreenSize = ImVec2(1280.f, 720.f + 3.f); // This just fixes some weird pixels on the bottom
};