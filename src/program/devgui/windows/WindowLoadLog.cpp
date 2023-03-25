#include "devgui/windows/WindowLoadLog.h"
#include "devgui/DevGuiManager.h"
#include "logger/LoadLogger.hpp"

WindowLoadLog::WindowLoadLog(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor,
                             int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages) {
    mConfig.mSize = ImVec2(600, 400);
}

namespace LoadLog {
    ImVector<char*> mTextLines;
}

bool WindowLoadLog::tryUpdateWinDisplay() {
    ImGui::SetWindowFontScale(1.0f);
    for (int i = 0; i < LoadLog::mTextLines.size(); i++) {
        char currentLine[256];
        strncpy(currentLine, LoadLog::mTextLines[i], 255);
        ImGui::Text(currentLine);
    }
    if ((ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
        ImGui::SetScrollHereY(1.0f);
    return true;
}

void WindowLoadLog::setupAnchor(int totalAnchoredWindows, int anchorIdx) {
    WinAnchorType type = mParent->getAnchorType();
    // Setup window's position based on the anchor type
    switch (type) {
    case WinAnchorType::ANC_TOP:
        mConfig.mTrans = ImVec2(mConfig.mScrSize.x - mConfig.mSize.x, mConfig.mScrSize.y - mConfig.mSize.y);
        break;
    case WinAnchorType::ANC_BOTTOM:
        mConfig.mTrans = ImVec2(mConfig.mScrSize.x - mConfig.mSize.x, mConfig.mMinimumY);
        break;
    case WinAnchorType::ANC_LEFT:
        mConfig.mTrans = ImVec2(0, mConfig.mMinimumY);
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