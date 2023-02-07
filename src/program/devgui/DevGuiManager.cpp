#include "program/devgui/DevGuiManager.h"
#include "program/devgui/windows/DevGuiWindowBase.h"

SEAD_SINGLETON_DISPOSER_IMPL(DevGuiManager)
DevGuiManager::DevGuiManager() = default;
DevGuiManager::~DevGuiManager() = default;

void DevGuiManager::init(sead::Heap *heap)
{
    mWindows.allocBuffer(0x10, heap);
    mDevGuiHeap = heap;
    mIsActive = false;

    DevGuiWindowBase* newWindow = new DevGuiWindowBase("Temp Name");
    mWindows.pushBack(newWindow);

    for(DevGuiWindowBase entry : mWindows) {
        entry.init(heap);
    }
}

void DevGuiManager::update()
{
    for(DevGuiWindowBase entry : mWindows) {
        entry.updateWin();
    }
}

void DevGuiManager::updateDisplay()
{
    // ImGui::start();

    for(DevGuiWindowBase entry : mWindows) {
        entry.updateWinDisplay();
    }

    // ImGui::end();
}