#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuPrims.h"
#include "imgui.h"

HomeMenuPrims::HomeMenuPrims(DevGuiManager* parent, const char* menuName)
    : HomeMenuBase(parent, menuName)
{
    mSettings = parent->getPrimitiveSettings();
}

void HomeMenuPrims::updateMenu()
{
    // if(!mIsEnableRendering)
    //     return;
    
    // al::Scene* scene = tryGetScene();
    // if(!scene)
    //     return;
    
    // PrimitiveQueue* queue = mParent->getPrimitiveQueue();


}

void HomeMenuPrims::updateMenuDisplay()
{
    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
    
    // Display all non-categorized items
    for(int i = 0; i < mSettings->getTotalSettingsInCat(PrimMenuCat_NONE); i++) {
        PrimMenuEntry* entry = mSettings->getSettingEntryInCat(i, PrimMenuCat_NONE);
        if(ImGui::MenuItem(entry->getName(), nullptr, entry->isTrue()))
            entry->toggleValue();
    }

    ImGui::PopItemFlag();
}