#include "WindowStagePause.h"
#include "helpers/GetHelper.h"
#include "imgui.h"
#include "stage-pause/StageSceneStateStagePause.h"

WindowStagePause::WindowStagePause(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault) {}

bool WindowStagePause::tryUpdateWinDisplay() {
    if (!WindowBase::tryUpdateWinDisplay())
        return false;

    if (ImGui::Button("Toggle Scene Pause")) {
        mIsStagePaused ? tryUnpauseScene() : tryPauseScene();
        mIsStagePaused = !mIsStagePaused;
    }
    if (ImGui::Button("Advance Frame") && mIsStagePaused) {
        mIsAdvanceFrame = true;
    }
    ImGui::Checkbox("Pause Music?", &mIsPauseAudio);
    return true;
}

void WindowStagePause::updateWin() {
    WindowBase::updateWin();
    tryAdvanceFrame();
}

bool WindowStagePause::tryPauseScene() {
    if (mIsStagePaused)
        return false;

    StageScene* stage = tryGetStageScene();
    if (!stage) {
        mIsStagePaused = false;
        return false;
    }

    if (!stage->getNerveKeeper()) {
        mIsStagePaused = false;
        return false;
    }

    mPreviousNerveKeeper = *stage->getNerveKeeper();
    auto state = stage->getNerveKeeper()->mStateCtrl;
    mPreviousState = state->mCurrentState;
    stage->mStatePause->mIsPauseAudio = mIsPauseAudio;
    stage->mStatePause->mIsPaused = true;
    stage->getNerveKeeper()->mCurrentNerve = &StageSceneNrvStagePause::sInstance;
    state->startState(&StageSceneNrvStagePause::sInstance);

    return true;
}

bool WindowStagePause::tryUnpauseScene() {
    if (!mIsStagePaused)
        return false;

    StageScene* stage = tryGetStageScene();
    if (!stage)
        return false;

    if (!stage->getNerveKeeper())
        return false;
    stage->mStatePause->mIsPaused = false;
    stage->getNerveKeeper()->mStateCtrl->tryEndCurrentState();
    *stage->getNerveKeeper() = mPreviousNerveKeeper;
    stage->getNerveKeeper()->mStateCtrl->mCurrentState = mPreviousState;

    return true;
}

bool WindowStagePause::tryAdvanceFrame() {
    if (mIsAdvanceFrame && !mIsStagePaused) {
        tryPauseScene();
        mIsAdvanceFrame = false;
        mIsStagePaused = true;
    }
    if (mIsAdvanceFrame && mIsStagePaused) {
        tryUnpauseScene();
        mIsStagePaused = false;
    }
    return true;
}