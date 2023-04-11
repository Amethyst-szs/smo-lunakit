#pragma once

#include "devgui/homemenu/HomeMenuBase.h"

#include "logger/Logger.hpp"

#include "imgui.h"
#include "imgui_internal.h"

#include "update/UpdateHandler.h"

class HomeMenuExtra : public HomeMenuBase {
public:
    HomeMenuExtra(DevGuiManager* parent, const char* menuName);

    virtual void updateMenu();
    virtual void updateMenuDisplay();

private:
    bool mIsFirstStep = true;
    bool mIsLoggerDisabled = false;

    bool mIsIPKeyboardOpen = false;
    bool mIsPortKeyboardOpen = false;
    const char* mKeyboardString = nullptr;

    sead::FixedSafeString<0x10> mIPString;
    sead::FixedSafeString<0x6> mPortString;
    
    uint mNewPort = 0;
};