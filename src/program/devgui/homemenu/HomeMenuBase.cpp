#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuBase.h"

HomeMenuBase::HomeMenuBase(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
{
    mParent = parent;
    mMenuName = menuName;
    mDevGuiHeap = heap;
}

void HomeMenuBase::updateMenu()
{
    // Run code for the game here
}

bool HomeMenuBase::addMenu(const char* name, bool enabled)
{
    bool isOpen = ImGui::BeginMenu(name, enabled);
    if(isOpen)
        ImGui::SetWindowFontScale(1.5f);
    
    return isOpen;
}