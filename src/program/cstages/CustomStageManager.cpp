#include "cstages/CustomStageManager.h"

void CustomStageManager::init(sead::Heap* heap)
{
    initDirectoryInfo();

    mStageResources.allocBuffer(mEntryCount, heap);
    for(int i = 0; i < mEntryCount; i++) {
        sead::FormatFixedSafeString<0xff> filePath("LunaKitData/CustomStages/%s", getFileName(i));
        filePath.chop(4);

        if (!al::isExistArchive(filePath))
            EXL_ABORT(0x69);

        CustomStageResource* newRes = new (heap) CustomStageResource(filePath.cstr(), getFileName(i));
        mStageResources.pushBack(newRes);
    }
}

void CustomStageManager::initDirectoryInfo()
{
    nn::fs::DirectoryHandle handle;
    nn::Result r = nn::fs::OpenDirectory(&handle, "sd:/LunaKit/LunaKitData/CustomStages/", nn::fs::OpenDirectoryMode_File);
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