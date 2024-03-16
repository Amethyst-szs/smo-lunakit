#pragma once

#include "nn/types.h"
#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuExtra : public HomeMenuBase {
public:
    HomeMenuExtra(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenu() override;
    void updateMenuDisplay() override;

private:
    bool mIsFirstStep = true;
    bool mIsLoggerDisabled = false;

    bool mIsIPKeyboardOpen = false;
    bool mIsPortKeyboardOpen = false;
    const char* mKeyboardString = nullptr;

    sead::FixedSafeString<0x10> mIPString;
    sead::FixedSafeString<0x6> mPortString;
    
    u32 mNewPort = 0;
};
