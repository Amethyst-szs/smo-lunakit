#include "WindowLoadLog.h"
#include "devgui/DevGuiManager.h"
#include "logger/LoadLogger.hpp"

WindowLoadLog::WindowLoadLog(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor,
                             int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages) {
    mConfig.mSize = ImVec2(475, 325);
}

namespace LoadLog {
    ImVector<char*> mTextLines;
}

bool WindowLoadLog::tryUpdateWinDisplay() {
    ImGui::SetWindowFontScale(1.0f);

    float lineSize = ImGui::GetTextLineHeightWithSpacing();
    float winHeight = ImGui::GetWindowHeight();
    float curScrollPos = ImGui::GetScrollY();

    ImGui::Dummy(ImVec2(50, calcRoundedNum(curScrollPos - lineSize, lineSize)));

    for (int i = curScrollPos / lineSize; i < (curScrollPos + winHeight) / lineSize; i++) {
        if (i >= LoadLog::mTextLines.size())
            continue;
            
        char currentLine[256];
        strncpy(currentLine, LoadLog::mTextLines[i], 255);
        ImGui::Text(currentLine);
    }

    if ((ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
        ImGui::SetScrollHereY(1.0f);
    else
        ImGui::Dummy(ImVec2(50, calcRoundedNum((LoadLog::mTextLines.size() - (curScrollPos / lineSize + 8)) * lineSize, lineSize)));

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
        mConfig.mTrans = ImVec2(mConfig.mScrSize.x - mConfig.mSize.x, mConfig.mScrSize.y - mConfig.mSize.y);
        break;
    case WinAnchorType::ANC_RIGHT:
        mConfig.mTrans = ImVec2(0, mConfig.mScrSize.y - mConfig.mSize.y);
        break;
    default:
        break;
    }

    ImGui::SetWindowPos(mConfig.mTrans);
    ImGui::SetWindowSize(mConfig.mSize);
}

int WindowLoadLog::calcRoundedNum(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}