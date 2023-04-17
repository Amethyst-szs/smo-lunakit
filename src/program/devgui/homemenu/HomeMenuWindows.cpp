#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuWindows.h"
#include "devgui/savedata/DevGuiSaveData.h"
#include "devgui/theme/DevGuiTheme.h"
#include "devgui/windows/WindowGroup.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_backend/imgui_impl_nvn.hpp"

HomeMenuWindows::HomeMenuWindows(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
    : HomeMenuBase(parent, menuName, isDisplayInListByDefault)
{}

void HomeMenuWindows::updateMenuDisplay()
{
    ImGui::MenuItem("Appearance:", nullptr, false, false);
    
    if(ImGui::Button("Save"))
        mParent->getSaveData()->writeImGuiLayout();

    ImGui::SameLine();
    if(ImGui::Button("Load"))
        mParent->getSaveData()->readImGuiLayout();
        
    ImGui::SameLine();
    ImGui::Text("Layout");
    
    ImGui::SetNextItemWidth(97.f * (*mParent->getCurrentScreenSizeMulti()));
    if(ImGui::SliderFloat("Opacity", &ImGui::GetStyle().Alpha, 0.7f, 1.f, "%.2f"))
        mParent->getSaveData()->queueSaveWrite();
    
    drawInterfaceSizeEditor(mParent->getScreenSizeMultiDocked(), "Dock Size");
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("Set the interface scaling factor for\nwhen the switch is in docked mode");

    drawInterfaceSizeEditor(mParent->getScreenSizeMultiHandheld(), "Handheld Size");
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("Set the interface scaling factor for\nwhen the switch is in handheld mode");

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

    // Create a seperator between settings and wins
    ImGui::NewLine();
    ImGui::MenuItem("Windows:", nullptr, false, false);

    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

    // List of all non-grouped windows
    for (int i = 0; i < mParent->getWindowCount(); i++) {
        WindowBase* win = mParent->getWindow(i);

        if(win->isInGroup())
            continue;

        bool* isActive = win->getActiveState();
        
        if(ImGui::MenuItem(win->getWindowName(), NULL, *isActive)) {
            *isActive = !(*isActive);
            mParent->getSaveData()->queueSaveWrite();
        }
    }

    // List of all grouped windows
    for (int i = 0; i < mParent->getWindowGroupCount(); i++) {
        WindowGroup* group = mParent->getWindowGroup(i);

        bool tree = addMenu(group->getName());
        if(!tree)
            continue;

        ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

        for(int w = 0; w < group->getSize(); w++) {
            WindowBase* win = group->getWindowInGroup(w);
            bool* isActive = win->getActiveState();
        
            if(ImGui::MenuItem(win->getWindowName(), NULL, *isActive)) {
                *isActive = !(*isActive);
                mParent->getSaveData()->queueSaveWrite();
            }
        }

        ImGui::PopItemFlag();
        ImGui::EndMenu();
    }

    ImGui::PopItemFlag();
}

void HomeMenuWindows::drawInterfaceSizeEditor(float* sizePtr, const char* sliderName)
{
    ImGui::SetNextItemWidth(97.f  * (*mParent->getCurrentScreenSizeMulti()));

    ImGui::SliderFloat(sliderName, sizePtr, 1.f, 1.5f, "%.1f");
    if(ImGui::IsItemDeactivated()) {
        ImVec2 &dispSize = ImGui::GetIO().DisplaySize;
        bool isDockedMode = !(dispSize.x == 1280 && dispSize.y == 720);
        ImguiNvnBackend::updateScale(isDockedMode, *mParent->getScreenSizeMultiDocked(), *mParent->getScreenSizeMultiHandheld());

        mParent->getSaveData()->queueSaveWrite();
        mParent->getTheme()->refreshTheme();
    }
}