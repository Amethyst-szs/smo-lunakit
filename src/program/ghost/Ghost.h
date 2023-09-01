#pragma once

#include "HashedEnum.h"
#include "ReplayFrame.h"
#include "al/nerve/NerveExecutor.h"
#include "al/scene/Scene.h"
#include "al/util/NerveUtil.h"
#include "devgui/savedata/DevGuiWriteStream.h"
#include "fs/fs_types.hpp"
#include "game/Player/PlayerActorHakoniwa.h"
#include "heap/seadHeap.h"
#include "nn/result.h"
#include "stream/seadRamWriteStream.h"

class GhostManager;
class PuppetActor;

class Ghost : public al::NerveExecutor {
public:
    Ghost();
    ~Ghost();
    void init(al::ActorInitInfo const& info);
    void removePuppet();
    void startReplay(ReplayFrame* frames, s32 frameCount);
    void endReplay();
    bool isRunning();
    void exeWait();
    void exePlay();

private:
    ReplayFrame* mFrames = nullptr;
    s32 mFrameCount = 0;
    GhostManager* mParent = nullptr;
    PuppetActor* mPuppet = nullptr;
};

