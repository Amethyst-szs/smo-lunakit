#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuWindows.h"

HomeMenuWindows::HomeMenuWindows(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuWindows::updateMenu()
{
    if (addMenu("Window Anchor")) {
        ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

        if (ImGui::MenuItem("Top"))
            mParent->setAnchorType(WinAnchorType::ANC_TOP);

        if (ImGui::MenuItem("Bottom"))
            mParent->setAnchorType(WinAnchorType::ANC_BOTTOM);

        if (ImGui::MenuItem("Left"))
            mParent->setAnchorType(WinAnchorType::ANC_LEFT);

        if (ImGui::MenuItem("Right"))
            mParent->setAnchorType(WinAnchorType::ANC_RIGHT);
        
        ImGui::PopItemFlag();
        
        ImGui::EndMenu();
    }

    if (addMenu("Themes")) {
        ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

        DevGuiTheme* theme = mParent->getTheme();

        for(int i = 0; i < theme->getThemeCount(); i++) {
            if (ImGui::MenuItem(theme->getThemeName(i)))
                theme->setWinTheme(i);
        }

        if(ImGui::MenuItem("Refresh Themes")) {
            theme->finalize();
            theme->init();
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
        }
    }

    ImGui::PopItemFlag();
}