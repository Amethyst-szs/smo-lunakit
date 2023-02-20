#pragma once

#include "al/byaml/ByamlIter.h"
#include "al/resource/Resource.h"
#include "al/util.hpp"

#include "nn/fs/fs_directories.hpp"
#include "nn/fs/fs_files.hpp"
#include "nn/result.h"
#include "nn/init.h"

#include "helpers/fsHelper.h"

#include "sead/heap/seadExpHeap.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadHeapMgr.h"
#include "sead/filedevice/seadFileDeviceMgr.h"

#include "Logger/Logger.hpp"

class DevGuiManager; // Forward declaration (include is in cpp file)

class DevGuiTheme {
public:
    DevGuiTheme(DevGuiManager* parent) { mParent = parent; }

    void init();
    void finalize();

    void tryUpdateTheme();

    const char* getThemeName();
    const char* getThemeName(int idx);
    int getCurThemeIdx() { return mThemeIdx; };
    s64 getThemeCount() { return mEntryCount; }

    void setWinThemeByIdx(int theme) {mIsRefreshTheme = true; mThemeIdx = theme; }
    void setWinThemeByName(const char* themeName);
    void refreshTheme() { mIsRefreshTheme = true; }

    nn::fs::DirectoryEntry getFile(int idx) const { return mEntries[idx]; }
    const char* getFileName(int idx) const { return mEntries[idx].m_Name; }
    s64 getFileCount() const { return mEntryCount; }

private:
    void loadColorData(ImVec4* result, al::ByamlIter* colors, const char* colorName);
    void setStyleParam(bool* target, al::ByamlIter* parameters, const char* parameterName);
    void setStyleParam(float* target, al::ByamlIter* parameters, const char* parameterName);
    void setStyleParam(ImVec2* target, al::ByamlIter* parameters, const char* parameterName);

    void setupDirectoryInfo();

    DevGuiManager* mParent = nullptr;

    bool mIsRefreshTheme = true;
    int mThemeIdx = 0;

    s64 mEntryCount = -1;
    nn::fs::DirectoryEntry* mEntries = nullptr;
    al::ByamlIter* mThemes = nullptr;
};