#pragma once

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuWindows : public HomeMenuBase {
public:
    HomeMenuWindows(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenuDisplay() override;

private:
    void opacitySetting(const char* label, float opacity);
};