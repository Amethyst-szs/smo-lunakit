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
    
    DevGuiWindowBase* newWindow = new (heap) DevGuiWindowBase("Temp Name", heap);
    mWindows.pushBack(newWindow);
}

void DevGuiManager::update()
{
    for(DevGuiWindowBase entry : mWindows) {
        entry.updateWin();
    }
}

void DevGuiManager::updateDisplay()
{
    for(DevGuiWindowBase entry : mWindows) {
        entry.updateWinDisplay();
    }
}