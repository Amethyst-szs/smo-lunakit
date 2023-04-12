
/*
    - LunaKit Home Menu Base -

    Each HomeMenu class controls one header in the bar on the top of the screen
    Every other HomeMenu class inherits from this class

    If you're looking to modify these menus or create new ones:
    Read the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#home-bar-items
*/

#pragma once

#include "container/seadPtrArray.h"
#include "heap/seadDisposer.h"
#include "heap/seadHeap.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class HomeMenuBase {
public:
    HomeMenuBase(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    // updateMenu is called every frame even if the LunaKit display is closed
    virtual void updateMenu(){};

    // updateMenuDisplay is only called if the menu is open AND the LunaKit display is active
    virtual void updateMenuDisplay() = 0;

    // updatePostDisplay is only called if the menu is open AND the LunaKit display is active
    // Mainly serves as a place to open popups or modals if needed
    virtual void updatePostDisplay(){};

    virtual const char* getMenuName() { return mMenuName; }
    virtual bool isDisplayInList() { return mIsDisplayInList; }

protected:
    // This function is used to preserve font sizing through sub-menus
    // For more information, read the wiki!!
    virtual bool addMenu(const char* name, bool enabled = true);

    DevGuiManager* mParent = nullptr;
    sead::Heap* mHeap = nullptr;

    bool mIsDisplayInList = true;
    const char* mMenuName = nullptr;
};