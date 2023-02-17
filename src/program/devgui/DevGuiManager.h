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

#include "cstages/CustomStageManager.h"

#include "devgui/DevGuiSettings.h"
#include "devgui/DevGuiTheme.h"

#include "devgui/windows/WindowBase.h"
#include "devgui/windows/WindowEditor.h"
#include "devgui/windows/WindowInfo.h"
#include "devgui/windows/WindowMemoryManage.h"
#include "devgui/windows/WindowFPS.h"

#include "devgui/homemenu/HomeMenuBase.h"
#include "devgui/homemenu/HomeMenuFile.h"
#include "devgui/homemenu/HomeMenuSettings.h"
#include "devgui/homemenu/HomeMenuWindows.h"
#include "devgui/homemenu/HomeMenuWorlds.h"
#include "devgui/homemenu/HomeMenuCStages.h"
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

    void updateNoclip();

    // Anchor functions
    WinAnchorType getAnchorType() { return mWinAnchor; };
    void setAnchorType(WinAnchorType type) { mIsAnchorChange = true; mWinAnchor = type; };
    void refreshAnchor() { mIsAnchorChange = true; };
    int calcTotalAnchoredWindows();

    // Theme functions
    DevGuiTheme* getTheme() { return mTheme; }

    bool isMenuActive() { return mIsActive; };
    bool isFirstStep() { return mIsFirstStep; };

    // Generic getters
    int getWindowCount() { return mWindows.size(); };
    bool* getWindowActiveStateAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getActiveState(); }
    const char* getWindowNameAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getWindowName(); }

    sead::Heap* getHeap() { return mDevGuiHeap; };
    DevGuiSettings* getSettings() { return &mSettings; }
    CustomStageManager* getCustomStageManager() { return mCustomList; }
    bool* getImGuiDemoWindowState() {return &mIsDisplayImGuiDemo; };

private:
    sead::Heap* mDevGuiHeap = nullptr; // Uses the stationed heap
    bool mIsActive = false;
    bool mIsFirstStep = false;

    // Settings / Cheats
    DevGuiSettings mSettings;

    // Window display stuff
    DevGuiTheme* mTheme = nullptr;
    bool mIsAnchorChange = true; // Starts true in order to automatically fire anchor setup on first activation
    WinAnchorType mWinAnchor = WinAnchorType::ANC_TOP;

    // Custom stage information
    CustomStageManager* mCustomList = nullptr;

    // Debug info
    bool mIsDisplayImGuiDemo = false;

    // Array of children classes (Manager holds each window and each home menu tab)
    sead::PtrArray<WindowBase> mWindows;
    sead::PtrArray<HomeMenuBase> mHomeMenuTabs;
};