#pragma once

#include "imgui.h"

#include "container/seadPtrArray.h"
#include "heap/seadDisposer.h"
#include "heap/seadHeap.h"

#include "devgui/DevGuiSettings.h"

class HomeMenuBase {
public:
    HomeMenuBase(const char* menuName, sead::Heap* heap);

    virtual void updateMenu();
    // Unlike categories, these don't have a seperation between run and display since code is triggered once on input (or sets flags)

    virtual const char* getMenuName() { return mMenuName; };

protected:
    sead::Heap* mDevGuiHeap = nullptr;
    const char* mMenuName = nullptr;
};