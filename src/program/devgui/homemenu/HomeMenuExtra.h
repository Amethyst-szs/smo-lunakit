#pragma once

#include "imgui.h"

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuExtra : public HomeMenuBase {
public:
    HomeMenuExtra(DevGuiManager* parent, const char* menuName, sead::Heap* heap);

    virtual void updateMenu();
};