#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuCStages.h"

HomeMenuCStages::HomeMenuCStages(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuCStages::updateMenu()
{
    ImGui::MenuItem("ExLaunch Devs", NULL, false, false);

    CustomStageManager* manager = mParent->mCustomList;

    for(int i = 0; i < manager->getResourceCount(); i++) {
        CustomStageResource* curRes = manager->getResource(i);
        drawResource(curRes);
    }

    if (ImGui::MenuItem("Refresh Database")) {
        // Implement function into CustomStageManager to destroy current database and regenerate
    }
}

void HomeMenuCStages::drawResource(CustomStageResource* res)
{
    if(!res->isValid()) {
        ImGui::MenuItem(res->getResourceName(), NULL, false, false);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Archive was found but could\nnot read StageList.byml!");

        return;
    }

    if(addMenu(res->getResourceName())) {

        for(int i = 0; i < res->getResourceSize(); i++) {
            CustomStageCategory* curCat = res->getCategory(i);
            drawCategory(curCat);
        }

        ImGui::EndMenu();
    }
}

void HomeMenuCStages::drawCategory(CustomStageCategory* cat)
{
    if(ImGui::BeginMenu(cat->getCategoryName())) {
        ImGui::MenuItem(cat->getCatDesc(), NULL, false, false);

        for(int i = 0; i < cat->getCategorySize(); i++) {
            CustomStageEntry* curEnt = cat->getEntry(i);
            drawEntry(curEnt);
        }

        ImGui::EndMenu();
    }
}

void HomeMenuCStages::drawEntry(CustomStageEntry* ent)
{
    if(!ent->isStageExist()) {
        ImGui::MenuItem(ent->getName(), NULL, false, false);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("This stage does't exist!\nPlease supply stage file in\nthe LunaKit or Atmosphere folder!");

        return;
    }

    if(ImGui::MenuItem(ent->getName())) {
        // Load stage here, maybe replace this with a sub menu to have a scenario picker like the world list
    }
}