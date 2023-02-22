/*

    This class is used by each window to configure it's position, size, and flags (regardless of anchored or not)
    For more information about different flags go these points in the imgui.h header:

    ImGuiWindowFlags: imgui.h line 953
    ImGuiTabBarFlags: imgui.h line 1093
    ImGuiTabItemFlags: imgui.h line 1109

*/

#pragma once

#include "imgui.h"

struct DevGuiWindowConfig {
    ImGuiWindowFlags mWindowFlags = ImGuiWindowFlags_None;
    ImGuiTabBarFlags mTabFlags = ImGuiTabBarFlags_None;
    ImGuiTabItemFlags mTabItemFlags = ImGuiTabItemFlags_None;

    ImVec2 mTrans = ImVec2(0, 0);
    ImVec2 mSize = ImVec2(100, 100);

    const int mMinimumY = 25;
    const ImVec2 mSizeBase = ImVec2(427, 220);

    const ImVec2 mScrSize = ImVec2(1280, 720);

    float mFontSize = 1.5f;
};