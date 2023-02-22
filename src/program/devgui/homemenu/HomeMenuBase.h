
/*
    - LunaKit Home Menu Base -

    Each HomeMenu class controls one header in the bar on the top of the screen
    Every other HomeMenu class inherits from this class

    If you're looking to modify these menus or create new ones:
    Read the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki
*/

#pragma once

#include "imgui.h"

#include "container/seadPtrArray.h"
#include "heap/seadDisposer.h"
#include "heap/seadHeap.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class HomeMenuBase {
public:
    HomeMenuBase(DevGuiManager* parent, const char* menuName, sead::Heap* heap);

    virtual void updateMenu(); // Called whenever this menu is open
    // Unlike categories, these don't have a seperation between run and display since code is triggered once on input (or sets flags)

    virtual const char* getMenuName() { return mMenuName; };

protected:
    // This function is used to preserve font sizing through sub-menus
    // For more information, read the wiki!!
    virtual bool addMenu(const char* name, bool enabled = true);

    DevGuiManager* mParent = nullptr;
    sead::Heap* mDevGuiHeap = nullptr;

    const char* mMenuName = nullptr;
};