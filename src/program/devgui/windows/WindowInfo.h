#pragma once

#include "imgui.h"

#include "program/devgui/DevGuiWindowConfig.h"
#include "program/devgui/windows/WindowBase.h"

#include "program/devgui/categories/CategoryBase.h"
#include "program/devgui/categories/CategoryInfPlayer.h"

class WindowInfo : public WindowBase {
public:
    WindowInfo(DevGuiManager* parent, const char* winName, sead::Heap* heap);

    void updateWin() override;
    bool tryUpdateWinDisplay() override;
};