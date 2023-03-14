#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowEditor.h"

WindowEditor::WindowEditor(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages)
{
    createCategory<CategoryPrimitive>("Prims", "Customize primitive rendering");
    createCategory<CategoryHealth>("HP", "Edit the player's health");
    createCategory<CategoryCoins>("Coins", "Edit the player's coin count");
    createCategory<CategorySpeed>("Speed", "Edit the player's speed");
    createCategory<CategoryOutfit>("Outfit", "Change player's outfit quickly");
    createCategory<CategoryHomeShip>("Ship", "Edit Odyssey ship progression");
}