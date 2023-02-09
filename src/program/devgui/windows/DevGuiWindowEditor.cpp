#include "program/devgui/windows/DevGuiWindowEditor.h"

DevGuiWindowEditor::DevGuiWindowEditor(const char* winName, sead::Heap* heap) : DevGuiWindowBase(winName, heap)
{
    // Setup window config
    mConfig.mTrans = ImVec2(1280 / 1.5, 0); // Anchor point (top-left) positioned at top middle of screen
    mConfig.mSize = ImVec2(1280 / 3, 200);

    mConfig.mWindowFlags |= ImGuiWindowFlags_NoMove;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoResize;

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