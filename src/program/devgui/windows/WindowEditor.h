#pragma once

#include "imgui.h"

#include "program/devgui/DevGuiWindowConfig.h"
#include "program/devgui/windows/WindowBase.h"

#include "program/devgui/categories/CategoryBase.h"
#include "program/devgui/categories/CategoryHealth.h"
#include "program/devgui/categories/CategoryPrimitive.h"
#include "program/devgui/categories/CategoryOutfit.h"
#include "program/devgui/categories/CategoryHomeShip.h"

class WindowEditor : public WindowBase {
public:
    WindowEditor(DevGuiManager* parent, const char* winName, sead::Heap* heap);

    void updateWin() override;
    void updateWinDisplay() override;
    void configImGuiStyle() override;
};