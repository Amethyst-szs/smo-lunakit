#pragma once

#include "al/byaml/ByamlIter.h"
#include "al/byaml/writer/ByamlWriter.h"
#include "al/util.hpp"

#include "helpers/fsHelper.h"

#include "nn/fs/fs_directories.hpp"
#include "nn/fs/fs_files.hpp"
#include "nn/fs/fs_types.hpp"

#include "sead/stream/seadRamWriteStream.h"
#include "sead/stream/seadStream.h"

#include "types.h"

#define SAVEPATH "sd:/LunaKit/LKData/Save/Data.byml"

class DevGuiManager; // Forward declaration (include is in cpp file)

class DevGuiWriteStream : public sead::WriteStream {
public:
    DevGuiWriteStream(sead::RamStreamSrc* src, sead::Stream::Modes mode);
};

class DevGuiSaveData {
public:
    DevGuiSaveData(sead::Heap* heap) { mHeap = heap; }
    void init(DevGuiManager* parent);
    void read();

    bool isSaveQueued() { return mIsQueueSave; }
    float getSaveQueueTime() { return mSaveTimer; }

    bool trySave();
    
    void queueSaveWrite()
    {
        mIsQueueSave = true;
        mSaveTimer = 4.f;
    }

private:
    nn::Result write();
    
    bool mIsQueueSave = false;
    float mSaveTimer = 0.f;

    sead::Heap* mHeap = nullptr;
    DevGuiManager* mParent = nullptr;

    sead::RamStreamSrc* mRamStream = nullptr;
    DevGuiWriteStream* mWriteStream = nullptr;
    u8 mWorkBuf[0x500] = {};
};