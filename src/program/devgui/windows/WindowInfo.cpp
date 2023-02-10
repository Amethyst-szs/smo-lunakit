#include "program/devgui/windows/WindowInfo.h"

WindowInfo::WindowInfo(const char* winName, sead::Heap* heap)
    : WindowBase(winName, heap)
{
    // Setup window config
    mConfig.mTrans = ImVec2(1280 / 3, 0);
    mConfig.mSize = ImVec2(1280 / 3, 220);

    mConfig.mWindowFlags |= ImGuiWindowFlags_NoCollapse;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoMove;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoResize;

    // Template category
    CategoryBase* tempCat = new (heap) CategoryBase("Placeholder", "Pizza Balls");
    mCategories.pushBack(tempCat);
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