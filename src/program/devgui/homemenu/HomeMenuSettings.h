#pragma once

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuSettings : public HomeMenuBase {
public:
    HomeMenuSettings(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenuDisplay() override;
private:

    void parameterEdit(const char* name, bool* value, bool isSave);
};