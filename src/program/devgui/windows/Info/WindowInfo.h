
/*
    - LunaKit Info Viewer Window -

    This window displays general information about various parts of the game
    Uses categories

    https://github.com/Amethyst-szs/smo-lunakit/wiki#info-viewer
*/

#pragma once

#include "program/devgui/windows/WindowBase.h"

__attribute__((used)) static const char* infoWindowName = "Info Viewer";

class WindowInfo : public WindowBase {
public:
    WindowInfo(DevGuiManager* parent, const char* winName, bool isActiveByDefault);
};