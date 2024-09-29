#pragma once

#include "HashedEnum.h"
#include "ReplayFrame.h"
#include "Library/Nerve/NerveExecutor.h"
#include "Library/Scene/Scene.h"
#include "al/util/NerveUtil.h"
#include "devgui/savedata/DevGuiWriteStream.h"
#include "nn/fs/fs_types.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "heap/seadHeap.h"
#include "vapours/results.hpp"
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

