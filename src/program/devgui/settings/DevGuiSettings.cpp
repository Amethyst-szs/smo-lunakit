#include "devgui/DevGuiManager.h"

#include "devgui/settings/DevGuiSettings.h"

// Settings are added and created here
DevGuiSettings::DevGuiSettings(DevGuiManager* parent, sead::Heap* heap)
{
    mSettingsHeap = heap;

    // Max of 0x20 (32) settings, should never go beyond this but if you do for some reason, increase this number!
    mSettings.allocBuffer(0x20, heap);

    registerNewSetting(false, false, "Noclip");
    registerNewSetting(false, true, "Button Motion Roll");
    registerNewSetting(false, true, "Grey Moon Refresh");
    registerNewSetting(false, true, "No Damage");
    registerNewSetting(false, true, "Always Allow Checkpoints");
    registerNewSetting(true, true, "Autosave");
    registerNewSetting(true, true, "Display HUD");
    registerNewSetting(true, true, "Play Music");

    Logger::log("Created %i settings\n", mSettings.size());
}

void DevGuiSettings::registerNewSetting(bool isEnabledByDefault, bool isSave, const char* settingName)
{
    DevGuiSettingsEntry* newSet = new (mSettingsHeap) DevGuiSettingsEntry(isEnabledByDefault, isSave, settingName);
    mSettings.pushBack(newSet);
}



// Everything below this point is general helper functions, likely not what you are looking for!

bool DevGuiSettings::getStateByName(const char* settingName)
{
    for(DevGuiSettingsEntry entry : mSettings) {
        if(al::isEqualString(entry.getName(), settingName))
            return entry.isTrue();
    }

    Logger::log("DevGuiSettings getStateByName failed! Setting Name: %s\n", settingName);
    return false;
}

void DevGuiSettings::setStateByName(const char* settingName, bool newState)
{
    for(DevGuiSettingsEntry entry : mSettings) {
        if(al::isEqualString(entry.getName(), settingName)) {
            entry.setValue(newState);
            return;
        }
    }

    Logger::log("DevGuiSettings setStateByName failed! Setting Name: %s\n", settingName);
    return;
}

void DevGuiSettings::toggleStateByName(const char* settingName)
{
    for(DevGuiSettingsEntry entry : mSettings) {
        if(al::isEqualString(entry.getName(), settingName)) {
            entry.toggleValue();
            return;
        }
    }

    Logger::log("DevGuiSettings toggleStateByName failed! Setting Name: %s\n", settingName);
    return;
}