#pragma once

#include "imgui.h"

#include "container/seadPtrArray.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/GameSystem.h"
#include "heap/seadHeap.h"
#include "math/seadVector.h"

#include "program/GetterUtil.h"
#include "devgui/DevGuiWindowConfig.h"
#include "devgui/categories/CategoryBase.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class WindowBase {
public:
    WindowBase(DevGuiManager* parent, const char* winName, bool active, sead::Heap* heap);

    virtual void setupAnchor(int totalAnchoredWindows, int anchorIdx);

    virtual void updateWin();
    virtual bool tryUpdateWinDisplay();
    
    virtual const char* getWindowName() { return mWinName; }
    virtual bool* getCloseInteractionPtr() { return &mIsCloseUnpressed; }
    virtual DevGuiWindowConfig* getWindowConfig() { return &mConfig; }
    virtual int getCategoryCount() { return mCategories.size(); }
    virtual bool* getActiveState() { return &mIsActive; }

    virtual void setActiveState(bool isActive) { mIsActive = isActive; }
    
    virtual bool isActive() { return mIsActive; }
    virtual bool isInAnchorList() { return mIsAnchorList; }

protected:
    bool mIsActive = true;
    bool mIsCloseUnpressed = true;
    const char* mWinName = "null";

    DevGuiManager* mParent;
    DevGuiWindowConfig mConfig;
    sead::Heap* mDevGuiHeap;

    bool mIsAnchorList = true;

    sead::PtrArray<CategoryBase> mCategories;
};