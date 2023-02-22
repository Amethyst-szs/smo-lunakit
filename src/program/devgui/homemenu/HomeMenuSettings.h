#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "devgui/savedata/DevGuiSettings.h"
#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuSettings : public HomeMenuBase {
public:
    HomeMenuSettings(DevGuiManager* parent, const char* menuName, sead::Heap* heap);

    virtual void updateMenu();
private:

    void parameterEdit(const char* name, bool* value, bool isSave);
};