#pragma once

#include "imgui.h"

#include "al/actor/LiveActorKit.h"

#include "game/System/GameSystem.h"
#include "game/System/Application.h"

#include "program/devgui/DevGuiWindowConfig.h"
#include "program/devgui/windows/WindowBase.h"

class WindowMemoryManage : public WindowBase {
public:
    WindowMemoryManage(DevGuiManager* parent, const char* winName, bool active, sead::Heap* heap);

    bool tryUpdateWinDisplay() override;

private:
    float getHeapPercent(sead::Heap* heap);
    void drawProgressBarPerc(float percent, const char* header);
    void drawProgressBarFrac(int current, int max, const char* header);
};