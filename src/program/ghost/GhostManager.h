#pragma once

#include "Ghost.h"
#include "container/seadPtrArray.h"
#include "fs/fs_types.hpp"
#include "heap/seadDisposer.h"

#define REPLAY_SAVEPATH "sd:/smo/tas/replay"
#define MAX_GHOST_COUNT 4

class GhostManager : public al::NerveExecutor {
    SEAD_SINGLETON_DISPOSER(GhostManager);
    GhostManager();
    ~GhostManager();

public:
    void init(al::ActorInitInfo const& info);
    void exeWait();
    void exeRecord();
    void exeRecordEnd();
    void updateGhostNerve();
    void setScene(al::Scene* scene) { mScene = scene; };
    bool tryStartRecord();
    void endRecord();
    void recordEnd();
    void tryStartReplay();
    void endReplay();
    void updateDir();
    void setNerveRecordEnd();
    bool isRecording();
    bool* getActiveReplays() { return mActiveReplays; };
    int* getMaxGhosts() { return &mMaxGhostNum; };
    Ghost* getGhost(int idx) { return ghosts.at(idx); }
    nn::fs::DirectoryEntry* getReplays() const { return mEntries; };
    s64 getEntryCount() const { return mEntryCount; };
    void setMaxGhosts(int max) { mMaxGhostNum = max; };

private:
    nn::Result write();
    s64 mEntryCount;
    nn::fs::DirectoryEntry* mEntries = nullptr;
    bool* mActiveReplays = nullptr;
    int mMaxGhostNum = 1;
    sead::PtrArray<Ghost> ghosts;
    al::Scene* mScene = nullptr;
    PlayerActorHakoniwa* mPlayer = nullptr;
    sead::FixedSafeString<256> mReplayPath;
    int mStep = 0;
    u32 mFrameLength = 0;
    ReplayFrame* mFrames;
};