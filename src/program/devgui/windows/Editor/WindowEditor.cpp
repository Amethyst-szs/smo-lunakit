#include "devgui/DevGuiManager.h"
#include "WindowEditor.h"

#include "program/devgui/categories/edit/CategoryHealth.h"
#include "program/devgui/categories/edit/CategoryCoins.h"
#include "program/devgui/categories/edit/CategorySpeed.h"
#include "program/devgui/categories/edit/CategoryWarp.h"
#include "program/devgui/categories/edit/CategoryOutfit.h"
#include "program/devgui/categories/edit/CategoryHomeShip.h"

WindowEditor::WindowEditor(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault)
{
    createCategory<CategoryHealth>("HP", "Edit the player's health");
    createCategory<CategoryCoins>("Coins", "Edit the player's coin count");
    createCategory<CategorySpeed>("Speed", "Edit the player's speed");
    createCategory<CategoryWarp>("Warp", "Save warp positions for player");
    createCategory<CategoryOutfit>("Outfit", "Change player's outfit quickly");
    createCategory<CategoryHomeShip>("Ship", "Edit Odyssey ship progression");
}