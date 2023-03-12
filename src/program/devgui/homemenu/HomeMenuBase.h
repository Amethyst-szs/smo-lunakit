
/*
    - LunaKit Home Menu Base -

    Each HomeMenu class controls one header in the bar on the top of the screen
    Every other HomeMenu class inherits from this class

    If you're looking to modify these menus or create new ones:
    Read the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#home-bar-items
*/

#pragma once

#include "imgui.h"

#include "al/util.hpp"

#include "container/seadPtrArray.h"
#include "heap/seadDisposer.h"
#include "heap/seadHeap.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class HomeMenuBase {
public:
    HomeMenuBase(DevGuiManager* parent, const char* menuName);

    virtual void updateMenu() {} // Called every frame regardless of if the menu is currently open
    virtual void updateMenuDisplay() {} // Called whenever this menu is opened

    virtual const char* getMenuName() { return mMenuName; };

protected:
    // This function is used to preserve font sizing through sub-menus
    // For more information, read the wiki!!
    virtual bool addMenu(const char* name, bool enabled = true);

    DevGuiManager* mParent = nullptr;
    sead::Heap* mHeap = nullptr;

    const char* mMenuName = nullptr;
};