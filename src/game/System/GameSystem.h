#pragma once

#include "GameSystemInfo.h"
#include "al/nerve/NerveExecutor.h"
#include "al/sequence/Sequence.h"

class GameSystem : public al::NerveExecutor {
public:
    void init();

    al::Sequence *mCurSequence; // 0x10
    al::GameSystemInfo *mSystemInfo;  // 0x18
    // 0x78 GameConfigData
};

namespace GameSystemFunction {
    GameSystem *getGameSystem(); // { return Application::instance()->getRootTask()->mSomething; (mSomething = 0x200)
}