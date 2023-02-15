#pragma once

#include "lib.hpp"

#include "al/byaml/ByamlIter.h"
#include "al/resource/Resource.h"
#include "al/util.hpp"

#include "nn/fs/fs_directories.hpp"
#include "nn/fs/fs_files.hpp"
#include "nn/result.h"

#include "sead/heap/seadExpHeap.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadHeapMgr.h"
#include "sead/filedevice/seadFileDeviceMgr.h"

#include "types.h"

#include "CustomStage.h"

class CustomStageManager {
public:
    CustomStageManager() {};

    void init(sead::Heap* heap);
    void initDirectoryInfo();


    sead::PtrArray<CustomStageEntry>* getEntries(int resIdx, int catIdx) { return &mStageResources.at(resIdx)->mCategories.at(catIdx)->mEntries; }
    CustomStageEntry* getEntry(int resIdx, int catIdx, int entIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->mEntries.at(entIdx); }
    const char* getEntryName(int resIdx, int catIdx, int entIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->mEntries.at(entIdx)->getName(); }
    bool getEntryValid(int resIdx, int catIdx, int entIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->mEntries.at(entIdx)->isStageExist(); }

    sead::PtrArray<CustomStageCategory>* getCategories(int resIdx) { return &mStageResources.at(resIdx)->mCategories; }
    CustomStageCategory* getCategory(int resIdx, int catIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx); }
    const char* getCategoryName(int resIdx, int catIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->getCatName(); }
    const char* getCategoryDesc(int resIdx, int catIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->getCatDesc(); }
    int getCategorySize(int resIdx, int catIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->getCatSize(); }

    sead::PtrArray<CustomStageResource>* getResources() { return &mStageResources; }
    CustomStageResource* getResource(int idx) { return mStageResources.at(idx); }
    const char* getResourceName(int idx) { return mStageResources.at(idx)->getResourceName(); }
    int getResourceCount() { return mStageResources.size(); }

    nn::fs::DirectoryEntry getFile(int idx) const { return mEntries[idx]; }
    const char* getFileName(int idx) const { return mEntries[idx].m_Name; }
    s64 getFileCount() const { return mEntryCount; }

private:
    s64 mEntryCount = -1;
    nn::fs::DirectoryEntry* mEntries = nullptr;

    sead::PtrArray<CustomStageResource> mStageResources;
};