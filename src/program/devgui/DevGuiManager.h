
/*
    --- Welcome to LunaKit! ---
This is the LunaKit Manager, the manager class that controls everything in LunaKit

Help:
    - Head to the wiki at https://github.com/Amethyst-szs/smo-lunakit/wiki if you are:
    - Using LunaKit as a general user
    - Looking to make custom themes, add your custom stages, or other general plugin type features
    - Add new features to LunaKit
    - Edit features or fix bugs
    - Or anything else you want to use LunaKit for!
*/

#pragma once

// Current version of the application (change this if you make changes, especially changes that effect the save data!)
#define LUNAKITVERSION "V2"

// General includes
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

// Custom stage plugin support
#include "cstages/CustomStageManager.h"

// All extra DevGui features included by the manager
#include "devgui/savedata/DevGuiSaveData.h"
#include "devgui/settings/DevGuiSettings.h"
#include "devgui/theme/DevGuiTheme.h"

// All windows
#include "devgui/windows/WindowBase.h"
#include "devgui/windows/WindowEditor.h"
#include "devgui/windows/WindowInfo.h"
#include "devgui/windows/WindowMemoryManage.h"
#include "devgui/windows/WindowActorBrowse.h"
#include "devgui/windows/WindowFPS.h"

// All tabs on the bar the top of the screen
#include "devgui/homemenu/HomeMenuBase.h"
#include "devgui/homemenu/HomeMenuFile.h"
#include "devgui/homemenu/HomeMenuSettings.h"
#include "devgui/homemenu/HomeMenuWindows.h"
#include "devgui/homemenu/HomeMenuWorlds.h"
#include "devgui/homemenu/HomeMenuCStages.h"
#include "devgui/homemenu/HomeMenuExtra.h"

// All positions the windows can be placed on the screen
enum WinAnchorType {
    ANC_TOP,
    ANC_BOTTOM,
    ANC_LEFT,
    ANC_RIGHT,
    ANC_TOTAL_SIZE
};

class DevGuiManager {
    // This class is a singleton! It does not have a typical constructor
    // This is class is created in GameSystemInit in main.cpp
    // Access this class from anywhere using DevGuiManager::instance()->...
    SEAD_SINGLETON_DISPOSER(DevGuiManager);
    DevGuiManager();
    ~DevGuiManager();

public:
    // Create the DevGuiManager, only called once in the GameSystemInit
    void init(sead::Heap* heap);

    void update(); // Update is always called every frame (on the sequence)
    void updateDisplay(); // Update display is only used when the menu is currently open
    void updateNoclip(); // Controls the player's noclip movement (likely want to move this somewhere else)

    bool isMenuActive() { return mIsActive; } // Checks if the menu is open
    bool isFirstStep() { return mIsFirstStep; } // Checks if this is the first frame the window is open

    // Anchor functions
    WinAnchorType getAnchorType() { return mWinAnchor; } // Current anchor position
    void setAnchorType(WinAnchorType type) { mIsAnchorChange = true; mWinAnchor = type; } // Change the anchor and queue a refresh
    void refreshAnchor() { mIsAnchorChange = true; } // Refresh the anchor position (used when opening/closing windows to resize)
    int calcTotalAnchoredWindows(); // Amount of open windows in the anchor list (excludes windows outside the list ex. FPS Window)

    // Generic getters
    WindowBase* getWindow(int windowIdx) { return mWindows.at(windowIdx); } // Get a window at an index (casts to WindowBase)
    int getWindowCount() { return mWindows.size(); } // Total windows (includes closed and non-anchored windows)
    bool* getWindowActiveStateAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getActiveState(); } // Open/close state of a window
    const char* getWindowNameAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getWindowName(); } // Header name of a window

    sead::Heap* getHeap() { return mDevGuiHeap; } // Heap where data is stored (same as the Stationed Heap)
    DevGuiSettings* getSettings() { return mSettings; } // Current settings (used in the settings home menu, written to save file)
    DevGuiTheme* getTheme() { return mTheme; } // Controls the theme, including reading data from the SD card
    DevGuiSaveData* getSaveData() { return mSaveData; } // Preferences and settings, written to the save file
    CustomStageManager* getCustomStageManager() { return mCustomList; } // Custom stage plugin support

    bool* getImGuiDemoWindowState() {return &mIsDisplayImGuiDemo; } // Is the ImGui Demo Window open (accessible in the extras tab)

private:
    void updateCursorState(); // Shows/hides the cursor based on if the window is open

    bool mIsActive = false; // Is the LunaKit display active
    bool mIsFirstStep = false; // Is this the first frame of the LunaKit display (retriggers each time it is opened)
    bool mIsDisplayAnchorWindows = true; // Are the main windows hidden by pressing L-Stick?

    sead::Heap* mDevGuiHeap = nullptr; // Uses the stationed heap
    DevGuiSettings* mSettings = nullptr; // Current settings (used in the settings home menu, written to save file)
    DevGuiTheme* mTheme = nullptr; // Controls the theme, including reading data from the SD card
    DevGuiSaveData* mSaveData = nullptr; // Preferences and settings, written to the save file
    CustomStageManager* mCustomList = nullptr; // Custom stage plugin support

    // Window anchor stuff
    bool mIsAnchorChange = true; // Starts true in order to automatically fire anchor setup on first activation
    WinAnchorType mWinAnchor = WinAnchorType::ANC_TOP; // Default anchor is top, is replaced by data in save file if it exists

    // Debug info
    bool mIsDisplayImGuiDemo = false;

    // Array of children classes (Manager holds each window and each home menu tab)
    sead::PtrArray<WindowBase> mWindows;
    sead::PtrArray<HomeMenuBase> mHomeMenuTabs;
};