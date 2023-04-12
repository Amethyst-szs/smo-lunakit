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

    if (addMenu("Opacity")) {
        ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

        opacitySetting("100%", 1.f);
        opacitySetting("95%", 0.95f);
        opacitySetting("90%", 0.9f);
        opacitySetting("85%", 0.85f);
        opacitySetting("80%", 0.8f);
        opacitySetting("70%", 0.7f);
        
        ImGui::PopItemFlag();
        ImGui::EndMenu();
    }

    // Create a seperator between settings and wins
    ImGui::MenuItem(" ", nullptr, false, false); 

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

void HomeMenuWindows::opacitySetting(const char* label, float opacity)
{
    ImGuiStyle* style = &ImGui::GetStyle();

    if(ImGui::MenuItem(label)){
        style->Alpha = opacity;
        style->DisabledAlpha = opacity;
        mParent->getSaveData()->queueSaveWrite();
    }
}