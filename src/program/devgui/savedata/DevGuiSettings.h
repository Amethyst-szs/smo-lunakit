#pragma once

#include "al/util.hpp"

#include "sead/heap/seadExpHeap.h"
#include "sead/heap/seadHeap.h"
#include "sead/heap/seadHeapMgr.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class DevGuiSettingsEntry {
public:
    DevGuiSettingsEntry(bool initState, const char* name)
    {
        mValue = initState;
        mName = name;
    }

    bool isTrue() { return mValue; }
    bool* getValuePtr() { return &mValue; }
    const char* getName() { return mName; }

    void setValue(bool newValue) { mValue = newValue; }
    void toggleValue() { mValue = !mValue; }

private:
    bool mValue = false;
    const char* mName = nullptr;
};

class DevGuiSettings {
public:
    DevGuiSettings(DevGuiManager* parent, sead::Heap* heap);

    DevGuiSettingsEntry* getSettingEntry(int idx) { return mSettings.at(idx); }
    int getTotalSettings() { return mSettings.size(); }

    bool getStateByName(const char* settingName);
    void setStateByName(const char* settingName, bool newState);
    void toggleStateByName(const char* settingName);

    bool getStateByIdx(int idx) { return mSettings.at(idx)->isTrue(); }
    bool* getStatePtrByIdx(int idx) { return mSettings.at(idx)->getValuePtr(); }
    void setStateByIdx(int idx, bool state) { return mSettings.at(idx)->setValue(state); }
    const char* getNameByIdx(int idx) { return mSettings.at(idx)->getName(); }

private:
    DevGuiManager* mParent;
    sead::PtrArray<DevGuiSettingsEntry> mSettings;
};