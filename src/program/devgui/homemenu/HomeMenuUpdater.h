#pragma once

#include "sead/heap/seadHeap.h"

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
    void interfaceFailedDownload();
    void interfaceFailedSDCard();
    void interfaceComplete();

    bool mIsOpenInterface = false;
    bool mIsDisplayingInterface = false;

    bool mIsStartInstall = false;

    const float mInterfaceBorder = 25.f;
};