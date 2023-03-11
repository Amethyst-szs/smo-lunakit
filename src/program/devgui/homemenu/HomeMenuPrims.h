#pragma once

#include "imgui.h"

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuPrims : public HomeMenuBase {
public:
    HomeMenuPrims(DevGuiManager* parent, const char* menuName);

    void updateMenu() override;
    void updateMenuDisplay() override;

private:
    bool mIsEnableRendering = false;
};