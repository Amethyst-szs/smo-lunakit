#pragma once

#include <al/nerve/NerveStateBase.h>

class SceneAudioSystemPauseController;

namespace al {
class Scene;
}

class StageSceneStateStagePause : public al::NerveStateBase {
public:
    al::Scene* mParent;
    bool mIsPaused = false;
    bool mIsPauseAudio = false;
    SceneAudioSystemPauseController* mAudioSystemPauseController;

    StageSceneStateStagePause(const char* stateName, al::Scene* parent, SceneAudioSystemPauseController* audioController);
    ~StageSceneStateStagePause() override {}
    void appear() override;
    void exeWait();
    void kill() override;
};