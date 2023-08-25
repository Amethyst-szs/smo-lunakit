#pragma once

#include "program/devgui/windows/WindowBase.h"
#include "program/devgui/categories/CategoryBase.h"

__attribute__((used)) static const char* tasWindowName = "TAS";

class WindowTAS : public WindowBase {
public:
    WindowTAS(DevGuiManager* parent, const char* winName, bool isActiveByDefault);

//    void updateWin() override;
    bool tryUpdateWinDisplay() override;
private:
    bool isStartTAS = false;
    bool isStartRecord = false;
    bool isStartReplay = false;
};
