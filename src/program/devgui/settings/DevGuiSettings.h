
/*
    - LunaKit Settings -

    This class is all the settings inside the "Settings" category in the top bar menu
    All information here is automatically written to the save file
    This information can be accessed anywhere to use the settings

    New settings are added/definied in the DevGuiSettings constructor

    You can access settings by name or index in various different ways depending on the situation
    Read the wiki to learn more! https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#settings
*/

#pragma once

#include "al/util.hpp"

#include "sead/heap/seadExpHeap.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadHeapMgr.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

// Each entry is definied as a DevGuiSettingsEntry, containing helper functions
// along with a state, name, and if it should be saved
class DevGuiSettingsEntry {
public:
    DevGuiSettingsEntry(bool initState, bool isSave, const char* name)
    {
        mValue = initState;
        mName = name;
        mIsSave = isSave;
    }

    // Save related functions
    bool isAllowSave() { return mIsSave; }

    // Current state/value related functions
    bool isTrue() { return mValue; }
    bool* getValuePtr() { return &mValue; }
    void setValue(bool newValue) { mValue = newValue; }
    void toggleValue() { mValue = !mValue; }

    // Name related functions
    const char* getName() { return mName; }

private:
    bool mValue = false;
    bool mIsSave = true;
    const char* mName = nullptr;
};

// Main class holding all settings
class DevGuiSettings {
public:
    DevGuiSettings(DevGuiManager* parent);

    DevGuiSettingsEntry* getSettingEntry(int idx) { return mSettings.at(idx); }
    int getTotalSettings() { return mSettings.size(); }

    // Access SettingsEntry by the setting name
    bool getStateByName(const char* settingName);
    void setStateByName(const char* settingName, bool newState);
    void toggleStateByName(const char* settingName);

    // Access SettingsEntry by index in settings list
    bool getStateByIdx(int idx) { return mSettings.at(idx)->isTrue(); }
    bool* getStatePtrByIdx(int idx) { return mSettings.at(idx)->getValuePtr(); }
    void setStateByIdx(int idx, bool state) { return mSettings.at(idx)->setValue(state); }
    const char* getNameByIdx(int idx) { return mSettings.at(idx)->getName(); }

private:
    void registerNewSetting(bool isEnabledByDefault, bool isSave, const char* settingName);
    
    DevGuiManager* mParent;
    sead::PtrArray<DevGuiSettingsEntry> mSettings;
};