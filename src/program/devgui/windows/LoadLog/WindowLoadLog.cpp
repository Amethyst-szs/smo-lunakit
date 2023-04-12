#include "WindowLoadLog.h"
#include "devgui/DevGuiManager.h"

#include "logger/LoadLogger.hpp"

#include "imgui.h"

WindowLoadLog::WindowLoadLog(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault) {}

bool WindowLoadLog::tryUpdateWinDisplay() {
    ResourceLoadLogger& log = *ResourceLoadLogger::instance();

    ImGui::SetWindowFontScale(1.0f);

    float lineSize = ImGui::GetTextLineHeightWithSpacing();
    float winHeight = ImGui::GetWindowHeight();
    float curScrollPos = ImGui::GetScrollY();

    if (ImGui::GetScrollY() > 1.f)
        ImGui::Dummy(ImVec2(50, calcRoundedNum(curScrollPos - lineSize, lineSize)));

    for (int i = curScrollPos / lineSize; i < (curScrollPos + winHeight) / lineSize; i++) {
        if (i >= log.mTextLines.size())
            continue;
            
        ImGui::Text(log.mTextLines[i]->cstr());
    }

    if (ImGui::GetScrollY() <= 1.f)
        ImGui::SetScrollY(0.f);

    ImGui::Dummy(ImVec2(50, calcRoundedNum((log.mTextLines.size() - (curScrollPos / lineSize + 8)) * lineSize, lineSize)));

    return true;
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