#include "program/devgui/DevGuiManager.h"

// This class is a singleton! It does not have a typical constructor
// This is class is created in GameSystemInit in main.cpp
// Access this class from anywhere using DevGuiManager::instance()->...
SEAD_SINGLETON_DISPOSER_IMPL(DevGuiManager)
DevGuiManager::DevGuiManager() = default;
DevGuiManager::~DevGuiManager() = default;

void DevGuiManager::createElements()
{
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);
    
    // Create all display windows
    createWindow<WindowMemoryManage>("Memory Manager", true);
    createWindow<WindowEditor>("Param Editor", true);
    createWindow<WindowInfo>("Info Viewer", true);
    createWindow<WindowActorBrowse>("Actor Browser", false);
    createWindow<WindowFPS>("FPS Window", true);
    createWindow<WindowLoadLog>("Load Log", false);

    // Create all home menu tabs
    createHomeMenuItem<HomeMenuFile>("File", true);
    createHomeMenuItem<HomeMenuSettings>("Settings", true);
    createHomeMenuItem<HomeMenuWindows>("Windows", true);
    createHomeMenuItem<HomeMenuPrims>("Prims", true);
    createHomeMenuItem<HomeMenuWorlds>("Kingdoms", true);
    createHomeMenuItem<HomeMenuCStages>("Stages", true);
    createHomeMenuItem<HomeMenuExtra>("Extras", true);
    createHomeMenuItem<HomeMenuUpdater>("Update!", false);

    // Create each popup window
    mPopupKeyboard = new PopupKeyboard();
}

void DevGuiManager::init(sead::Heap* heap)
{
    Logger::log("Initing DevGuiManager... (Version: %s)\n", GIT_VER);
    
    // Sets the DevGuiHeap to the heap passed in as an arg, along with setting the current scope to the heap
    mHeap = heap;
    sead::ScopedCurrentHeapSetter heapSetter(heap);

    // Allocate 0x10 (16) slots for windows and tabs at the top
    // Please don't increase these unless you REALLY need more space for some ungodly reason
    mWindows.allocBuffer(0x10, heap);
    mHomeMenuTabs.allocBuffer(0x10, heap);
    mDockSystem = new DevGuiDocking(this);

    mSettings = new DevGuiSettings(this); // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#settings

    mCustomList = new CustomStageManager(); // https://github.com/Amethyst-szs/smo-lunakit/wiki/Custom-Stage-Support
    mCustomList->init(heap);

    mPrimQueue = new PrimitiveQueue(heap); // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#primitives
    mPrimitiveSettings = new PrimMenuSettings(this);

    mTheme = new DevGuiTheme(this); // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#themes
    mTheme->init();

    // Create all windows and home menu items
    createElements();

    // Load and read save data if it already exists
    mSaveData = new DevGuiSaveData(heap); // https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#save-data
    mSaveData->init(this);
    mSaveData->read();
}

void DevGuiManager::update()
{
    // Check for enabling and disabling the window
    if (InputHelper::isHoldR() && InputHelper::isHoldZR() && InputHelper::isPressL()) {
        mIsActive = !mIsActive;
        if (mIsActive)
            mIsRequestCursorShow = true;

        Logger::log("Active state %s\n", mIsActive ? "enabled" : "disabled");
    }

    // Toggle display/hide of all anchored windows
    if(mIsActive && al::isPadTriggerPressLeftStick(-1)) {
        mIsDisplayWindows = !mIsDisplayWindows;
        Logger::log("window display %s\n", mIsDisplayWindows ? "enabled" : "disabled");
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

void DevGuiManager::updateDisplay()
{
    // Show/hide the cursor if the window is opened/closed
    updateCursorState();

    if(!mIsActive)
        return;
        
    mPopupKeyboard->update();
    mDockSystem->update();
    mTheme->tryUpdateTheme();

    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);
        if(!entry->isActive() || (!mIsDisplayWindows))
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

        if(mSaveData->isSaveQueued()) {
            sead::FormatFixedSafeString<0x20> display("  Save %.00fs", mSaveData->getSaveQueueTime());
            if(ImGui::BeginMenu(display.cstr(), false))
                ImGui::EndMenu();
        }

        if(!mIsDisplayWindows && ImGui::BeginMenu("  Hidden! (L-Stick)", false))
            ImGui::EndMenu();

        if(InputHelper::isInputToggled() && ImGui::BeginMenu("  Controller (R+ZR+ZL)", false))
            ImGui::EndMenu();

        ImGui::EndMainMenuBar();
    }

    for (int i = 0; i < mHomeMenuTabs.size(); i++) {
        auto* entry = mHomeMenuTabs.at(i);
        entry->updatePostDisplay();
    }

    // Draw the demo window if the settings class has it enabled
    if(mIsDisplayImGuiDemo)
        ImGui::ShowDemoWindow();

    // Try loading the ImGui layout on first step now that everything is created
    // Reset the first step flag when complete!
    if (mIsFirstStep) {
        mSaveData->readImGuiLayout();
        mIsFirstStep = false;
    }
}

void DevGuiManager::updateCursorState()
{
    if (!mIsActive)
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);

    if (mIsRequestCursorShow) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        mIsRequestCursorShow = false;
    }
}

template <class T>
void DevGuiManager::createWindow(const char* winName, bool isActiveByDefault)
{
    T* window = new (mHeap) T(this, winName, isActiveByDefault);
    mWindows.pushBack(window);
}

template <class T>
void DevGuiManager::createHomeMenuItem(const char* menuName, bool isDisplayInListByDefault)
{
    T* home = new (mHeap) T(this, menuName, isDisplayInListByDefault);
    mHomeMenuTabs.pushBack(home);
}