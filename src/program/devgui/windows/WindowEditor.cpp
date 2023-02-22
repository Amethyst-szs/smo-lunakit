#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowEditor.h"

WindowEditor::WindowEditor(DevGuiManager* parent, const char* winName, bool active, sead::Heap* heap)
    : WindowBase(parent, winName, active, heap)
{
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