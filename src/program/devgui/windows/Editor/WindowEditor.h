
/*
    - LunaKit Parameter Editor Window -

    This window is responsible for allowing editing several different things about the player, save, and world
    Uses categories!

    https://github.com/Amethyst-szs/smo-lunakit/wiki#parameter-editor
*/

#pragma once

#include "program/devgui/windows/WindowBase.h"

__attribute__((used)) static const char* paramEditorWindowName = "Param Editor";

class WindowEditor : public WindowBase {
public:
    WindowEditor(DevGuiManager* parent, const char* winName, bool isActiveByDefault);
};