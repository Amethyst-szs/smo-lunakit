
/*
    --- Welcome to LunaKit! ---
This is the LunaKit Manager, the manager class that controls everything in LunaKit

General Help:
    - Head to the wiki at https://github.com/Amethyst-szs/smo-lunakit/wiki if you are:
    - Using LunaKit as a general user
    - Looking to make custom themes, add your custom stages, or other general plugin type features
    - Add new features to LunaKit
    - Edit features or fix bugs
    - Or anything else you want to use LunaKit for!

Code Documentation: https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#manager-devguimanager
*/

#pragma once

#include "sead/container/seadPtrArray.h"
#include "sead/heap/seadHeap.h"

#include "nn/oe.h"

// All popups
#include "devgui/popups/PopupKeyboard.h"

// Base classes for windows and menu tabs
#include "devgui/windows/WindowBase.h"
#include "devgui/homemenu/HomeMenuBase.h"

class CustomStageManager; // Forward declaration

class DevGuiDocking; // Forward declaration
class DevGuiSettings; // Forward declaration
class DevGuiSaveData; // Forward declaration
class DevGuiTheme; // Forward declaration
class DevGuiHooks; // Forward declaration

class PrimitiveQueue; // Forward declaration
class PrimMenuSettings; // Forward declaration

class WindowGroup; // Forward declaration

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
    void createElements();

    // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#update-vs-updatedisplay
    void update(); // Update is always called every frame (on the sequence)
    void updateDisplay(); // Update display is only used when the menu is currently open

    // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#creating-a-window-class
    template <class T> // Template function to create and add a new window to the list
    void createWindow(const char* winName, bool isActiveByDefault);
    template <class T> // Template function to create and add a new window to the list, as well as a group
    void createWindow(const char* winName, bool isActiveByDefault, WindowGroup* group);

    // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#adding-a-home-bar-item
    template <class T> // Template function to create and add a new tab to the home bar
    void createHomeMenuItem(const char* menuName, bool isDisplayInListByDefault);
    
    WindowGroup* createWindowGroup(const char* groupName, u8 maxSize);

    // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#popups-and-on-screen-keyboard
    bool tryOpenKeyboard(uint16_t maxChars, PopupKeyboardType keyType, const char** output, bool* isKeyboardOpen) { return mPopupKeyboard->tryOpenKeyboard(maxChars, keyType, output, isKeyboardOpen); }
    bool tryOpenKeyboard(uint16_t maxChars, PopupKeyboardType keyType, sead::FixedSafeString<0xff>* output, bool* isKeyboardOpen) { return mPopupKeyboard->tryOpenKeyboard(maxChars, keyType, output, isKeyboardOpen); }

    bool isMenuActive() { return mIsActive; } // Checks if the menu is open
    bool isFirstStep() { return mIsFirstStep; } // Checks if this is the first frame the window is open

    void updateCursorState(); // Shows/hides the cursor based on if the window is open

    // Generic getters
    WindowBase* getWindow(int windowIdx) { return mWindows.at(windowIdx); } // Get a window at an index (casts to WindowBase)
    WindowBase* getWindow(const char* sName);
    int getWindowCount() { return mWindows.size(); } // Total windows (includes closed and non-anchored windows)
    bool* getWindowActiveStateAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getActiveState(); } // Open/close state of a window
    const char* getWindowNameAtIdx(int windowIdx) { return mWindows.at(windowIdx)->getWindowName(); } // Header name of a window

    WindowGroup* getWindowGroup(int groupIdx) { return mWindowGroups.at(groupIdx); } // Get a window group at an idx
    int getWindowGroupCount() { return mWindowGroups.size(); } // Total window groups created

    float* getCurrentScreenSizeMulti() { return nn::oe::GetOperationMode() ? &mScreenSizeDocked : &mScreenSizeHandheld; } // Get the current scale modifier for docked mode
    float* getScreenSizeMultiDocked() { return &mScreenSizeDocked; } // Get the current scale modifier for docked mode
    float* getScreenSizeMultiHandheld() { return &mScreenSizeHandheld; } // Get the current scale modifier for handheld mode

    sead::Heap* getHeap() { return mHeap; } // Heap where data is stored (same as the Stationed Heap)
    DevGuiDocking* getDockSystem() { return mDockSystem; } // Custom DockSpace system used by LunaKit for docking windows
    DevGuiSettings* getSettings() { return mSettings; } // Current settings (used in the settings home menu, written to save file)
    PrimMenuSettings* getPrimitiveSettings() { return mPrimitiveSettings; } // Settings for the prim home menu tab, written to save file
    DevGuiTheme* getTheme() { return mTheme; } // Controls the theme, including reading data from the SD card
    DevGuiSaveData* getSaveData() { return mSaveData; } // Preferences and settings, written to the save file
    CustomStageManager* getCustomStageManager() { return mCustomList; } // Custom stage plugin support
    PrimitiveQueue* getPrimitiveQueue() { return mPrimQueue; } // Accessible primitive renderer queueing

    DevGuiHooks *getHookSettings() { return mHooks; } // Settings for hooks, not stored in save file

    bool* getImGuiDemoWindowState() {return &mIsDisplayImGuiDemo; } // Is the ImGui Demo Window open (accessible in the extras tab)

private:
    bool mIsActive = false; // Is the LunaKit display active
    bool mIsFirstStep = true; // Is this the first frame of the LunaKit display (retriggers each time it is opened)
    bool mIsRequestCursorShow = false; // Setting this bool to true will display the mouse cursor
    bool mIsDisplayWindows = true; // Are the windows hidden by pressing L-Stick?
    bool mIsDisplayImGuiDemo = false; // Display the debug ImGui demo window for testing

    float mScreenSizeDocked = 1.2f;
    float mScreenSizeHandheld = 1.f;

    sead::Heap* mHeap = nullptr; // Uses the stationed heap
    DevGuiDocking* mDockSystem = nullptr; // Custom DockSpace system used by LunaKit for docking windows
    DevGuiSettings* mSettings = nullptr; // Current settings (used in the settings home menu, written to save file)
    PrimMenuSettings* mPrimitiveSettings = nullptr; // Settings for the prim home menu tab, written to save file
    DevGuiTheme* mTheme = nullptr; // Controls the theme, including reading data from the SD card
    DevGuiSaveData* mSaveData = nullptr; // Preferences and settings, written to the save file
    DevGuiHooks *mHooks = nullptr; // Settings for hooks not stored in save file

    CustomStageManager* mCustomList = nullptr; // Custom stage plugin support
    PrimitiveQueue* mPrimQueue = nullptr; // Accessible primitive renderer queueing

    // Popups
    PopupKeyboard* mPopupKeyboard = nullptr; // On screen ImGui keyboard used by other modules

    // Array of children classes (Manager holds each window and each home menu tab)
    sead::PtrArray<WindowBase> mWindows;
    sead::PtrArray<WindowGroup> mWindowGroups;
    sead::PtrArray<HomeMenuBase> mHomeMenuTabs;
};