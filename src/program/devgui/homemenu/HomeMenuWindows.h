#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuWindows : public HomeMenuBase {
public:
    HomeMenuWindows(DevGuiManager* parent, const char* menuName);

    virtual void updateMenu();

private:
    void setAnc(int type);
};