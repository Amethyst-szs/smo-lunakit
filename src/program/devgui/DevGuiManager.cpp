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

#include "program/devgui/DevGuiManager.h"

// This class is a singleton! It does not have a typical constructor
// This is class is created in GameSystemInit in main.cpp
// Access this class from anywhere using DevGuiManager::instance()->...
SEAD_SINGLETON_DISPOSER_IMPL(DevGuiManager)
DevGuiManager::DevGuiManager() = default;
DevGuiManager::~DevGuiManager() = default;

void DevGuiManager::createElements()
{
    sead::ScopedCurrentHeapSetter heapSetter(mDevGuiHeap);
    
    // Create all display windows
    createWindow<WindowMemoryManage>("Memory Manager", true, true, 1);
    createWindow<WindowEditor>("Param Editor", true, true, 1);
    createWindow<WindowInfo>("Info Viewer", true, true, 1);
    createWindow<WindowActorBrowse>("Actor Browser", false, true, 2);
    createWindow<WindowFPS>("FPS Window", true, false, 1);

    // Create all home menu tabs
    createHomeMenuItem<HomeMenuFile>("File");
    createHomeMenuItem<HomeMenuSettings>("Settings");
    createHomeMenuItem<HomeMenuWindows>("Windows");
    createHomeMenuItem<HomeMenuWorlds>("Kingdoms");
    createHomeMenuItem<HomeMenuCStages>("Stages");
    createHomeMenuItem<HomeMenuExtra>("Extras");
}

void DevGuiManager::init(sead::Heap* heap)
{
    Logger::log("Initing DevGuiManager... (Version: %s)\n", LUNAKITVERSION);
    
    // Sets the DevGuiHeap to the heap passed in as an arg, along with setting the current scope to the heap
    mDevGuiHeap = heap;
    sead::ScopedCurrentHeapSetter heapSetter(heap);

    // Allocate 0x10 (16) slots for windows and tabs at the top
    // Please don't increase these unless you REALLY need more space for some ungodly reason
    mWindows.allocBuffer(0x10, mDevGuiHeap);
    mHomeMenuTabs.allocBuffer(0x10, mDevGuiHeap);

    // Create keyboard popup used by other windows and actions
    mKeyboard = new DevGuiKeyboard();

    // Primitive renderer class & functions
    mPrimitive = new DevGuiPrimitive();

    // Creates the settings class, accessed by various functions and set by HomeMenuSettings
    mSettings = new DevGuiSettings(this, heap);

    // Creates a theme class and loads in the themes from the SD card themes folder
    mTheme = new DevGuiTheme(this);
    mTheme->init();

    // Creates the custom stage manager and loads in the custom stage information from the SD card CustomStages folder
    mCustomList = new CustomStageManager();
    mCustomList->init(heap);

    // Create all windows and home menu items
    createElements();

    // Load and read save data if it already exists
    mSaveData = new DevGuiSaveData(heap);
    mSaveData->init(this);
    mSaveData->read();
}

void DevGuiManager::update()
{
    // Check for enabling and disabling the window
    if (al::isPadHoldR(-1) && al::isPadHoldZR(-1) && al::isPadTriggerL(-1)) {
        mIsActive = !mIsActive;
        if (mIsActive)
            mIsFirstStep = true;
    }

    // Toggle display/hide of all anchored windows
    if(mIsActive && al::isPadTriggerPressLeftStick(-1)) {
        mIsDisplayAnchorWindows = !mIsDisplayAnchorWindows;
    }

    // This is run every frame, only actually saves if a save is queued and the timer hits zero
    mSaveData->trySave();

    // Note: Each window's update function runs even with the menu closed/inactive!
    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);
        entry->updateWin();
    }
}

void DevGuiManager::updateDisplay()
{
    // Show/hide the cursor if the window is opened/closed
    updateCursorState();

    if(!mIsActive)
        return;

    // Load and draw all windows (and update anchors if needed)
    int totalAnchorWin = calcTotalAnchoredWindows();
    int curAnchorWin = 0;

    mKeyboard->update();
    mTheme->tryUpdateTheme();

    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);
        if(!entry->isActive() || (entry->isInAnchorList() && !mIsDisplayAnchorWindows))
            continue;

        ImGui::Begin(entry->getWindowName(), entry->getCloseInteractionPtr(), entry->getWindowConfig()->mWindowFlags);

        if(mIsAnchorChange) {
            entry->setupAnchor(totalAnchorWin, curAnchorWin);
            curAnchorWin += entry->getAnchorPages();
        }

        entry->tryUpdateWinDisplay();

        ImGui::End();
    }

    mIsAnchorChange = false;
    
    // Load and draw all home menu tabs
    if (ImGui::BeginMainMenuBar()) {
        ImGui::SetWindowFontScale(1.5f);
        
        for (int i = 0; i < mHomeMenuTabs.size(); i++) {
            auto* entry = mHomeMenuTabs.at(i);
            if (ImGui::BeginMenu(entry->getMenuName())) {
                entry->updateMenu();

                ImGui::EndMenu();
            }
        }

        if(mSaveData->isSaveQueued()) {
            sead::FormatFixedSafeString<0x20> display("   Saving Preferences... %.00fs", mSaveData->getSaveQueueTime());
            if(ImGui::BeginMenu(display.cstr(), false))
                ImGui::EndMenu();
        }

        if(!mIsDisplayAnchorWindows && ImGui::BeginMenu("   Hidden! (Press L-Stick)", false))
            ImGui::EndMenu();

        ImGui::EndMainMenuBar();
    }

    // Draw the demo window if the settings class has it enabled
    if(mIsDisplayImGuiDemo)
        ImGui::ShowDemoWindow();

    // Reset the first step flag when complete!
    if (mIsFirstStep)
        mIsFirstStep = false;
}

void DevGuiManager::updateCursorState()
{
    if (!mIsActive)
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);

    if (mIsFirstStep)
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
}

template <class T>
void DevGuiManager::createWindow(const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
{
    T* window = new (mDevGuiHeap) T(this, winName, isActiveByDefault, isAnchor, windowPages);
    mWindows.pushBack(window);
}

template <class T>
void DevGuiManager::createHomeMenuItem(const char* menuName)
{
    T* home = new (mDevGuiHeap) T(this, menuName);
    mHomeMenuTabs.pushBack(home);
}

int DevGuiManager::calcTotalAnchoredWindows()
{
    int total = 0;
    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);

        if(*(entry->getActiveState()) && entry->isInAnchorList())
            total += entry->getAnchorPages();
    }

    return total;
}