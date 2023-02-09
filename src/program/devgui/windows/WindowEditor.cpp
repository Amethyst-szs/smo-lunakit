#include "program/devgui/windows/WindowEditor.h"

WindowEditor::WindowEditor(const char* winName, sead::Heap* heap)
    : WindowBase(winName, heap)
{
    // Setup window config
    mConfig.mTrans = ImVec2(1280 / 1.5, 0); // Anchor point (top-left) positioned at top middle of screen
    mConfig.mSize = ImVec2(1280 / 3, 220);

    mConfig.mWindowFlags |= ImGuiWindowFlags_NoMove;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoResize;

    // Player health edtior category
    CategoryHealth* healthCat = new (heap) CategoryHealth("HP", "Edit the player's health");
    mCategories.pushBack(healthCat);

    // Primitive renderer category
    CategoryPrimitive* primitiveCat = new (heap) CategoryPrimitive("Prims", "Customize primitive rendering");
    mCategories.pushBack(primitiveCat);
}

void WindowEditor::updateWin()
{
    WindowBase::updateWin();
}

void WindowEditor::updateWinDisplay()
{
    WindowBase::updateWinDisplay();
}

void WindowEditor::configImGuiStyle()
{
    WindowBase::configImGuiStyle();
}