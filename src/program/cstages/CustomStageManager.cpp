#include "cstages/CustomStageManager.h"

#include "sead/filedevice/seadFileDeviceMgr.h"

#include "nn/fs/fs_files.hpp"
#include "nn/result.h"

#include "logger/Logger.hpp"

void CustomStageManager::init(sead::Heap* heap)
{
    Logger::log("Starting custom stage plugin loader from %s\n", CUSTOMSTAGEPATH);

    setupDirectoryInfo();

    mStageResources.allocBuffer(mEntryCount, heap);
    for(int i = 0; i < mEntryCount; i++) {
        Logger::log("   Loading custom stage plugin %s\n", getFileName(i));
        
        sead::FormatFixedSafeString<0xff> filePath("%s%s", CUSTOMSTAGEPATH, getFileName(i));

        CustomStageResource* newRes = new (heap) CustomStageResource(filePath.cstr(), getFileName(i), heap);
        mStageResources.pushBack(newRes);
    }

    Logger::log("   Loaded all custom stages - Total %i\n", mEntryCount);
}

void CustomStageManager::setupDirectoryInfo()
{
    nn::fs::DirectoryHandle handle;
    nn::Result r = nn::fs::OpenDirectory(&handle, CUSTOMSTAGEPATH, nn::fs::OpenDirectoryMode_File);
    if (R_FAILED(r)) return;
    s64 entryCount;
    r = nn::fs::GetDirectoryEntryCount(&entryCount, handle);
    if (R_FAILED(r)) {
        nn::fs::CloseDirectory(handle);
        return;
    }
    nn::fs::DirectoryEntry* entryBuffer = new nn::fs::DirectoryEntry[entryCount];
    r = nn::fs::ReadDirectory(&entryCount, entryBuffer, handle, entryCount);
    nn::fs::CloseDirectory(handle);
    if (R_FAILED(r)) {
        delete[] entryBuffer;
        return;
    }
    delete[] mEntries;
    mEntries = entryBuffer;
    mEntryCount = entryCount;
}