#pragma once

#include "Ghost.h"
#include "container/seadPtrArray.h"
#include "nn/fs/fs_types.h"
#include "heap/seadDisposer.h"

#define REPLAY_SAVEPATH "sd:/smo/tas/replay"
#define MAX_GHOST_COUNT 8

class GhostManager  : public al::NerveExecutor {
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
    bool* getActiveReplays() { return mActiveReplays; } ;
    int* getMaxGhosts() { return &mMaxGhostNum; };
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
    u32 mFrameLength = 0;
    u8* mWorkBuf = nullptr;
    sead::RamStreamSrc* mRamStream = nullptr;
    DevGuiWriteStream* mWriteStream = nullptr;
    ReplayFrame* mFrames;
};
