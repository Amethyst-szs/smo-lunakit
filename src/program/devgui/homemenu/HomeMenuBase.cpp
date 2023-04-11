#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuBase.h"

HomeMenuBase::HomeMenuBase(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
{
    Logger::log("Constructing HomeMenu: %s\n", menuName);

    mParent = parent;
    mHeap = parent->getHeap();
    
    mMenuName = menuName;
    mIsDisplayInList = isDisplayInListByDefault;
}

bool HomeMenuBase::addMenu(const char* name, bool enabled)
{
    bool isOpen = ImGui::BeginMenu(name, enabled);
    if(isOpen)
        ImGui::SetWindowFontScale(1.5f);
    
    return isOpen;
}