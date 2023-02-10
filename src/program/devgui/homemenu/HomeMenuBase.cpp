#include "program/devgui/homemenu/HomeMenuBase.h"

HomeMenuBase::HomeMenuBase(const char* menuName, sead::Heap* heap)
{
    mMenuName = menuName;
    mDevGuiHeap = heap;
}

void HomeMenuBase::updateMenu()
{
    // Run code for the game here
}