
/*
    - LunaKit Info Viewer Window -

    This window displays general information about various parts of the game
    Uses categories
*/

#pragma once

#include "imgui.h"

#include "program/devgui/DevGuiWindowConfig.h"
#include "program/devgui/windows/WindowBase.h"

#include "program/devgui/categories/CategoryBase.h"
#include "program/devgui/categories/info/CategoryInfPlayer.h"

class WindowInfo : public WindowBase {
public:
    WindowInfo(DevGuiManager* parent, const char* winName, bool active, sead::Heap* heap);
};