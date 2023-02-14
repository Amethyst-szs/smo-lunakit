#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowFPS.h"

#include "game/System/Application.h"

WindowFPS::WindowFPS(DevGuiManager* parent, const char* winName, sead::Heap* heap)
    : WindowBase(parent, winName, heap)
{
    mConfig.mSize = ImVec2(400, 70);
    mIsAnchorList = false;

    mConfig.mWindowFlags |= ImGuiWindowFlags_NoMove;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoNav;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoDecoration;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoInputs;
}

void WindowFPS::updateWin()
{
    WindowBase::updateWin();
}

bool WindowFPS::tryUpdateWinDisplay()
{
    bool canUpdateDisp = WindowBase::tryUpdateWinDisplay();

    if(!canUpdateDisp)
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
    ImGui::PlotLines("", mHistory, IM_ARRAYSIZE(mHistory), mHistoryOffset, overlay, 0.0f, 60.0f, mConfig.mSize);

    ImGui::End();

    return true;
}

void WindowFPS::configImGuiStyle()
{
    WindowBase::configImGuiStyle();
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