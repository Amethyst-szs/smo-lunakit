#pragma once

/*
    --- Welcome to LunaKit! ---
This is the LunaKit Manager, the manager class that controls everything in LunaKit

Help:
    - Head to the wiki at https://github.com/Amethyst-szs/smo-lunakit/wiki if you are:
    - Looking to make custom themes, add your custom stages, or other general plugin type features
    - Add new features to LunaKit
    - Edit features or fix bugs
    - Or anything else you want to use LunaKit for!

Where should I start:
*/

// Current version of the application (change this if you make changes, especially changes that effect the save data!)
#define LUNAKITVERSION "Beta-2"


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

#include "devgui/savedata/DevGuiSaveData.h"
#include "devgui/savedata/DevGuiSettings.h"
#include "devgui/theme/DevGuiTheme.h"

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

    bool isMenuActive() { return mIsActive; }
    bool isFirstStep() { return mIsFirstStep; }

    // Anchor functions
    WinAnchorType getAnchorType() { return mWinAnchor; }
    void setAnchorType(WinAnchorType type) { mIsAnchorChange = true; mWinAnchor = type; }
    void refreshAnchor() { mIsAnchorChange = true; }
    int calcTotalAnchoredWindows();

    // Generic getters
    WindowBase* getWindow(int windowIdx) { return mWindows.at(windowIdx); }
    int getWindowCount() { return mWindows.size(); }
    bool* getWindowActiveStateAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getActiveState(); }
    const char* getWindowNameAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getWindowName(); }

    sead::Heap* getHeap() { return mDevGuiHeap; }
    DevGuiSettings* getSettings() { return mSettings; }
    DevGuiTheme* getTheme() { return mTheme; }
    DevGuiSaveData* getSaveData() { return mSaveData; }
    CustomStageManager* getCustomStageManager() { return mCustomList; }
    bool* getImGuiDemoWindowState() {return &mIsDisplayImGuiDemo; }

private:
    bool mIsActive = false;
    bool mIsFirstStep = false;
    bool mIsDisplayAnchorWindows = true;

    sead::Heap* mDevGuiHeap = nullptr; // Uses the stationed heap
    DevGuiSettings* mSettings = nullptr;
    DevGuiTheme* mTheme = nullptr;
    DevGuiSaveData* mSaveData = nullptr;
    CustomStageManager* mCustomList = nullptr;

    // Window anchor stuff
    bool mIsAnchorChange = true; // Starts true in order to automatically fire anchor setup on first activation
    WinAnchorType mWinAnchor = WinAnchorType::ANC_TOP;

    // Debug info
    bool mIsDisplayImGuiDemo = false;

    // Array of children classes (Manager holds each window and each home menu tab)
    sead::PtrArray<WindowBase> mWindows;
    sead::PtrArray<HomeMenuBase> mHomeMenuTabs;
};