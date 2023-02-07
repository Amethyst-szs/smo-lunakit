#include "program/devgui/windows/DevGuiWindowBase.h"
#include "program/devgui/categories/DevGuiCategoryBase.h"

#include "imgui.h"

void DevGuiWindowBase::init(sead::Heap *heap)
{
    mCategories.allocBuffer(0x10, heap);
    mDevGuiHeap = heap;

    DevGuiCategoryBase* newCategory = new DevGuiCategoryBase("Temp Cat");
    mCategories.pushBack(newCategory);
}

void DevGuiWindowBase::updateWin()
{
    for(DevGuiCategoryBase entry : mCategories) {
        entry.updateWin();
    }
}

void DevGuiWindowBase::updateWinDisplay()
{
    ImGui::Begin(mWinName);
    ImGui::Text("Balls (WindowBase)");
    
    if(mCategories.size() > 0) {
        for (DevGuiCategoryBase entry : mCategories) {
            // ImGui draw category headers! 
        }
        
        mCategories.at(mCategoryIdx)->updateWinDisplay();
    }

    ImGui::End();
}