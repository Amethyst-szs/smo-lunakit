#pragma once

#include "container/seadPtrArray.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/GameSystem.h"
#include "heap/seadHeap.h"
#include "math/seadVector.h"

#include "program/devgui/categories/DevGuiCategoryBase.h"

class DevGuiWindowBase {
public:
    DevGuiWindowBase(const char* winName) { mWinName = winName; };
    virtual void init(sead::Heap* heap);

    virtual void updateWin();
    virtual void updateWinDisplay();

    virtual bool isAnchored() { return mIsAnchored; };

    virtual const char* getWindowName() { return mWinName; };
    virtual int getCategoryCount() { return mCategories.size(); };
    virtual float getWindowPosX() { return mWinPos.x; };
    virtual float getWindowPosY() { return mWinPos.y; };
    virtual float getWindowSizeX() { return mWinScale.x; };
    virtual float getWindowSizeY() { return mWinScale.y; };

private:
    sead::Heap* mDevGuiHeap;

    const char* mWinName = "null";
    
    // Replace these both with ImGui vectors in porting?
    bool mIsAnchored = false;
    sead::Vector2f mWinPos = sead::Vector2f::zero;
    sead::Vector2f mWinScale = sead::Vector2f::zero;

    int mCategoryIdx = 0;
    sead::PtrArray<DevGuiCategoryBase> mCategories;
};