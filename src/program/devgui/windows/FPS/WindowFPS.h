
/*
    - LunaKit FPS Window -

    This window does not exist in the anchor list, it is a independently placed FPS display
    Does not use categories!
*/

#pragma once

#include "program/devgui/windows/WindowBase.h"

class WindowFPS : public WindowBase {
public:
    WindowFPS(DevGuiManager* parent, const char* winName, bool isActiveByDefault);

    bool tryUpdateWinDisplay() override;

private:
    static const int mHistorySize = 40;
    float mHistory[mHistorySize] = {};
    int mHistoryOffset = 0;
    
    double mRefreshTime = 0.f;
};