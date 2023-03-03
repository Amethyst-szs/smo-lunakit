
/*
    - LunaKit Parameter Editor Window -

    This window is responsible for allowing editing several different things about the player, save, and world
    Uses categories!
*/

#pragma once

#include "imgui.h"

#include "program/devgui/windows/WindowBase.h"

#include "program/devgui/categories/CategoryBase.h"
#include "program/devgui/categories/edit/CategoryHealth.h"
#include "program/devgui/categories/edit/CategoryPrimitive.h"
#include "program/devgui/categories/edit/CategoryOutfit.h"
#include "program/devgui/categories/edit/CategoryHomeShip.h"

class WindowEditor : public WindowBase {
public:
    WindowEditor(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);
};