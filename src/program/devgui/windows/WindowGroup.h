
/*
    - LunaKit Window Groups -

    This class is mainly for organizing windows in the "Windows" home menu tab
    When creating windows, they can be assigned into groups, making sub-categories

    Check the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation
*/

#pragma once

#include "sead/container/seadPtrArray.h"

#include "types.h"
#include "WindowBase.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class WindowGroup {
public:
    WindowGroup(DevGuiManager* parent, const char* groupName, u8 maxSize);
    void registerWindow(WindowBase* window);

    const char* getName() { return mGroupName; }
    int getSize() { return mWindows.size(); }

    WindowBase* getWindowInGroup(int idx) { return mWindows.at(idx); }
    sead::PtrArray<WindowBase>& getPtrArray() { return mWindows; }

private:
    DevGuiManager* mParent = nullptr;
    const char* mGroupName = nullptr;
    u8 mMaxSize = 0;
    sead::PtrArray<WindowBase> mWindows;
};