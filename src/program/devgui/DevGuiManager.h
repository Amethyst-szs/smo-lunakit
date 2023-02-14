#pragma once

#include "imgui.h"

#include "al/scene/Scene.h"

#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/GameSystem.h"

#include "container/seadPtrArray.h"
#include "heap/seadDisposer.h"
#include "heap/seadExpHeap.h"
#include "heap/seadHeap.h"
#include "heap/seadHeapMgr.h"

#include "GetterUtil.h"

#include "devgui/windows/WindowBase.h"
#include "devgui/windows/WindowEditor.h"
#include "devgui/windows/WindowInfo.h"
#include "devgui/windows/WindowMemoryManage.h"
#include "devgui/windows/WindowFPS.h"

#include "devgui/homemenu/HomeMenuBase.h"
#include "devgui/homemenu/HomeMenuWorlds.h"
#include "devgui/homemenu/HomeMenuWindows.h"
#include "devgui/homemenu/HomeMenuExtra.h"

enum WinAnchorType {
    ANC_TOP,
    ANC_BOTTOM,
    ANC_LEFT,
    ANC_RIGHT,
    ANC_TOTAL_SIZE
};

class DevGuiManager {
    SEAD_SINGLETON_DISPOSER(DevGuiManager);
    DevGuiManager();
    ~DevGuiManager();

public:
    void init(sead::Heap* heap);

    void update();
    void updateDisplay();
    void updateCursorState();

    bool isMenuActive() { return mIsActive; };
    bool isFirstStep() { return mIsFirstStep; };

    // Generic getters
    int getWindowCount() { return mWindows.size(); };
    bool* getWindowActiveStateAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getActiveState(); }
    const char* getWindowNameAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getWindowName(); }

    sead::Heap* getHeap() { return mDevGuiHeap; };
    bool* getImGuiDemoWindowState() {return &mIsDisplayImGuiDemo; };

    // Anchor functions
    WinAnchorType getAnchorType() { return mWinAnchor; };
    void setAnchorType(WinAnchorType type) { mIsAnchorChange = true; mWinAnchor = type; };
    void refreshAnchor() { mIsAnchorChange = true; };
    int calcTotalAnchoredWindows();

private:
    // Heap
    sead::Heap* mDevGuiHeap = nullptr; // Uses the game system heap

    // Manager status
    bool mIsActive = false;
    bool mIsFirstStep = false;

    bool mIsAnchorChange = true; // Starts true in order to automatically fire anchor setup on first activation
    WinAnchorType mWinAnchor = WinAnchorType::ANC_TOP;

    // Debug info
    bool mIsDisplayImGuiDemo = false;

    // Array of children classes (Manager holds each window and each home menu tab)
    sead::PtrArray<WindowBase> mWindows;
    sead::PtrArray<HomeMenuBase> mHomeMenuTabs;
};