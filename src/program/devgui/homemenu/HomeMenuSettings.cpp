#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuSettings.h"

HomeMenuSettings::HomeMenuSettings(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuSettings::updateMenu()
{
    DevGuiSettings* set = mParent->getSettings();

    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

    for(int i = 0; i < set->getTotalSettings(); i++) {
        DevGuiSettingsEntry* entry = set->getSettingEntry(i);
        parameterEdit(entry->getName(), entry->getValuePtr());
    }

    ImGui::PopItemFlag();
}

void HomeMenuSettings::parameterEdit(const char* name, bool* value)
{
    if(ImGui::MenuItem(name, NULL, *value)) {
        *value = !(*value);
        mParent->getSaveData()->queueSaveWrite();
    }
}