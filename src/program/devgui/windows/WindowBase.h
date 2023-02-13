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
    WindowBase(DevGuiManager* parent, const char* winName, sead::Heap* heap);

    virtual void configImGuiStyle();
    virtual void setupAnchor(WinAnchorType type);

    virtual void updateWin();
    virtual bool tryUpdateWinDisplay();
    
    virtual const char* getWindowName() { return mWinName; };
    virtual int getCategoryCount() { return mCategories.size(); };

protected:
    const char* mWinName = "null";

    DevGuiManager* mParent;
    DevGuiWindowConfig mConfig;
    sead::Heap* mDevGuiHeap;

    bool mIsActive = true;

    sead::PtrArray<CategoryBase> mCategories;
};