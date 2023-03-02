#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuWindows.h"

HomeMenuWindows::HomeMenuWindows(DevGuiManager* parent, const char* menuName)
    : HomeMenuBase(parent, menuName)
{}

void HomeMenuWindows::updateMenu()
{
    if (addMenu("Window Anchor")) {
        ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

        if (ImGui::MenuItem("Top"))
            setAnc((int)WinAnchorType::ANC_TOP);

        if (ImGui::MenuItem("Bottom"))
            setAnc((int)WinAnchorType::ANC_BOTTOM);

        if (ImGui::MenuItem("Left"))
            setAnc((int)WinAnchorType::ANC_LEFT);

        if (ImGui::MenuItem("Right"))
            setAnc((int)WinAnchorType::ANC_RIGHT);
        
        ImGui::PopItemFlag();
        
        ImGui::EndMenu();
    }

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
            mParent->refreshAnchor();
            mParent->getSaveData()->queueSaveWrite();
        }
    }

    ImGui::PopItemFlag();
}

void HomeMenuWindows::setAnc(int type)
{
    mParent->setAnchorType((WinAnchorType)type);
    mParent->getSaveData()->queueSaveWrite();
}