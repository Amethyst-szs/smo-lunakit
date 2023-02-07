#pragma once

#include "al/scene/Scene.h"

#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/GameSystem.h"

#include "container/seadPtrArray.h"
#include "heap/seadDisposer.h"
#include "heap/seadHeap.h"

#include "program/devgui/windows/DevGuiWindowBase.h"

class DevGuiManager {
    SEAD_SINGLETON_DISPOSER(DevGuiManager);
    DevGuiManager();
    ~DevGuiManager();

public:
    void init(sead::Heap* heap);

    void update();
    void updateDisplay();

    bool isMenuActive() { return mIsActive; };

    sead::Heap* getHeap() { return mDevGuiHeap; }
    int getWindowCount() { return mWindows.size(); }

private:
    sead::Heap* mDevGuiHeap = nullptr; // Uses the game system heap

    bool mIsActive = false;
    sead::PtrArray<DevGuiWindowBase> mWindows;
};