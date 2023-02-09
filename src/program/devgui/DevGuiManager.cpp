#include "program/devgui/DevGuiManager.h"

SEAD_SINGLETON_DISPOSER_IMPL(DevGuiManager)
DevGuiManager::DevGuiManager() = default;
DevGuiManager::~DevGuiManager() = default;

void DevGuiManager::init(sead::Heap* heap)
{
    mWindows.allocBuffer(0x10, heap);
    mDevGuiHeap = heap;
    mIsActive = false;

    WindowEditor* editorWindow = new (heap) WindowEditor("LunaKit Param Editor", heap);
    mWindows.pushBack(editorWindow);
}

void DevGuiManager::update()
{
    // Check for enabling and disabling the window
    if (al::isPadHoldR(-1) && al::isPadHoldZR(-1) && al::isPadTriggerL(-1)) {
        mIsActive = !mIsActive;
        if (mIsActive)
            mIsFirstStep = true;
    }

    // Note: Each window's update function runs even with the menu closed/inactive!
    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);
        entry->updateWin();
    }
}

void DevGuiManager::updateDisplay()
{
    // Setup mouse cursor state
    if (!mIsActive) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_None);
        return;
    }

    if (mIsFirstStep)
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);

    // Load and draw all windows
    for (int i = 0; i < mWindows.size(); i++) {
        auto* entry = mWindows.at(i);
        entry->updateWinDisplay();
    }

    // Reset the first step flag when complete!
    if (mIsFirstStep)
        mIsFirstStep = false;
}