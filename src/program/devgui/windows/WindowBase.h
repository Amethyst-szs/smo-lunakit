
/*
    - LunaKit Window Base -

    This class is the basis for all windows displayed in game
    All other windows will inherit from this class and call back to this class's functions

    Looking to make new windows or modify existing ones?
    Check the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki
*/

#pragma once

#include "imgui.h"

#include "al/util.hpp"

#include "container/seadPtrArray.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/GameSystem.h"
#include "heap/seadHeap.h"
#include "math/seadVector.h"

#include "program/GetterUtil.h"
#include "devgui/DevGuiWindowConfig.h"
#include "devgui/categories/CategoryBase.h"

#include "logger/Logger.hpp"

class DevGuiManager; // Forward declaration (include is in cpp file)

class WindowBase {
public:
    WindowBase(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);

    // Determines how the window is positioned
    // Most non-anchored windows will override this function with their own placement code
    virtual void setupAnchor(int totalAnchoredWindows, int anchorIdx);

    // updateWin is called every frame (where the window is active) even if the LunaKit display is closed
    virtual void updateWin();

    // updateWinDisplay is only called if the window is open AND the LunaKit display is active
    // If window does not have any categories, the implementation is responsible for running ImGui::End()
    virtual bool tryUpdateWinDisplay();

    template <class T> // Template function to create and add category to list
    void createCategory(const char* catName, const char* catDesc) {
        T* cat = new (mDevGuiHeap) T(catName, catDesc);
        mCategories.pushBack(cat);
    }
    
    // Generic getter functions, can be accessed from anywhere
    // Not recommended to override unless you have a very specific goal in mind
    virtual const char* getWindowName() { return mWinName; }
    virtual bool* getCloseInteractionPtr() { return &mIsCloseUnpressed; } // This value is set by clicking the X on the window
    virtual DevGuiWindowConfig* getWindowConfig() { return &mConfig; }
    virtual int getCategoryCount() { return mCategories.size(); } // Will return 0 if no categories exist
    virtual bool* getActiveState() { return &mIsActive; }

    // Allows enabling/displaying the window from elsewhere
    virtual void setActiveState(bool isActive) { mIsActive = isActive; }
    
    virtual bool isActive() { return mIsActive; }

    // If window is not anchored (defined in the constructor code) it will be placed independently from other windows
    virtual bool isInAnchorList() { return mIsAnchorList; }
    virtual int getAnchorPages() { return mAnchorPages; }

protected:
    bool mIsActive = true;
    bool mIsCloseUnpressed = true;
    const char* mWinName = "null";

    DevGuiManager* mParent;
    DevGuiWindowConfig mConfig;
    sead::Heap* mDevGuiHeap;

    bool mIsAnchorList = true;
    int mAnchorPages = 1;

    sead::PtrArray<CategoryBase> mCategories;
};