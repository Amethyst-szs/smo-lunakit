
/*
    - LunaKit Actor Browser Window -
*/

#pragma once

#include "imgui.h"

#include "program/devgui/windows/WindowBase.h"

class WindowActorBrowse : public WindowBase {
public:
    WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);

    void updateWin() override;
    bool tryUpdateWinDisplay() override;

private:
    void drawButtonHeader();
    void drawActorList(al::Scene* scene);
    void drawActorInfo();

    ImGuiWindowFlags mChildFlags = ImGuiWindowFlags_HorizontalScrollbar;
    const float mHeaderSize = 20.f;
};