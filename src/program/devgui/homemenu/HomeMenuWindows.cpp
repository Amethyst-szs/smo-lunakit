#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuWindows.h"

HomeMenuWindows::HomeMenuWindows(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuWindows::updateMenu()
{
    if (ImGui::BeginMenu("Window Anchor")) {
        for(int i = 0; i < WinAnchorType::TOTAL_SIZE; i++) {
            if (ImGui::MenuItem(WinAnchorTypeNames))
                mParent->setAnchorType((WinAnchorType)i);
        }
    }

    // Add a selector for what windows are open (idk how the fuck to do this, I should probably find a 
    // new way to expose data from DevGuiManager to the HomeMenu selectors. :amethy73Shrug:)

    // if (ImGui::MenuItem("ImGui Demo Window", "", DevGuiSettings::instance()->mIsDisplayImGuiDemo)) {
        
    // }
}