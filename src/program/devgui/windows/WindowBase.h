
/*
    - LunaKit Window Base -

    This class is the basis for all windows displayed in game
    All other windows will inherit from this class and call back to this class's functions

    Looking to make new windows or modify existing ones?
    Check the wiki! https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#windows
*/

#pragma once

#include "devgui/categories/CategoryBase.h"

#include "sead/container/seadPtrArray.h"

class DevGuiManager; // Forward declaration (include is in cpp file)
class WindowGroup; // Forward declaration

typedef int ImGuiWindowFlags; // Forward declaration from imgui.h

class WindowBase {
public:
    WindowBase(DevGuiManager* parent, const char* winName, bool isActiveByDefault);

    // updateWin is called every frame (where the window is active) even if the LunaKit display is closed
    virtual void updateWin();

    // updateWinDisplay is only called if the window is open AND the LunaKit display is active
    virtual bool tryUpdateWinDisplay();

    // updatePostDisplay is only called if the window is open AND the LunaKit display is active
    // Mainly serves as a place to open popups or modals if needed
    virtual void updatePostDisplay(){};

    // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#categories
    template <class T> // Template function to create and add category to list
    void createCategory(const char* catName, const char* catDesc) {
        T* cat = new (mHeap) T(catName, catDesc, mHeap);
        mCategories.pushBack(cat);
    }
    
    // Generic getter functions, can be accessed from anywhere
    // Not recommended to override unless you have a very specific goal in mind
    virtual const char* getWindowName() { return mWinName; }
    virtual bool* getCloseInteractionPtr() { return &mIsCloseUnpressed; } // This value is set by clicking the X on the window
    virtual int getCategoryCount() { return mCategories.size(); } // Will return 0 if no categories exist
    virtual bool* getActiveState() { return &mIsActive; }
    virtual ImGuiWindowFlags getWindowFlags() { return mWindowFlags; }

    // Allows enabling/displaying the window from elsewhere
    virtual void setActiveState(bool isActive) { mIsActive = isActive; }
    
    virtual bool isActive() { return mIsActive; }

    // WindowGroup functions
    virtual bool isInGroup() { return mGroup; }
    virtual void setGroup(WindowGroup* group) { mGroup = group; }

protected:
    // Parent info
    DevGuiManager* mParent;
    sead::Heap* mHeap;

    // Current state
    bool mIsActive = true;
    bool mIsFirstStep = true;
    bool mIsCloseUnpressed = true;

    // Window information
    const char* mWinName = "null";
    WindowGroup* mGroup = nullptr;
    ImGuiWindowFlags mWindowFlags = 0;

    sead::PtrArray<CategoryBase> mCategories;
};