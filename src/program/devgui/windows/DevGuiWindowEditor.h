#pragma once

#include "imgui.h"

#include "program/devgui/windows/DevGuiWindowBase.h"
#include "program/devgui/DevGuiWindowConfig.h"

#include "program/devgui/categories/DevGuiCategoryBase.h"
#include "program/devgui/categories/DevGuiCategoryHealth.h"

class DevGuiWindowEditor : public DevGuiWindowBase {
public:
    DevGuiWindowEditor(const char* winName, sead::Heap* heap);

    void updateWin() override;
    void updateWinDisplay() override;
    void configImGuiStyle() override;
};