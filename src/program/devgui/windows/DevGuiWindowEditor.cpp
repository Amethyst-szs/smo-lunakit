#include "program/devgui/windows/DevGuiWindowEditor.h"

DevGuiWindowEditor::DevGuiWindowEditor(const char* winName, sead::Heap* heap) : DevGuiWindowBase(winName, heap)
{
    // Setup window config
    mConfig.mSize = ImVec2(400, 800);

    // Player health edtior category
    DevGuiCategoryHealth* healthCat = new (heap) DevGuiCategoryHealth("Health", "Customize the player's health");
    mCategories.pushBack(healthCat);
}

void DevGuiWindowEditor::updateWin()
{
    DevGuiWindowBase::updateWin();
}

void DevGuiWindowEditor::updateWinDisplay()
{
    DevGuiWindowBase::updateWinDisplay();
}

void DevGuiWindowEditor::configImGuiStyle()
{
    DevGuiWindowBase::configImGuiStyle();
}