#include "StageSceneStateStagePause.h"
#include <al/effect/EffectSystem.h>
#include <al/graphics/GraphicsFunction.h>
#include <al/util/ControllerUtil.h>
#include <al/util/GraphicsUtil.h>
#include <al/util/NerveUtil.h>
#include "al/actor/LiveActorKit.h"
#include "game/StageScene/SceneAudioSystemPauseController.h"

namespace ScenePlayerFunction {
void startSnapShotMode(const al::Scene*);
void endSnapShotMode(const al::Scene*);
void updatePlayerDither(const al::Scene*);
}  // namespace ScenePlayerFunction

namespace rs {
void updateKitListPostSnapShot(al::Scene*);
}

namespace {
NERVE_IMPL(StageSceneStateStagePause, Wait);
struct {
    NERVE_MAKE(StageSceneStateStagePause, Wait);
} nrvStageSceneStateStagePause;
}  // namespace

StageSceneStateStagePause::StageSceneStateStagePause(const char* stateName, al::Scene* parent, SceneAudioSystemPauseController* audioController)
    : NerveStateBase(stateName) {
    initNerve(&nrvStageSceneStateStagePause.Wait, 0);
    mParent = parent;
    mAudioSystemPauseController = audioController;
}

void StageSceneStateStagePause::appear() {
    mIsDead = false;
    al::setNerve(this, &nrvStageSceneStateStagePause.Wait);
}

void StageSceneStateStagePause::kill() {
    mIsDead = true;
}

void StageSceneStateStagePause::exeWait() {
    if (al::isFirstStep(this)) {
        al::pausePadRumble(mParent);
        if (mIsPauseAudio)
            mAudioSystemPauseController->pause(false);
        alGraphicsFunction::setRainUpdateFlag(mParent, false);
        alGraphicsFunction::setFogNoiseUpdateFlag(mParent, false);
    }

    mParent->getLiveActorKit()->getEffectSystem()->setIsUpdateKit(true);
    al::updateKitListPrev(mParent);
    //    al::updateKitList(mParent, "カメラ");                // camera
    al::updateKitList(mParent, "クリッピング");          // clipping
    al::updateKitTable(mParent, "スナップショット");     // snap shot
    al::updateKitList(mParent, "シャドウマスク");        // shadow mask
    al::updateKitList(mParent, "グラフィックス要求者");  // graphics requester
    al::updateKitList(mParent, "２Ｄ（ポーズ無視）");    // 2D (ignore pose)
    ScenePlayerFunction::updatePlayerDither(mParent);
    rs::updateKitListPostSnapShot(mParent);
    mParent->getLiveActorKit()->getEffectSystem()->setIsUpdateKit(false);

    if (mIsPaused)
        return;

    al::endPausePadRumble(mParent);
    mAudioSystemPauseController->resume(1);
    alGraphicsFunction::setRainUpdateFlag(mParent, true);
    alGraphicsFunction::setFogNoiseUpdateFlag(mParent, true);

    kill();
}
