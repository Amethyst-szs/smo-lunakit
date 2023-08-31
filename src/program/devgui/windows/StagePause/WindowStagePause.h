#pragma once

#include <al/nerve/NerveKeeper.h>
#include <al/nerve/NerveStateCtrl.h>
#include <devgui/windows/WindowBase.h>

__attribute__((used)) static const char* stagePauseWindowName = "Stage Pauser";

class WindowStagePause : public WindowBase {
private:
    bool mIsStagePaused = false;
    bool mIsPauseAudio = false;
    bool mIsAdvanceFrame = false;
    al::NerveKeeper mPreviousNerveKeeper;
    al::State* mPreviousState = nullptr;

public:
    WindowStagePause(DevGuiManager* parent, const char* winName, bool isActiveByDefault);
    bool tryUpdateWinDisplay() override;
    void updateWin() override;
    bool tryAdvanceFrame();
    bool tryPauseScene();
    bool tryUnpauseScene();
};
