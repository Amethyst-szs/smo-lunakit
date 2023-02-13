#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowEditor.h"

WindowEditor::WindowEditor(DevGuiManager* parent, const char* winName, sead::Heap* heap)
    : WindowBase(parent, winName, heap)
{
    // Setup window config
    mConfig.mTrans = ImVec2(853, 19);
    mConfig.mSize = ImVec2(427, 220);

    mConfig.mWindowFlags |= ImGuiWindowFlags_NoCollapse;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoMove;
    mConfig.mWindowFlags |= ImGuiWindowFlags_NoResize;

    // Primitive renderer category
    CategoryPrimitive* primitiveCat = new (heap) CategoryPrimitive("Prims", "Customize primitive rendering", heap);
    mCategories.pushBack(primitiveCat);

    // Player health edtior category
    CategoryHealth* healthCat = new (heap) CategoryHealth("HP", "Edit the player's health", heap);
    mCategories.pushBack(healthCat);

    // Outfit category
    CategoryOutfit* outfitCat = new (heap) CategoryOutfit("Outfit", "Change player's outfit quickly", heap);
    mCategories.pushBack(outfitCat);

    // Home ship (Odyssey ship) category
    CategoryHomeShip* homeShipCat = new (heap) CategoryHomeShip("Ship", "Edit Odyssey ship progression", heap);
    mCategories.pushBack(homeShipCat);
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