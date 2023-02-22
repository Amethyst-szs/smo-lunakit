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

void DevGuiManager::init(sead::Heap* heap)
{
    Logger::log("Initing DevGuiManager... (Version: %s)\n", LUNAKITVERSION);
    
    // Sets the DevGuiHeap to the heap passed in as an arg, along with setting the current scope to the heap
    mDevGuiHeap = heap;
    sead::ScopedCurrentHeapSetter heapSetter(heap);

    // LunaKit is not active by default
    mIsActive = false;

    // Allocate 0x10 (16) slots for windows and tabs at the top
    // Please don't increase these unless you REALLY need more space for some ungodly reason
    mWindows.allocBuffer(0x10, mDevGuiHeap);
    mHomeMenuTabs.allocBuffer(0x10, mDevGuiHeap);

    // Creates the settings class, accessed by various functions and set by HomeMenuSettings
    mSettings = new DevGuiSettings(this, heap);

    // Creates a theme class and loads in the themes from the SD card themes folder
    mTheme = new DevGuiTheme(this);
    mTheme->init();

    // Creates the custom stage manager and loads in the custom stage information from the SD card CustomStages folder
    mCustomList = new CustomStageManager();
    mCustomList->init(heap);
    
    // Create all display windows

    WindowMemoryManage* memWindow = new WindowMemoryManage(this, "LunaKit Memory Manager", true, mDevGuiHeap);
    mWindows.pushBack(memWindow);

    WindowEditor* editorWindow = new WindowEditor(this, "LunaKit Param Editor", true, mDevGuiHeap);
    mWindows.pushBack(editorWindow);

    WindowInfo* infoWindow = new WindowInfo(this, "LunaKit Info Viewer", true, mDevGuiHeap);
    mWindows.pushBack(infoWindow);

    WindowFPS* fpsWindow = new WindowFPS(this, "FPS Window", true, mDevGuiHeap);
    mWindows.pushBack(fpsWindow);

    // Create all home menu tabs
    HomeMenuFile* homeFile = new HomeMenuFile(this, "File", mDevGuiHeap);
    mHomeMenuTabs.pushBack(homeFile);

    HomeMenuSettings* homeSetting = new HomeMenuSettings(this, "Settings", mDevGuiHeap);
    mHomeMenuTabs.pushBack(homeSetting);

    HomeMenuWindows* homeWindows = new HomeMenuWindows(this, "Windows", mDevGuiHeap);
    mHomeMenuTabs.pushBack(homeWindows);

    HomeMenuWorlds* homeWorld = new HomeMenuWorlds(this, "Kingdoms", mDevGuiHeap);
    mHomeMenuTabs.pushBack(homeWorld);

    HomeMenuCStages* homeCStages = new HomeMenuCStages(this, "Stages", mDevGuiHeap);
    mHomeMenuTabs.pushBack(homeCStages);

    HomeMenuExtra* homeExtra = new HomeMenuExtra(this, "Extras", mDevGuiHeap);
    mHomeMenuTabs.pushBack(homeExtra);

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

    mTheme->tryUpdateTheme();

    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);
        if(!entry->isActive() || (entry->isInAnchorList() && !mIsDisplayAnchorWindows))
            continue;

        ImGui::Begin(entry->getWindowName(), entry->getCloseInteractionPtr(), entry->getWindowConfig()->mWindowFlags);

        if(mIsAnchorChange) {
            entry->setupAnchor(totalAnchorWin, curAnchorWin);
            curAnchorWin++;
        }

        entry->tryUpdateWinDisplay();
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

void DevGuiManager::updateNoclip()
{
    PlayerActorBase* player = tryGetPlayerActor();

    if(!player)
        return;
    
    bool isNoclip = mSettings->getStateByName("Noclip");

    if(!isNoclip && !rs::isActiveDemo(player))
        al::onCollide(player);

    if(!isNoclip)
        return;

    static float speed = 25.0f;
    static float speedMax = 150.0f;
    static float vspeed = 20.0f;
    static float speedGain = 0.0f;

    sead::Vector3f *playerPos = al::getTransPtr(player);
    sead::Vector3f *cameraPos = al::getCameraPos(player, 0);
    sead::Vector2f *leftStick = al::getLeftStick(-1);

    // Its better to do this here because loading zones reset this.
    al::offCollide(player);
    al::setVelocityZero(player);

    // Mario slightly goes down even when velocity is 0. This is a hacky fix for that.
    playerPos->y += 1.4553f;

    float d = sqrt(al::powerIn(playerPos->x - cameraPos->x, 2) + (al::powerIn(playerPos->z - cameraPos->z, 2)));
    float vx = ((speed + speedGain) / d) * (playerPos->x - cameraPos->x);
    float vz = ((speed + speedGain) / d) * (playerPos->z - cameraPos->z);

    if (!al::isPadHoldZR(-1)) {
        playerPos->x -= leftStick->x * vz;
        playerPos->z += leftStick->x * vx;

        playerPos->x += leftStick->y * vx;
        playerPos->z += leftStick->y * vz;

        if (al::isPadHoldX(-1)) speedGain -= 0.5f;
        if (al::isPadHoldY(-1)) speedGain += 0.5f;
        if (speedGain <= 0.0f) speedGain = 0.0f;
        if (speedGain >= speedMax) speedGain = speedMax;

        if (al::isPadHoldZL(-1) || al::isPadHoldA(-1)) playerPos->y -= (vspeed + speedGain / 6);
        if (al::isPadHoldB(-1)) playerPos->y += (vspeed + speedGain / 6);
    }
}

int DevGuiManager::calcTotalAnchoredWindows()
{
    int total = 0;
    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);

        if(*(entry->getActiveState()) && entry->isInAnchorList())
            total++;
    }

    return total;
}