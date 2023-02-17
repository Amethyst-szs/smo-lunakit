#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowInfo.h"

WindowInfo::WindowInfo(DevGuiManager* parent, const char* winName, sead::Heap* heap)
    : WindowBase(parent, winName, heap)
{
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoCollapse;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoMove;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoResize;

    // Template category
    CategoryInfPlayer* playerCat = new (heap) CategoryInfPlayer("Player", "Player Information", heap);
    mCategories.pushBack(playerCat);
}

void WindowInfo::updateWin()
{
    WindowBase::updateWin();
}

bool WindowInfo::tryUpdateWinDisplay()
{
    return WindowBase::tryUpdateWinDisplay();
}