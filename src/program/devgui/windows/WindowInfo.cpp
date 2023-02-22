#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowInfo.h"

WindowInfo::WindowInfo(DevGuiManager* parent, const char* winName, bool active, sead::Heap* heap)
    : WindowBase(parent, winName, active, heap)
{
    // Template category
    CategoryInfPlayer* playerCat = new (heap) CategoryInfPlayer("Player", "Player Information", heap);
    mCategories.pushBack(playerCat);
}