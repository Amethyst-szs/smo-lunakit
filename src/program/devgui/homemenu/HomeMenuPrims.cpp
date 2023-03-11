#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuPrims.h"

HomeMenuPrims::HomeMenuPrims(DevGuiManager* parent, const char* menuName)
    : HomeMenuBase(parent, menuName)
{}

void HomeMenuPrims::updateMenu()
{
    if(!mIsEnableRendering)
        return;
    
    al::Scene* scene = tryGetScene();
    if(!scene)
        return;
    
    PrimitiveQueue* queue = mParent->getPrimitiveQueue();

    // Logger::log("Pushing entry\n");
    // PrimitiveTypePoint* point = new (al::getSequenceHeap()) PrimitiveTypePoint({0.f, 0.f, 0.f}, 200.f, {1.f, 1.f, 1.f, 0.75f});
    // queue->pushEntry(point);
    // Logger::log("Pushed entry\n");
}

void HomeMenuPrims::updateMenuDisplay()
{
    ImGui::MenuItem("All Rendering", nullptr, &mIsEnableRendering);
}