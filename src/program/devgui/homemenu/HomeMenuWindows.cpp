#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuWindows.h"

HomeMenuWindows::HomeMenuWindows(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuWindows::updateMenu()
{
    if (ImGui::BeginMenu("Window Anchor")) {
        if (ImGui::MenuItem("Top"))
            mParent->setAnchorType(WinAnchorType::ANC_TOP);

        if (ImGui::MenuItem("Bottom"))
            mParent->setAnchorType(WinAnchorType::ANC_BOTTOM);
        
        ImGui::EndMenu();
    }

    for (int i = 0; i < mParent->getWindowCount(); i++) {
        bool* isActive = mParent->getWindowActiveStateAtIdx(i);

        if(ImGui::MenuItem(mParent->getWindowNameAtIdx(i), NULL, *isActive)) {
            // *isActive = !(*isActive);
            // mParent->refreshAnchor();
        }
    }
}