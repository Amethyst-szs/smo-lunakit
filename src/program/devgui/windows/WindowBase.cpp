#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowBase.h"
#include "devgui/categories/CategoryBase.h"

#include "types.h"

WindowBase::WindowBase(DevGuiManager* parent, const char* winName, sead::Heap* heap)
{
    // Preare PtrArray
    mCategories.allocBuffer(0x10, heap);

    // Set members from parameters
    mWinName = winName;
    mParent = parent;
    mDevGuiHeap = heap;

    // Default position and size settings
    mConfig.mTrans = ImVec2(0, 19);
    mConfig.mSize = ImVec2(427, 220);
    
    // Window flags
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
}

void WindowBase::updateWin()
{
    if(!mIsCloseUnpressed) {
        mIsCloseUnpressed = true;
        mIsActive = false;
        mParent->refreshAnchor();
    }

    if(!mIsActive)
        return;
        
    if (mCategories.size() > 0) {
        for (int i = 0; i < mCategories.size(); i++) {
            auto* entry = mCategories.at(i);
            entry->updateCat();
        }
    }
}

bool WindowBase::tryUpdateWinDisplay()
{
    configImGuiStyle();

    // If this window contains categories, load in the tabs
    if (mCategories.size() > 0) {
        if (ImGui::BeginTabBar("Categories", mConfig.mTabFlags)) {

            for (int i = 0; i < mCategories.size(); i++) {
                auto* entry = mCategories.at(i);

                if (ImGui::BeginTabItem(entry->getCategoryName(), NULL, mConfig.mTabItemFlags)) {
                    entry->updateCatDisplay();
                    ImGui::EndTabItem();
                }
            }

            ImGui::EndTabBar();
        }
        
        ImGui::End();
    }

    return true;
}

void WindowBase::configImGuiStyle()
{
    ImGui::SetWindowFontScale(mConfig.mFontSize);

    // Color pallete
    ImVec4 PurpleDark = ImVec4(0.088f, 0.002f, 0.193f, 1.000f);
    ImVec4 PurpleMid = ImVec4(0.334f, 0.069f, 0.540f, 1.000f);
    ImVec4 PurpleLight = ImVec4(0.494f, 0.286f, 0.600f, 1.000f);
    ImVec4 YellowDark = ImVec4(0.639f, 0.374f, 0.002f, 0.930f);
    ImVec4 YellowLight = ImVec4(0.733f, 0.539f, 0.000f, 0.850f);

    ImGuiStyle& style = ImGui::GetStyle();

    style.Alpha = 1.f;

    style.WindowPadding = ImVec2(5, 5);
    style.WindowBorderSize = 0.f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

    style.ChildRounding = 5.f;
    style.ChildBorderSize = 1.f;

    style.PopupRounding = 5.f;
    style.PopupBorderSize = 1.f;

    style.FrameRounding = 5.f;
    style.FrameBorderSize = 1.f;

    style.ScrollbarSize = 10.f;
    style.ScrollbarRounding = 5.f;

    style.GrabMinSize = 15.f;
    style.GrabRounding = 5.f;

    style.TabRounding = 5.f;
    style.TabBorderSize = 1.f;

    style.Colors[ImGuiCol_Text]              = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    style.Colors[ImGuiCol_TextDisabled]      = ImVec4(0.794f, 0.586f, 0.900f, 0.850f);
    style.Colors[ImGuiCol_WindowBg]          = ImVec4(0.010f, 0.000f, 0.010f, 0.970f);
    style.Colors[ImGuiCol_ChildBg]           = ImVec4(0.010f, 0.000f, 0.010f, 0.930f);
    style.Colors[ImGuiCol_PopupBg]           = ImVec4(0.010f, 0.000f, 0.010f, 1.000f);
    style.Colors[ImGuiCol_Border]            = PurpleLight;
    style.Colors[ImGuiCol_BorderShadow]      = PurpleMid;
    style.Colors[ImGuiCol_FrameBg]           = PurpleDark;
    style.Colors[ImGuiCol_FrameBgHovered]    = PurpleMid;
    style.Colors[ImGuiCol_FrameBgActive]     = PurpleLight;
    style.Colors[ImGuiCol_TitleBg]           = PurpleDark;
    style.Colors[ImGuiCol_TitleBgActive]     = PurpleMid;
    style.Colors[ImGuiCol_TitleBgCollapsed]  = ImVec4(0.000f, 0.000f, 0.000f, 0.150f);
    style.Colors[ImGuiCol_MenuBarBg]         = PurpleDark;
    style.Colors[ImGuiCol_ScrollbarBg]       = PurpleDark;
    style.Colors[ImGuiCol_ScrollbarGrab]     = PurpleMid;
    style.Colors[ImGuiCol_ScrollbarGrabHovered]= YellowDark;
    style.Colors[ImGuiCol_ScrollbarGrabActive]= YellowLight;
    style.Colors[ImGuiCol_CheckMark]         = YellowLight;
    style.Colors[ImGuiCol_SliderGrab]        = PurpleLight;
    style.Colors[ImGuiCol_SliderGrabActive]  = YellowLight;
    style.Colors[ImGuiCol_Button]            = PurpleMid;
    style.Colors[ImGuiCol_ButtonHovered]     = YellowDark;
    style.Colors[ImGuiCol_ButtonActive]      = YellowLight;
    style.Colors[ImGuiCol_Header]            = PurpleDark;
    style.Colors[ImGuiCol_HeaderHovered]     = PurpleMid;
    style.Colors[ImGuiCol_HeaderActive]      = YellowLight;
    style.Colors[ImGuiCol_Separator]         = PurpleMid;
    style.Colors[ImGuiCol_SeparatorHovered]  = PurpleLight;
    style.Colors[ImGuiCol_SeparatorActive]   = YellowLight;
    style.Colors[ImGuiCol_ResizeGrip]        = PurpleMid;
    style.Colors[ImGuiCol_ResizeGripHovered] = YellowDark;
    style.Colors[ImGuiCol_ResizeGripActive]  = YellowLight;
    style.Colors[ImGuiCol_Tab]               = PurpleDark;
    style.Colors[ImGuiCol_TabHovered]        = YellowDark;
    style.Colors[ImGuiCol_TabActive]         = PurpleMid;
    style.Colors[ImGuiCol_TabUnfocused]      = PurpleDark;
    style.Colors[ImGuiCol_TabUnfocusedActive]= PurpleLight;
    style.Colors[ImGuiCol_PlotLines]         = YellowDark;
    style.Colors[ImGuiCol_PlotLinesHovered]  = YellowLight;
    style.Colors[ImGuiCol_PlotHistogram]     = YellowLight;
    style.Colors[ImGuiCol_PlotHistogramHovered]= YellowLight;
}

void WindowBase::setupAnchor(int totalAnchoredWindows, int anchorIdx)
{
    if(totalAnchoredWindows == 0)
        return; // This should never happen, but check just in case to avoid dividing by zero

    WinAnchorType type = mParent->getAnchorType();
    DevGuiWindowConfig* c = &mConfig;

    // Setup window's position based on the anchor type
    switch(type) {
        case WinAnchorType::ANC_TOP:
            c->mTrans = ImVec2(c->mScrSize.x / totalAnchoredWindows * anchorIdx, c->mMinimumY);
            c->mSize = ImVec2(c->mScrSize.x / totalAnchoredWindows, c->mSizeBase.y);
            break;
        case WinAnchorType::ANC_BOTTOM:
            c->mTrans = ImVec2(c->mScrSize.x / totalAnchoredWindows * anchorIdx, c->mScrSize.y - c->mSizeBase.y);
            c->mSize = ImVec2(c->mScrSize.x / totalAnchoredWindows, c->mSizeBase.y);
            break;
        case WinAnchorType::ANC_LEFT:
            c->mTrans = ImVec2(0, (c->mScrSize.y / totalAnchoredWindows * anchorIdx) + c->mMinimumY);
            c->mSize = ImVec2(c->mSizeBase.x, c->mScrSize.y / totalAnchoredWindows);
            break;
        case WinAnchorType::ANC_RIGHT:
            c->mTrans = ImVec2(c->mScrSize.x - c->mSizeBase.x, (c->mScrSize.y / totalAnchoredWindows * anchorIdx) + c->mMinimumY);
            c->mSize = ImVec2(c->mSizeBase.x, c->mScrSize.y / totalAnchoredWindows);
            break;
        default:
            mConfig.mTrans = ImVec2(0, 0);
            mConfig.mSize = ImVec2(1280, 720);
            break;
    }

    c->mSize.x += 1;

    ImGui::SetWindowPos(mConfig.mTrans);
    ImGui::SetWindowSize(mConfig.mSize);
}