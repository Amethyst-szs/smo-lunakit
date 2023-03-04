
/*
    - LunaKit FPS Window -

    This window does not exist in the anchor list, it is a independently placed FPS display
    Does not use categories!
*/

#pragma once

#include "imgui.h"

#include "program/devgui/windows/WindowBase.h"

class WindowFPS : public WindowBase {
public:
    WindowFPS(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);

    bool tryUpdateWinDisplay() override;

    void setupAnchor(int totalAnchoredWindows, int anchorIdx) override;

private:
    static const int mHistorySize = 200;
    float mHistory[mHistorySize] = {};
    int mHistoryOffset = 0;
    
    double mRefreshTime = 0.f;
};