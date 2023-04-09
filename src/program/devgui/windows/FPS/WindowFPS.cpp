#include "devgui/DevGuiManager.h"
#include "WindowFPS.h"

#include "game/System/Application.h"

WindowFPS::WindowFPS(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages)
{
    mConfig.mSize = ImVec2(400, 70);

    mConfig.mWindowFlags |= ImGuiWindowFlags_NoBackground;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoNav;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoDecoration;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoInputs;
}

bool WindowFPS::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;

    float curFPS = Application::instance()->mFramework->calcFps();
    
    if (mRefreshTime == 0.0)
        mRefreshTime = ImGui::GetTime();

    while (mRefreshTime < ImGui::GetTime()) {
        mHistory[mHistoryOffset] = curFPS;
        mHistoryOffset = (mHistoryOffset + 1) % IM_ARRAYSIZE(mHistory);
        mRefreshTime += 1.0f / 30.0f;
    }

    char overlay[10];
    sprintf(overlay, "%.00f FPS", curFPS);

    ImVec2 lineSize = mConfig.mSize;
    lineSize.x -= 12;
    lineSize.y -= 10;
    ImGui::PlotLines("", mHistory, IM_ARRAYSIZE(mHistory), mHistoryOffset, overlay, 0.0f, 60.0f, lineSize);

    return true;
}

void WindowFPS::setupAnchor(int totalAnchoredWindows, int anchorIdx)
{
    WinAnchorType type = mParent->getAnchorType();

    // Setup window's position based on the anchor type
    switch(type) {
        case WinAnchorType::ANC_TOP:
            mConfig.mTrans = ImVec2(0, mConfig.mScrSize.y - mConfig.mSize.y);
            break;
        case WinAnchorType::ANC_BOTTOM:
            mConfig.mTrans = ImVec2(0, mConfig.mMinimumY);
            break;
        case WinAnchorType::ANC_LEFT:
            mConfig.mTrans = ImVec2(mConfig.mScrSize.x - mConfig.mSize.x, mConfig.mMinimumY);
            break;
        case WinAnchorType::ANC_RIGHT:
            mConfig.mTrans = ImVec2(0, mConfig.mMinimumY);
            break;
        default:
            break;
    }

    ImGui::SetWindowPos(mConfig.mTrans);
    ImGui::SetWindowSize(mConfig.mSize);
}