#pragma once

#include "imgui.h"
#include "imgui_internal.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class DevGuiDocking {
public:
    DevGuiDocking(DevGuiManager* parent);

    void update();

    ImGuiID getDockPoint(ImGuiDir direction);
    ImGuiDir getDockDirection(ImGuiID id); // Will return ImGuiDir_None if id is not in the DockSpace

private:
    DevGuiManager* mParent = nullptr;
    bool mIsFirstStep = true;

    // Dock points
    ImGuiID mDockSpace;
    ImGuiID mDockUp;
    ImGuiID mDockDown;
    ImGuiID mDockLeft;
    ImGuiID mDockRight;

    // Constants
    const ImVec2 mScreenSize = ImVec2(1280.f, 720.f + 2.f); // This just fixes some weird pixels on the bottom
};