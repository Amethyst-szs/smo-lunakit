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
    ImGuiID mDockUp;
    ImGuiID mDockDown;
    ImGuiID mDockLeft;
    ImGuiID mDockRight;

    // Constants
    const ImVec2 mScreenSize = ImVec2(1280.f, 720.f);

    const float mDockSize = 40.f;
};