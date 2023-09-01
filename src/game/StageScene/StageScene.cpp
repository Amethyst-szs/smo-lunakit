#include "game/StageScene/StageScene.h"
#include <al/util/NerveUtil.h>
#include <al/util/SceneUtil.h>

NERVE_IMPL_INSTANCE_(StageScene, StagePause, StagePause);

void StageScene::exeStagePause() {
    al::updateKitListPostOnNerveEnd(this);
    al::updateNerveState(this);
}