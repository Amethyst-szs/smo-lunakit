#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowInfo.h"

WindowInfo::WindowInfo(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages)
{
    // Player Information category
    CategoryInfPlayer* playerCat = new (mDevGuiHeap) CategoryInfPlayer("Player", "Player Information", mDevGuiHeap);
    mCategories.pushBack(playerCat);
}