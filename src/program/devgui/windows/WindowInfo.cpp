#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowInfo.h"

WindowInfo::WindowInfo(DevGuiManager* parent, const char* winName, sead::Heap* heap)
    : WindowBase(parent, winName, heap)
{
    // Setup window config
    mConfig.mTrans = ImVec2(427, 19);
    mConfig.mSize = ImVec2(427, 220);

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

void WindowInfo::updateWinDisplay()
{
    WindowBase::updateWinDisplay();
}

void WindowInfo::configImGuiStyle()
{
    WindowBase::configImGuiStyle();
}