#include "GhostManager.h"
#include "al/util/NerveUtil.h"
#include "devgui/DevGuiManager.h"
#include "game/Player/HackCap.h"
#include "game/Player/PlayerAnimator.h"
#include "helpers/GetHelper.h"
#include "helpers/fsHelper.h"
#include "logger/Logger.hpp"
#include "smo-tas/TAS.h"

namespace {
NERVE_IMPL(GhostManager, Record);
NERVE_IMPL(GhostManager, Wait);
NERVE_IMPL(GhostManager, RecordEnd);
struct {
    NERVE_MAKE(GhostManager, Record);
    NERVE_MAKE(GhostManager, Wait);
    NERVE_MAKE(GhostManager, RecordEnd);
} nrvGhostManager;
}  // namespace

SEAD_SINGLETON_DISPOSER_IMPL(GhostManager);

GhostManager::GhostManager() : al::NerveExecutor("GhostManager") {
    sead::ScopedCurrentHeapSetter heapSetter(DevGuiManager::instance()->getHeap());
    ghosts.allocBuffer(MAX_GHOST_COUNT, DevGuiManager::instance()->getHeap());
    for (int i = 0; i < ghosts.capacity(); i++) {
        ghosts.pushBack(new Ghost());
    }
    initNerve(&nrvGhostManager.Wait, 0);
    nn::fs::CreateDirectory("sd:/smo");
    nn::fs::CreateDirectory("sd:/smo/tas");
    nn::fs::CreateDirectory(REPLAY_SAVEPATH);
    updateDir();
}

GhostManager::~GhostManager() {
    ghosts.freeBuffer();
}

void GhostManager::init(al::ActorInitInfo const& info) {
    int ghostIdx = 0;
    for (auto& ghost : ghosts) {
        if (ghostIdx >= mMaxGhostNum)
            return;
        ghost.init(info);
        ghostIdx++;
    }
}

void GhostManager::updateGhostNerve() {
    if (ghosts.isEmpty())
        return;
    for (int i = 0; i < mMaxGhostNum; i++) {
        if (ghosts.at(i))
            ghosts.at(i)->updateNerve();
    }
}

bool GhostManager::tryStartRecord() {
    sead::ScopedCurrentHeapSetter heapSetter(DevGuiManager::instance()->getHeap());
    auto* tas = TAS::instance();
    if (!tas->hasScript()) {
        return false;
    }
    mReplayPath = sead::FormatFixedSafeString<256>(REPLAY_SAVEPATH "/%s", tas->getScriptName());
    Logger::log("%s\n", mReplayPath.cstr());
    Script* script = tas->getScript();
    mFrameLength = script->mFrames[script->mInputCount - 1].mFrame + 1;
    mFrames = new ReplayFrame[mFrameLength];
    //    static const uint workBufSize = sizeof(ReplayFrame)* mFrameLength;
    //    mWorkBuf = new u8[workBufSize];
    //    sead::Stream::Modes streamMode = sead::Stream::Modes::Binary;
    //    mRamStream = new sead::RamStreamSrc(mWorkBuf, workBufSize);
    //    mWriteStream = new DevGuiWriteStream(mRamStream, streamMode);
    al::setNerve(this, &nrvGhostManager.Record);
    return true;
}

void GhostManager::endRecord() {
    al::setNerve(this, &nrvGhostManager.Wait);
    recordEnd();
}

void GhostManager::recordEnd() {
    sead::ScopedCurrentHeapSetter heapSetter(DevGuiManager::instance()->getHeap());
    mFrameLength = 0;
    mPlayer = nullptr;
    delete[] mFrames;
    //    delete[] mWorkBuf;
    //    delete mRamStream;
    //    delete mWriteStream;
}

void GhostManager::tryStartReplay() {
    sead::ScopedCurrentHeapSetter heapSetter(DevGuiManager::instance()->getHeap());
    endReplay();
    int ghostIdx = 0;
    for (int i = 0; i < mEntryCount; i++) {
        if (!mActiveReplays[i])
            continue;
        nn::fs::DirectoryEntry& curEntry = mEntries[i];
        sead::FormatFixedSafeString<256> scriptPath(REPLAY_SAVEPATH "/%s", curEntry.m_Name);
        nn::fs::FileHandle handle;
        nn::Result r = nn::fs::OpenFile(&handle, scriptPath.cstr(), nn::fs::OpenMode::OpenMode_Read);
        if (R_FAILED(r))
            continue;
        auto* frames = (ReplayFrame*)new u8[curEntry.m_FileSize];
        r = nn::fs::ReadFile(handle, 0, frames, curEntry.m_FileSize);
        nn::fs::CloseFile(handle);
        if (R_FAILED(r)) {
            delete[] frames;
            continue;
        }
        if (!ghosts.at(ghostIdx))
            Logger::log("Current Ghost is null!\n");
        ghosts.at(ghostIdx++)->startReplay(frames, curEntry.m_FileSize / sizeof(ReplayFrame));
    }
}

void GhostManager::endReplay() {
    for (auto& ghost : ghosts) {
        ghost.endReplay();
    }
}

void GhostManager::exeWait() {}

void GhostManager::exeRecord() {
    if (al::isFirstStep(this)) {
        mStep = 0;
    }
    auto tas = TAS::instance();
    if (!tas->isRunning())
        return;
    mPlayer = tryGetPlayerActorHakoniwa(mScene);
    if (!mPlayer)
        return;

    if (tas->getFrameIndex() >= tas->getFrameCount()) {
        al::setNerve(this, &nrvGhostManager.RecordEnd);
        return;
    }

    sead::SafeString pAnim = mPlayer->mPlayerAnimator->curAnim;
    const char* capAnim = al::getActionName(mPlayer->mHackCap);
    mFrames[mStep].playerAnim = PlayerAnims::FindEnum(pAnim.cstr());
    if (capAnim)
        mFrames[mStep].capAnim = PlayerAnims::FindEnum(capAnim);

    for (int i = 0; i < 6; i++)
        mFrames[mStep].blendWeights[i] = mPlayer->mPlayerAnimator->getBlendWeight(i);

    mFrames[mStep].pTrans = al::getTrans(mPlayer);
    mFrames[mStep].pRotation = al::getQuat(mPlayer);
    mFrames[mStep].cTrans = al::getTrans(mPlayer->mHackCap);
    mFrames[mStep].cRotation = al::getQuat(mPlayer->mHackCap);
    mFrames[mStep].cJoint = mPlayer->mHackCap->mJointKeeper->mJointRot;
    mFrames[mStep].cSkew = mPlayer->mHackCap->mJointKeeper->mSkew;
    mFrames[mStep].isCapVisible = !mPlayer->mHackCap->mLiveActorFlag->mIsModelVisible;
    mFrames[mStep].is2D = rs::isPlayer2D(mPlayer);
    //    mFrames[step].isHack = mPlayer->mPlayerHackKeeper->mIsHack;
    mFrames[mStep].isHack = false;
    mStep++;
}

void GhostManager::exeRecordEnd() {
    if (al::isFirstStep(this)) {
        write();
        recordEnd();
    }
    al::setNerve(this, &nrvGhostManager.Wait);
}

void GhostManager::updateDir() {
    sead::ScopedCurrentHeapSetter heapSetter(DevGuiManager::instance()->getHeap());
    nn::fs::DirectoryHandle handle = {};
    nn::Result r = nn::fs::OpenDirectory(&handle, REPLAY_SAVEPATH, nn::fs::OpenDirectoryMode_File);
    if (R_FAILED(r))
        return;
    s64 entryCount = 0;
    r = nn::fs::GetDirectoryEntryCount(&entryCount, handle);
    if (R_FAILED(r)) {
        nn::fs::CloseDirectory(handle);
        return;
    }
    auto* entryBuffer = new nn::fs::DirectoryEntry[entryCount];
    r = nn::fs::ReadDirectory(&entryCount, entryBuffer, handle, entryCount);
    nn::fs::CloseDirectory(handle);
    if (R_FAILED(r)) {
        delete[] entryBuffer;
        return;
    }
    delete[] mEntries;
    delete[] mActiveReplays;
    mEntries = entryBuffer;
    mEntryCount = entryCount;
    mActiveReplays = new bool[entryCount];
}

nn::Result GhostManager::write() {
    return FsHelper::writeFileToPath(mFrames, sizeof(ReplayFrame) * mFrameLength, mReplayPath.cstr());
}

void GhostManager::setNerveRecordEnd() {
    al::setNerve(this, &nrvGhostManager.RecordEnd);
}

bool GhostManager::isRecording() {
    return al::isNerve(this, &nrvGhostManager.Record);
}