#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuBase.h"

HomeMenuBase::HomeMenuBase(DevGuiManager* parent, const char* menuName)
{
    mParent = parent;
    mHeap = parent->getHeap();
    
    mMenuName = menuName;
}

bool HomeMenuBase::addMenu(const char* name, bool enabled)
{
    bool isOpen = ImGui::BeginMenu(name, enabled);
    if(isOpen)
        ImGui::SetWindowFontScale(1.5f);
    
    return isOpen;
}