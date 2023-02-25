#include "devgui/DevGuiManager.h"

#include "devgui/savedata/DevGuiSettings.h"

// Settings are added and created here
DevGuiSettings::DevGuiSettings(DevGuiManager* parent, sead::Heap* heap)
{
    // Max of 0x20 (32) settings, should never go beyond this but if you do for some reason, increase this number!
    mSettings.allocBuffer(0x20, heap);

    DevGuiSettingsEntry* autosave = new (heap) DevGuiSettingsEntry(true, true, "Autosave");
    mSettings.pushBack(autosave);

    DevGuiSettingsEntry* hud = new (heap) DevGuiSettingsEntry(true, true, "Display HUD");
    mSettings.pushBack(hud);

    DevGuiSettingsEntry* music = new (heap) DevGuiSettingsEntry(true, true, "Play Music");
    mSettings.pushBack(music);

    DevGuiSettingsEntry* checkpoint = new (heap) DevGuiSettingsEntry(false, true, "Always Allow Checkpoints");
    mSettings.pushBack(checkpoint);

    DevGuiSettingsEntry* noclip = new (heap) DevGuiSettingsEntry(false, false, "Noclip");
    mSettings.pushBack(noclip);

    DevGuiSettingsEntry* gmr = new (heap) DevGuiSettingsEntry(false, false, "Grey Moon Refresh");
    mSettings.pushBack(gmr);

    DevGuiSettingsEntry* buttonmotionroll = new (heap) DevGuiSettingsEntry(false, false, "Button Motion Roll");
    mSettings.pushBack(buttonmotionroll);

    DevGuiSettingsEntry* nodamage = new (heap) DevGuiSettingsEntry(false, false, "No Damage");
    mSettings.pushBack(nodamage);

    Logger::log("Created %i settings\n", mSettings.size());
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