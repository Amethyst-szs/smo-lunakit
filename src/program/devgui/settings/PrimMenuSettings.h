#pragma once

#include "sead/container/seadPtrArray.h"

#include "logger/Logger.hpp"

class DevGuiManager; // Forward declaration (include is in cpp file)

enum PrimMenuCategories {
    PrimMenuCat_NONE,
    PrimMenuCat_PLAYER,
    PrimMenuCat_TRIANGLE,
    PrimMenuCat_AREA,
    PrimMenuCat_HITSENSOR,
    PrimMenuCat_TOTALSIZE
};

class PrimMenuEntry {
public:
    PrimMenuEntry(bool initState, const char* name, PrimMenuCategories category, bool dependency)
    {
        mValue = initState;
        mName = name;
        mCategory = category;
        mIsDependent = dependency;
    }

    // Current state/value related functions
    bool isTrue() { return mValue; }
    bool* getValuePtr() { return &mValue; }
    void setValue(bool newValue) { mValue = newValue; }
    void toggleValue() { mValue = !mValue; }

    // Name related functions
    const char* getName() { return mName; }
    PrimMenuCategories getCategory() { return mCategory; }

    bool isDependent() { return mIsDependent; }

private:
    bool mValue = false;
    bool mIsDependent = false;
    const char* mName = nullptr;
    PrimMenuCategories mCategory = PrimMenuCat_NONE;
};

// Main class holding all settings
class PrimMenuSettings {
public:
    PrimMenuSettings(DevGuiManager* parent);

    PrimMenuEntry* getSettingEntry(int idx) { return mSettings.at(idx); }
    PrimMenuEntry* getSettingEntryInCat(int idx, PrimMenuCategories cat);
    PrimMenuEntry* getSettingEntryByName(const char* name);
    
    int getTotalSettings() { return mSettings.size(); }
    int getTotalSettingsInCat(PrimMenuCategories cat);

private:
    void registerNewSetting(bool isEnabledByDefault, const char* settingName, PrimMenuCategories cat, bool dependency);
    
    DevGuiManager* mParent;
    sead::PtrArray<PrimMenuEntry> mSettings;
};