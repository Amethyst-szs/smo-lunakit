
/*
    This class is an assistant to CustomStageManager containing:
    CustomStageResource,
    CustomStageCategory, and
    CustomStageEntry

    Each of these classes are at different levels for reading information from plugin files
    Most likely, you will not need to modify this file or it's source, more general information
    about the custom stage plugin system can be found in CustomStageManager.h and more importantly,
    the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki
*/

#pragma once

#include <basis/seadTypes.h>

#include "Library/Yaml/ByamlIter.h"

#include "nn/fs/fs_directories.h"

#include "sead/container/seadPtrArray.h"

// A specific stage file listed by a plugin
// Has validity checks to verify the stage actually exists in the game's StageData folder
class CustomStageEntry {
public:
    CustomStageEntry(const char* stageName);

    const char* getName() { return mStageName; }
    bool isStageExist() { return mIsExist; }

private:
    const char* mStageName = nullptr;
    bool mIsExist = false;
};

// Category of custom stages within the resource/plugin
class CustomStageCategory {
public:
    CustomStageCategory(al::ByamlIter catIter, sead::Heap* heap);

    // Access information about the category itself
    const char* getCategoryName() { return mCatName; }
    const char* getCategoryDesc() { return mCatDesc; }
    int getCategorySize() { return mEntries.size(); }

    // Access specific custom stage entries inside this category
    sead::PtrArray<CustomStageEntry>* getEntries() { return &mEntries; }
    CustomStageEntry* getEntry(int entIdx) { return mEntries.at(entIdx); }
    const char* getEntryName(int entIdx) { return mEntries.at(entIdx)->getName(); }
    bool getEntryValid(int entIdx) { return mEntries.at(entIdx)->isStageExist(); }

    sead::PtrArray<CustomStageEntry> mEntries;

private:
    al::ByamlIter mIter;
    u32 mCatSize = -1;
    const char* mCatName = "null";
    const char* mCatDesc = "null";
};

// Plugin file information, containing the different categories that exist within itself
class CustomStageResource {
public:
    CustomStageResource(const char* resourcePath, const char* resourceName, sead::Heap* heap);

    const char* getResourceName() { return mResourceName; }
    int getResourceSize() { return mCategories.size(); }

    // Access categories of stages inside this resource/plugin file
    sead::PtrArray<CustomStageCategory>* getCategories() { return &mCategories; }
    CustomStageCategory* getCategory(int catIdx) { return mCategories.at(catIdx); }
    const char* getCategoryName(int catIdx) { return mCategories.at(catIdx)->getCategoryName(); }
    const char* getCategoryDesc(int catIdx) { return mCategories.at(catIdx)->getCategoryDesc(); }
    int getCategorySize(int catIdx) { return mCategories.at(catIdx)->getCategorySize(); }

    // Access custom stage entries
    sead::PtrArray<CustomStageEntry>* getEntries(int catIdx) { return &mCategories.at(catIdx)->mEntries; }
    CustomStageEntry* getEntry(int catIdx, int entIdx) { return mCategories.at(catIdx)->mEntries.at(entIdx); }
    const char* getEntryName(int catIdx, int entIdx) { return mCategories.at(catIdx)->mEntries.at(entIdx)->getName(); }
    bool getEntryValid(int catIdx, int entIdx) { return mCategories.at(catIdx)->mEntries.at(entIdx)->isStageExist(); }

    sead::PtrArray<CustomStageCategory> mCategories;
    
private:
    const char* mResourceName = "null";

    al::ByamlIter mRootByaml;
};
