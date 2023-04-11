#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "devgui/settings/DevGuiSettings.h"
#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuSettings : public HomeMenuBase {
public:
    HomeMenuSettings(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenuDisplay() override;
private:

    void parameterEdit(const char* name, bool* value, bool isSave);
};