#pragma once

#include "imgui.h"

#include "devgui/homemenu/HomeMenuBase.h"

#include "update/UpdateHandler.h"

class HomeMenuUpdater : public HomeMenuBase {
public:
    HomeMenuUpdater(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenu() override;
    void updateMenuDisplay() override;
    void updatePostDisplay() override;

private:
    void interfaceHeader(UpdateHandler* update);
    void interfaceSetup();

    bool mIsOpenInterface = false;
    bool mIsDisplayingInterface = false;

    const float mInterfaceBorder = 25.f;
};