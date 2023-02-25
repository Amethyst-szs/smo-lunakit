#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowEditor.h"

WindowEditor::WindowEditor(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages)
{
    // Primitive renderer category
    CategoryPrimitive* primitiveCat = new (mDevGuiHeap) CategoryPrimitive("Prims", "Customize primitive rendering", mDevGuiHeap);
    mCategories.pushBack(primitiveCat);

    // Player health edtior category
    CategoryHealth* healthCat = new (mDevGuiHeap) CategoryHealth("HP", "Edit the player's health", mDevGuiHeap);
    mCategories.pushBack(healthCat);

    // Outfit category
    CategoryOutfit* outfitCat = new (mDevGuiHeap) CategoryOutfit("Outfit", "Change player's outfit quickly", mDevGuiHeap);
    mCategories.pushBack(outfitCat);

    // Home ship (Odyssey ship) category
    CategoryHomeShip* homeShipCat = new (mDevGuiHeap) CategoryHomeShip("Ship", "Edit Odyssey ship progression", mDevGuiHeap);
    mCategories.pushBack(homeShipCat);
}