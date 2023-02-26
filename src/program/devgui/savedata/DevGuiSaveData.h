
/*
    - LunaKit Custom Save Data Writer/Reader -

    Unlike most other mods that need to preserve data between game sessions, LunaKit stores it's save files
    externally outside of the current switch user's game save. The location of this save data is definied
    below by SAVEPATH

    Expanding the functionality of the saving system is fairly easy, but with some potential issues!
    If you are going to edit this class, please read the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki
*/

#pragma once

#define SAVEPATH "sd:/LunaKit/LKData/data.byml"

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

class DevGuiManager; // Forward declaration (include is in cpp file)

// This class (DevGuiWriteStream) is not the main class! This is a custom implementation of sead::WriteStream
// Which is passed into the al::ByamlWriter to create a buffer which is written to the save file!
class DevGuiWriteStream : public sead::WriteStream {
public:
    DevGuiWriteStream(sead::RamStreamSrc* src, sead::Stream::Modes mode);
};

class DevGuiSaveData {
public:
    DevGuiSaveData(sead::Heap* heap) { mHeap = heap; }
    void init(DevGuiManager* parent);
    void read(); // Read can technically be called at any time, but it only recommended during initalization

    bool trySave(); // Called each frame in the Manager's update() function, checks to see if it should save
    void queueSaveWrite() // Called by any function looking to save LunaKit! Will start a 4 second timer before saving
    {
        mIsQueueSave = true;
        mSaveTimer = 4.f;
    }

    bool isSaveQueued() { return mIsQueueSave; }
    float getSaveQueueTime() { return mSaveTimer; }

private:
    nn::Result write(); // Writes the save data to the SD card
    
    bool mIsQueueSave = false;
    float mSaveTimer = 0.f;

    sead::Heap* mHeap = nullptr;
    DevGuiManager* mParent = nullptr;

    sead::RamStreamSrc* mRamStream = nullptr;
    DevGuiWriteStream* mWriteStream = nullptr;
    u8 mWorkBuf[0x500] = {}; // IMPORTANT - If you are writing a much larger amount of data, may need to expand work buffer size
};