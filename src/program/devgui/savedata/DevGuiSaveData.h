
/*
    - LunaKit Custom Save Data Writer/Reader -

    Unlike most other mods that need to preserve data between game sessions, LunaKit stores it's save files
    externally outside of the current switch user's game save. The location of this save data is definied
    below by SAVEPATH

    Expanding the functionality of the saving system is fairly easy, but with some potential issues!
    If you are going to edit this class, please read the wiki!
    https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#save-data
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

#include "types.h"

#include "update/UpdateHandler.h"

#include "devgui/windows/ActorBrowse/WindowActorBrowse.h"

#include "DevGuiWriteStream.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

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

    void setActorBrowserFavoriteAtIdx(sead::FixedSafeString<0x40> name, int idx) { mActorBrowserFavorites[idx] = name; }
    sead::FixedSafeString<0x40> getActorBrowserFavoriteAtIdx(int idx) { return mActorBrowserFavorites[idx]; }

    bool isSaveQueued() { return mIsQueueSave; }
    float getSaveQueueTime() { return mSaveTimer; }

private:
    nn::Result write(); // Writes the save data to the SD card
    
    bool mIsQueueSave = false;
    float mSaveTimer = 0.f;

    sead::Heap* mHeap = nullptr;
    DevGuiManager* mParent = nullptr;

    sead::FixedSafeString<0x40> mActorBrowserFavorites[MAXFAVS];

    sead::RamStreamSrc* mRamStream = nullptr;
    DevGuiWriteStream* mWriteStream = nullptr;
    static const uint mWorkBufSize = 0x1000;
    u8 mWorkBuf[mWorkBufSize] = {}; // IMPORTANT - If you are writing a much larger amount of data, may need to expand work buffer size
};