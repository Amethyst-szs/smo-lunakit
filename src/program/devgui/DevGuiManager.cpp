#include "program/devgui/DevGuiManager.h"
#include "program/devgui/DevGuiHooks.h"

// sead
#include "heap/seadDisposer.h"
#include "heap/seadHeapMgr.h"

// Helpers
#include "helpers/GetHelper.h"
#include "helpers/InputHelper.h"

// Custom stage plugin support
#include "cstages/CustomStageManager.h"

// Primitive renderering queue system, allowing LunaKit to push primitive rendering shapes from anywhere
#include "primitives/PrimitiveQueue.h"

// All extra DevGui features included by the manager
#include "devgui/DevGuiHooks.h"
#include "devgui/docking/DevGuiDocking.h"
#include "devgui/savedata/DevGuiSaveData.h"
#include "devgui/settings/DevGuiSettings.h"
#include "devgui/settings/PrimMenuSettings.h"
#include "devgui/theme/DevGuiTheme.h"

// All windows
#include "devgui/windows/ActorBrowse/WindowActorBrowse.h"
#include "devgui/windows/Editor/WindowEditor.h"
#include "devgui/windows/FPS/WindowFPS.h"
#include "devgui/windows/Graphics/WindowGBuffer.h"
#include "devgui/windows/Graphics/WindowPresets.h"
#include "devgui/windows/Info/WindowInfo.h"
#include "devgui/windows/MemoryTools/WindowLoadLog.h"
#include "devgui/windows/MemoryTools/WindowMemoryManage.h"
#include "devgui/windows/StagePause/WindowStagePause.h"
#include "devgui/windows/TAS/WindowTAS.h"
#include "devgui/windows/WindowGroup.h"

// All tabs on the bar the top of the screen
#include "devgui/homemenu/HomeMenuCStages.h"
#include "devgui/homemenu/HomeMenuExtra.h"
#include "devgui/homemenu/HomeMenuFile.h"
#include "devgui/homemenu/HomeMenuPrims.h"
#include "devgui/homemenu/HomeMenuSettings.h"
#include "devgui/homemenu/HomeMenuUpdater.h"
#include "devgui/homemenu/HomeMenuWindows.h"
#include "devgui/homemenu/HomeMenuWorlds.h"

#include "imgui.h"

// This class is a singleton! It does not have a typical constructor
// This is class is created in GameSystemInit in main.cpp
// Access this class from anywhere using DevGuiManager::instance()->...
SEAD_SINGLETON_DISPOSER_IMPL(DevGuiManager)
DevGuiManager::DevGuiManager() = default;
DevGuiManager::~DevGuiManager() = default;

void DevGuiManager::createElements() {
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);

    // Create all display windows
    Logger::log("Constructing all windows\n");
    createWindow<WindowEditor>(paramEditorWindowName, true);
    createWindow<WindowInfo>(infoWindowName, true);
    createWindow<WindowActorBrowse>(actorBrowseWindowName, false);
    createWindow<WindowFPS>(fpsWindowName, true);
    createWindow<WindowTAS>(tasWindowName, false);
    createWindow<WindowStagePause>(stagePauseWindowName, false);

    WindowGroup* memoryGroup = createWindowGroup("Memory Tools", 2);
    createWindow<WindowLoadLog>(loadLogWindowName, false, memoryGroup);
    createWindow<WindowMemoryManage>(memoryManageWindowName, true, memoryGroup);

    WindowGroup* graphicsGroup = createWindowGroup("Graphics", 2);
    createWindow<WindowPresets>(presetsWindowName, false, graphicsGroup);
    createWindow<WindowGBuffer>(gbufferWindowName, false, graphicsGroup);

    // Create all home menu tabs
    Logger::log("Constructing all home menu items\n");
    createHomeMenuItem<HomeMenuFile>("File", true);
    createHomeMenuItem<HomeMenuSettings>("Settings", true);
    createHomeMenuItem<HomeMenuWindows>("Windows", true);
    createHomeMenuItem<HomeMenuPrims>("Prims", true);
    createHomeMenuItem<HomeMenuWorlds>("Kingdom", true);
    createHomeMenuItem<HomeMenuCStages>("Stages", true);
    createHomeMenuItem<HomeMenuExtra>("Extras", true);
    createHomeMenuItem<HomeMenuUpdater>("Update!", false);

    // Create each popup window
    mPopupKeyboard = new PopupKeyboard();
}

void DevGuiManager::init(sead::Heap* heap) {
    Logger::log("Initing DevGuiManager... (Version: %s)\n", GIT_VER);

    // Sets the DevGuiHeap to the heap passed in as an arg, along with setting the current scope to the heap
    mHeap = heap;
    sead::ScopedCurrentHeapSetter heapSetter(heap);

    mHooks = new DevGuiHooks();

    // Allocate 0x20 (32) slots for windows, 0x10 (16) slots for win groups, and 0x10 (16) for tabs at the top
    // Please don't increase these unless you REALLY need more space for some ungodly reason
    mWindows.allocBuffer(0x20, heap);
    mWindowGroups.allocBuffer(0x10, heap);
    mHomeMenuTabs.allocBuffer(0x10, heap);

    mDockSystem = new DevGuiDocking(this);

    mSettings = new DevGuiSettings(this);  // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#settings

    mCustomList = new CustomStageManager();  // https://github.com/Amethyst-szs/smo-lunakit/wiki/Custom-Stage-Support
    mCustomList->init(heap);

    mPrimQueue = new PrimitiveQueue(heap);  // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#primitives
    mPrimitiveSettings = new PrimMenuSettings(this);

    mTheme = new DevGuiTheme(this);  // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#themes
    mTheme->init();

    // Create all windows and home menu items
    createElements();

    // Load and read save data if it already exists
    mSaveData = new DevGuiSaveData(heap);  // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#save-data
    mSaveData->init(this);
    mSaveData->read();
}

void DevGuiManager::update() {
    // Check for enabling and disabling the window
    if (InputHelper::isHoldR() && InputHelper::isHoldZR() && InputHelper::isPressL()) {
        mIsActive = !mIsActive;
        if (mIsActive)
            mIsRequestCursorShow = true;

        Logger::log("Active state %s\n", mIsActive ? "Enabled" : "Disabled");
    }

    // Toggle display/hide of all anchored windows
    if (mIsActive && InputHelper::isPressStickL()) {
        mIsDisplayWindows = !mIsDisplayWindows;
        Logger::log("Window display %s\n", mIsDisplayWindows ? "Enabled" : "Disabled");
    }

    // This is run every frame, only actually saves if a save is queued and the timer hits zero
    mSaveData->trySave();

    // Note: Each window's update function runs even with the menu closed/inactive!
    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);
        entry->updateWin();
    }

    // Note: Each home menu item's update function runs even with the menu closed/inactive!
    for (int i = 0; i < mHomeMenuTabs.size(); i++) {
        auto* entry = mHomeMenuTabs.at(i);
        entry->updateMenu();
    }

    // Primitive renderering queue is drawn at this time
    mPrimQueue->render();
}

void DevGuiManager::updateDisplay() {
    // Show/hide the cursor if the window is opened/closed
    updateCursorState();

    if (!mIsActive)
        return;

    mPopupKeyboard->update();
    mDockSystem->update();
    mTheme->tryUpdateTheme();

    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);
        if (!entry->isActive() || (!mIsDisplayWindows))
            continue;

        ImGui::Begin(entry->getWindowName(), entry->getCloseInteractionPtr(), entry->getWindowFlags());

        entry->tryUpdateWinDisplay();

        ImGui::End();

        entry->updatePostDisplay();
    }

    // Load and draw all home menu tabs
    if (ImGui::BeginMainMenuBar()) {
        ImGui::SetWindowFontScale(1.5f);

        for (int i = 0; i < mHomeMenuTabs.size(); i++) {
            auto* entry = mHomeMenuTabs.at(i);
            if (entry->isDisplayInList() && ImGui::BeginMenu(entry->getMenuName())) {
                entry->updateMenuDisplay();

                ImGui::EndMenu();
            }
        }

        if (mSaveData->isSaveQueued()) {
            sead::FormatFixedSafeString<0x20> display("  Save %.00fs", mSaveData->getSaveQueueTime());
            if (ImGui::BeginMenu(display.cstr(), false))
                ImGui::EndMenu();
        }

        if (!mIsDisplayWindows && ImGui::BeginMenu("  Hidden! (L-Stick)", false))
            ImGui::EndMenu();

        if (InputHelper::isInputToggled() && ImGui::BeginMenu("  Controller (R+ZR+ZL)", false))
            ImGui::EndMenu();

        ImGui::EndMainMenuBar();
    }

    for (int i = 0; i < mHomeMenuTabs.size(); i++) {
        auto* entry = mHomeMenuTabs.at(i);
        entry->updatePostDisplay();
    }

    // Draw the demo window if the settings class has it enabled
    if (mIsDisplayImGuiDemo)
        ImGui::ShowDemoWindow();

    // Try loading the ImGui layout on first step now that everything is created
    // Reset the first step flag when complete!
    if (mIsFirstStep) {
        mSaveData->readImGuiLayout();
        mIsFirstStep = false;
    }
}

void DevGuiManager::updateCursorState() {
    if (!mIsActive)
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);

    if (mIsRequestCursorShow) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        mIsRequestCursorShow = false;
    }
}

template <class T>
void DevGuiManager::createWindow(const char* winName, bool isActiveByDefault) {
    T* window = new (mHeap) T(this, winName, isActiveByDefault);
    mWindows.pushBack(window);
}

template <class T>
void DevGuiManager::createWindow(const char* winName, bool isActiveByDefault, WindowGroup* group) {
    T* window = new (mHeap) T(this, winName, isActiveByDefault);
    mWindows.pushBack(window);
    group->registerWindow(window);
}

template <class T>
void DevGuiManager::createHomeMenuItem(const char* menuName, bool isDisplayInListByDefault) {
    T* home = new (mHeap) T(this, menuName, isDisplayInListByDefault);
    mHomeMenuTabs.pushBack(home);
}

WindowGroup* DevGuiManager::createWindowGroup(const char* groupName, u8 maxSize) {
    WindowGroup* g = new (mHeap) WindowGroup(this, groupName, maxSize);
    mWindowGroups.pushBack(g);
    return g;
}

WindowBase* DevGuiManager::getWindow(const char* sName) {
    for (WindowBase& win : mWindows) {
        if (al::isEqualString(win.getWindowName(), sName))
            return &win;
    }

    return nullptr;
}