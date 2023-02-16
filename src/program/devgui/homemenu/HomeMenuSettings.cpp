#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuSettings.h"

HomeMenuSettings::HomeMenuSettings(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuSettings::updateMenu()
{
    DevGuiSettings* set = mParent->getSettings();

    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

    ImGui::MenuItem("Settings:", NULL, false, false);

    parameterEdit("Autosaving", &set->mIsAutosave);
    parameterEdit("Display HUD", &set->mIsDisplayHUD);
    parameterEdit("Play Music", &set->mIsPlayMusic);

    ImGui::MenuItem("Cheats:", NULL, false, false);

    parameterEdit("Noclip", &set->mIsNoclip);
    parameterEdit("Hyperspeed", &set->mIsHyperspeed);
    parameterEdit("Bonking", &set->mIsBonk);

    ImGui::PopItemFlag();
}

void HomeMenuSettings::parameterEdit(const char* name, bool* value)
{
    if(ImGui::MenuItem(name, NULL, *value))
        *value = !(*value);
}