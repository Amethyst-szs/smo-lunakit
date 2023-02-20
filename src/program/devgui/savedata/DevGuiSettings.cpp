#include "devgui/DevGuiManager.h"

#include "devgui/savedata/DevGuiSettings.h"

DevGuiSettings::DevGuiSettings(DevGuiManager* parent, sead::Heap* heap)
{
    mSettings.allocBuffer(0x20, heap);

    DevGuiSettingsEntry* autosave = new (heap) DevGuiSettingsEntry(true, "Autosave");
    mSettings.pushBack(autosave);

    DevGuiSettingsEntry* hud = new (heap) DevGuiSettingsEntry(true, "Display HUD");
    mSettings.pushBack(hud);

    DevGuiSettingsEntry* music = new (heap) DevGuiSettingsEntry(true, "Play Music");
    mSettings.pushBack(music);

    DevGuiSettingsEntry* noclip = new (heap) DevGuiSettingsEntry(false, "Noclip");
    mSettings.pushBack(noclip);

    DevGuiSettingsEntry* checkpoint = new (heap) DevGuiSettingsEntry(false, "Always Allow Checkpoints");
    mSettings.pushBack(checkpoint);
}

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