#include "program/devgui/windows/DevGuiWindowBase.h"
#include "program/devgui/categories/DevGuiCategoryBase.h"

#include "types.h"

DevGuiWindowBase::DevGuiWindowBase(const char* winName, sead::Heap* heap)
{
    // Preare PtrArray
    mCategories.allocBuffer(0x10, heap);

    // Set members from parameters
    mWinName = winName;
    mDevGuiHeap = heap;
}

void DevGuiWindowBase::updateWin()
{
    if(mCategories.size() > 0) {
        for(int i = 0; i < mCategories.size(); i++) {
            auto* entry = mCategories.at(i);
            entry->updateCat();
        }
    }
}

void DevGuiWindowBase::updateWinDisplay()
{
    ImGui::Begin(mWinName, NULL, mConfig.mWindowFlags);

    configImGuiStyle();
    ImGui::SetWindowPos(mConfig.mTrans, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize(mConfig.mSize, ImGuiCond_FirstUseEver);
    ImGui::SetWindowFontScale(mConfig.mFontSize);

    // If this window contains categories, load in the tabs
    if(mCategories.size() > 0) {
        if (ImGui::BeginTabBar("Categories", mConfig.mTabFlags)) {

            for(int i = 0; i < mCategories.size(); i++) {
                auto* entry = mCategories.at(i);

                if (ImGui::BeginTabItem(entry->getCategoryName(), NULL, mConfig.mTabItemFlags)) {
                    entry->updateCatDisplay();
                    ImGui::EndTabItem();
                }

            }

            ImGui::EndTabBar();
        }
    }

    ImGui::End();
}

void DevGuiWindowBase::configImGuiStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();
    
    style.Alpha = 1.0f;
    style.WindowRounding = 7.0f;
    style.FrameRounding = 5.0f;
    style.ScrollbarSize = 18.f;
    style.ScrollbarRounding = 15.f;
    style.GrabRounding = 15.f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.MouseCursorScale = 1.2f;

    // style.Colors[ImGuiCol_Text]                  = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    // style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    // style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.99f, 0.99f, 0.99f, 0.99f);
    // style.Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    // style.Colors[ImGuiCol_Border]                = ImVec4(1.00f, 0.96f, 0.98f, 0.99f);
    // style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.80f, 0.76f, 0.78f, 0.59f);
    // style.Colors[ImGuiCol_PopupBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    // style.Colors[ImGuiCol_FrameBg]               = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    // style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
    // style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    // style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.96f, 0.9f, 0.92f, 1.00f);
    // style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(1.00f, 0.96f, 0.98f, 0.51f);
    // style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.82f, 0.76f, 0.78f, 1.00f);
    // style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.99f, 0.92f, 0.96f, 1.00f);
    // style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
    // style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
    // style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
    // style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
    // style.Colors[ImGuiCol_CheckMark]             = ImVec4(1.f, .3f, .3f, 1.00f);
    // style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.79f, 0.44f, 0.68f, 0.75f);
    // style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(1.f, .3f, .3f, 1.00f);
    // style.Colors[ImGuiCol_Button]                = ImVec4(0.79f, 0.44f, 0.68f, 0.50f);
    // style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.79f, 0.44f, 0.68f, 0.9f);
    // style.Colors[ImGuiCol_ButtonActive]          = ImVec4(1.f, .3f, .3f, 1.00f);
    // style.Colors[ImGuiCol_Header]                = ImVec4(0.79f, 0.44f, 0.68f, 0.61f);
    // style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.79f, 0.44f, 0.68f, 0.90f);
    // style.Colors[ImGuiCol_HeaderActive]          = ImVec4(1.f, .3f, .3f, 1.00f);
    // style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
    // style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.79f, 0.44f, 0.68f, 0.67f);
    // style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(1.f, .3f, .3f, 0.95f);
    // style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.85f, 0.70f, 0.78f, 1.00f);
    // style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    // style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    // style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    // style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
}