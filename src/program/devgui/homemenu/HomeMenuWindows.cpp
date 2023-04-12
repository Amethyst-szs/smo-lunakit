#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuWindows.h"

HomeMenuWindows::HomeMenuWindows(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
    : HomeMenuBase(parent, menuName, isDisplayInListByDefault)
{}

void HomeMenuWindows::updateMenuDisplay()
{
    if(ImGui::MenuItem("Save Layout"))
        mParent->getSaveData()->writeImGuiLayout();
    if(ImGui::MenuItem("Load Layout"))
        mParent->getSaveData()->readImGuiLayout();

    if (addMenu("Themes")) {
        ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

        DevGuiTheme* theme = mParent->getTheme();

        for(int i = 0; i < theme->getThemeCount(); i++) {
            if (ImGui::MenuItem(theme->getThemeName(i))) {
                theme->setWinThemeByIdx(i);
                mParent->getSaveData()->queueSaveWrite();
            }
        }
        
        ImGui::PopItemFlag();
        ImGui::EndMenu();
    }

    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

    for (int i = 0; i < mParent->getWindowCount(); i++) {
        bool* isActive = mParent->getWindowActiveStateAtIdx(i);
        
        if(ImGui::MenuItem(mParent->getWindowNameAtIdx(i), NULL, *isActive)) {
            *isActive = !(*isActive);
            mParent->getSaveData()->queueSaveWrite();
        }
    }

    ImGui::PopItemFlag();
}

void HomeMenuWindows::setAnc(int type)
{
    mParent->getSaveData()->queueSaveWrite();
}