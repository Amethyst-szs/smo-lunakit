#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuSettings.h"

HomeMenuSettings::HomeMenuSettings(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
    : HomeMenuBase(parent, menuName, isDisplayInListByDefault)
{}

void HomeMenuSettings::updateMenuDisplay()
{
    DevGuiSettings* set = mParent->getSettings();

    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

    for(int i = 0; i < set->getTotalSettings(); i++) {
        DevGuiSettingsEntry* entry = set->getSettingEntry(i);
        parameterEdit(entry->getName(), entry->getValuePtr(), entry->isAllowSave());
    }

    ImGui::PopItemFlag();
}

void HomeMenuSettings::parameterEdit(const char* name, bool* value, bool isSave)
{
    if(ImGui::MenuItem(name, NULL, *value)) {
        *value = !(*value);
        if(isSave)
            mParent->getSaveData()->queueSaveWrite();
    }
}