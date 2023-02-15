#pragma once

#include "al/byaml/ByamlIter.h"
#include "al/resource/Resource.h"
#include "al/util.hpp"

#include "sead/heap/seadExpHeap.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadHeapMgr.h"
#include "sead/filedevice/seadFileDeviceMgr.h"

#include "types.h"

class CustomStageEntry {
public:
    CustomStageEntry(const char* stageName);

    const char* getName() { return mStageName; }
    bool isStageExist() { return mIsExist; }

private:
    const char* mStageName = nullptr;
    bool mIsExist = false;
};

class CustomStageCategory {
public:
    CustomStageCategory(al::ByamlIter catIter);

    const char* getCatName() { return mCatName; }
    const char* getCatDesc() { return mCatDesc; }
    uint getCatSize() { return mCatSize; }

    sead::PtrArray<CustomStageEntry>* getEntries() { return &mEntries; }
    CustomStageEntry* getEntry(int entIdx) { return mEntries.at(entIdx); }
    const char* getEntryName(int entIdx) { return mEntries.at(entIdx)->getName(); }
    bool getEntryValid(int entIdx) { return mEntries.at(entIdx)->isStageExist(); }

    sead::PtrArray<CustomStageEntry> mEntries;

private:
    al::ByamlIter mIter;
    uint mCatSize = -1;
    const char* mCatName = "null";
    const char* mCatDesc = "null";
};

class CustomStageResource {
public:
    CustomStageResource(const char* resourcePath, const char* resourceName);

    bool isValid() { return mIsValidResource; }
    const char* getResourceName() { return mResourceName; }
    int getResourceSize() { return mCategories.size(); }

    sead::PtrArray<CustomStageEntry>* getEntries(int catIdx) { return &mCategories.at(catIdx)->mEntries; }
    CustomStageEntry* getEntry(int catIdx, int entIdx) { return mCategories.at(catIdx)->mEntries.at(entIdx); }
    const char* getEntryName(int catIdx, int entIdx) { return mCategories.at(catIdx)->mEntries.at(entIdx)->getName(); }
    bool getEntryValid(int catIdx, int entIdx) { return mCategories.at(catIdx)->mEntries.at(entIdx)->isStageExist(); }

    sead::PtrArray<CustomStageCategory>* getCategorys() { return &mCategories; }
    CustomStageCategory* getCategory(int catIdx) { return mCategories.at(catIdx); }
    const char* getCategoryName(int catIdx) { return mCategories.at(catIdx)->getCatName(); }
    const char* getCategoryDesc(int catIdx) { return mCategories.at(catIdx)->getCatDesc(); }
    int getCategorySize(int catIdx) { return mCategories.at(catIdx)->getCatSize(); }

    sead::PtrArray<CustomStageCategory> mCategories;
    
private:
    bool mIsValidResource = false;
    const char* mResourceName = "null";

    al::Resource* mRes = nullptr;
    al::ByamlIter mRootByaml;
};