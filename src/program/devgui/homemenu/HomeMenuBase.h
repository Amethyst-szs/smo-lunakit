#pragma once

#include "imgui.h"

#include "container/seadPtrArray.h"
#include "heap/seadDisposer.h"
#include "heap/seadHeap.h"

class DevGuiManager; // Forward declaration (include is in cpp file)

class HomeMenuBase {
public:
    HomeMenuBase(DevGuiManager* parent, const char* menuName, sead::Heap* heap);

    virtual void updateMenu();
    // Unlike categories, these don't have a seperation between run and display since code is triggered once on input (or sets flags)

    virtual const char* getMenuName() { return mMenuName; };

protected:
    virtual bool addMenu(const char* name, bool enabled = true);

    DevGuiManager* mParent = nullptr;
    sead::Heap* mDevGuiHeap = nullptr;

    const char* mMenuName = nullptr;
};