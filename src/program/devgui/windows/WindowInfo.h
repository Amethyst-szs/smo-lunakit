
/*
    - LunaKit Info Viewer Window -

    This window displays general information about various parts of the game
    Uses categories

    https://github.com/Amethyst-szs/smo-lunakit/wiki#info-viewer
*/

#pragma once

#include "imgui.h"

#include "program/devgui/windows/WindowBase.h"

#include "program/devgui/categories/CategoryBase.h"
#include "program/devgui/categories/info/CategoryInfPlayer.h"

class WindowInfo : public WindowBase {
public:
    WindowInfo(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);
};