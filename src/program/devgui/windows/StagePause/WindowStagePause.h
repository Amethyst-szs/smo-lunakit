#pragma once

#include <Library/Nerve/NerveKeeper.h>
#include <Library/Nerve/NerveStateCtrl.h>
#include <devgui/windows/WindowBase.h>

__attribute__((used)) static const char* stagePauseWindowName = "Stage Pauser";

class WindowStagePause : public WindowBase {
private:
    bool mIsStagePaused = false;
    bool mIsPauseAudio = false;
    bool mIsAdvanceFrame = false;
    al::NerveKeeper mPreviousNerveKeeper = {nullptr, nullptr, 0};
    al::NerveStateCtrl::State* mPreviousState = nullptr;

public:
    WindowStagePause(DevGuiManager* parent, const char* winName, bool isActiveByDefault);
    bool tryUpdateWinDisplay() override;
    void updateWin() override;
    bool tryAdvanceFrame();
    bool tryPauseScene();
    bool tryUnpauseScene();
};
