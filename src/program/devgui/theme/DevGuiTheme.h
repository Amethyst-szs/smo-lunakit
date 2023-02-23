
/*
    - LunaKit Theme Loader -

    Themes in LunaKit are loaded through the SD card (folder path determined by THEMEPATH, look below)

    Creating themes:
    These themes can be created through Switch Toolbox or any other .byml editor
    For more information on making themes, see the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki/LunaKit-Theme-Plugins

*/

#pragma once

#define THEMEPATH "sd:/LunaKit/LKData/Themes/"

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

    void tryUpdateTheme(); // Called whenever the theme changes (or first opening LunaKit)

    const char* getThemeName(); // Gets the current theme name
    const char* getThemeName(int idx); // Gets the theme name at a specific index (NOTE: Indexes are not consistent between game loads)
    int getCurThemeIdx() { return mThemeIdx; };
    s64 getThemeCount() { return mEntryCount; }

    void setWinThemeByIdx(int theme) {mIsRefreshTheme = true; mThemeIdx = theme; } // Sets the current theme by index in list of themes
    void setWinThemeByName(const char* themeName); // Sets the current theme by the name of the theme
    void refreshTheme() { mIsRefreshTheme = true; } // Reloads the theme without changing the current theme

private:
    nn::fs::DirectoryEntry getFile(int idx) const { return mEntries[idx]; }
    const char* getFileName(int idx) const { return mEntries[idx].m_Name; }
    s64 getFileCount() const { return mEntryCount; }
    
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