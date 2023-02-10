#pragma once

#include "imgui.h"

#include "program/devgui/DevGuiWindowConfig.h"
#include "program/devgui/windows/WindowBase.h"

#include "program/devgui/categories/CategoryBase.h"

class WindowFPS : public WindowBase {
public:
    WindowFPS(const char* winName, sead::Heap* heap);

    void updateWin() override;
    void updateWinDisplay() override;
    void configImGuiStyle() override;

private:
    const int mWindowWidth = 400;

    static const int mHistorySize = 200;
    float mHistory[mHistorySize] = {};
    int mHistoryOffset = 0;
    
    double mRefreshTime = 0.f;
};