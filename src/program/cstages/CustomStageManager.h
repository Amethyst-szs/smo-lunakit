
/*
    - Custom Stage Manager (for LunaKit) -

    This set of classes is stored outside of the devgui folder due to being mostly entirely seperate from
    LunaKit's functionality. However, this file is the core to supporting external custom stages for players
    and creators!

    Custom Stage information is read from CUSTOMSTAGEPATH (definied below) and used to create the
    "Stages" header at the top of the LunaKit interface. These files are read in by this class
    and allow instant warping to custom stages on a dime!

    If you're looking to support LunaKit in a custom stage:
    https://github.com/Amethyst-szs/smo-lunakit/wiki/Custom-Stage-Support

*/

#pragma once

#define CUSTOMSTAGEPATH "sd:/LunaKit/LKData/CustomStages/"

#include "nn/fs/fs_directories.h"

#include "CustomStage.h"

class CustomStageManager {
public:
    CustomStageManager() {}; // Nothing occurs on construction

    void init(sead::Heap* heap); // Init and load all data for all custom stage plugin files

    // Access information about the different resources (files) inside the custom stage plugin folder
    sead::PtrArray<CustomStageResource>* getResources() { return &mStageResources; }
    CustomStageResource* getResource(int idx) { return mStageResources.at(idx); }
    const char* getResourceName(int idx) { return mStageResources.at(idx)->getResourceName(); }
    int getResourceCount() { return mStageResources.size(); }

    // Access categories of stages inside specific plugin files
    sead::PtrArray<CustomStageCategory>* getCategories(int resIdx) { return &mStageResources.at(resIdx)->mCategories; }
    CustomStageCategory* getCategory(int resIdx, int catIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx); }
    const char* getCategoryName(int resIdx, int catIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->getCategoryName(); }
    const char* getCategoryDesc(int resIdx, int catIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->getCategoryDesc(); }
    int getCategorySize(int resIdx, int catIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->getCategorySize(); }

    // Access custom stage entries
    // THESE FUNCTIONS ARE NOT RECOMMENDED FOR USE
    // They are super clunky, taking in three variables to naviage through the file, category, and entry
    // It is strongly recommended to access the resource, then category, then entry unless you know what you're doing
    sead::PtrArray<CustomStageEntry>* getEntries(int resIdx, int catIdx) { return &mStageResources.at(resIdx)->mCategories.at(catIdx)->mEntries; }
    CustomStageEntry* getEntry(int resIdx, int catIdx, int entIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->mEntries.at(entIdx); }
    const char* getEntryName(int resIdx, int catIdx, int entIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->mEntries.at(entIdx)->getName(); }
    bool getEntryValid(int resIdx, int catIdx, int entIdx) { return mStageResources.at(resIdx)->mCategories.at(catIdx)->mEntries.at(entIdx)->isStageExist(); }

    // Access info about the custom stage directory
    nn::fs::DirectoryEntry getFile(int idx) const { return mEntries[idx]; }
    const char* getFileName(int idx) const { return mEntries[idx].mName; }
    s64 getFileCount() const { return mEntryCount; }

private:
    void setupDirectoryInfo(); // Loads all file names from folder
    s64 mEntryCount = -1;
    nn::fs::DirectoryEntry* mEntries = nullptr;

    sead::PtrArray<CustomStageResource> mStageResources;
};
