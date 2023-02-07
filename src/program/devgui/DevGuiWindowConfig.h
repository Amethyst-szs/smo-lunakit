#include "imgui.h"

struct DevGuiWindowConfig {
    ImGuiWindowFlags mWindowFlags = ImGuiWindowFlags_None;
    ImGuiTabBarFlags mTabFlags = ImGuiTabBarFlags_None;
    ImGuiTabItemFlags mTabItemFlags = ImGuiTabItemFlags_None;

    ImVec2 mTrans = ImVec2(0, 0);
    ImVec2 mSize = ImVec2(1280, 720);
    float mFontSize = 1.5f;
};