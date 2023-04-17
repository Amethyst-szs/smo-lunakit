#include "WindowGroup.h"
#include "devgui/DevGuiManager.h"

WindowGroup::WindowGroup(DevGuiManager* parent, const char* groupName, u8 maxSize)
{
    mParent = parent;
    mGroupName = groupName;
    mMaxSize = maxSize;
    mWindows.tryAllocBuffer(mMaxSize, mParent->getHeap());
}

void WindowGroup::registerWindow(WindowBase *window)
{
    window->setGroup(this);
    mWindows.pushBack(window);
}

