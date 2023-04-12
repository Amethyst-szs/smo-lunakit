#pragma once

#include "devgui/homemenu/HomeMenuBase.h"

#include "game/GameData/GameDataHolder.h"

enum SaveFileIdx {
    NONE = -1,
    FILE1 = 0,
    FILE2 = 1,
    FILE3 = 2,
    FILE4 = 3,
    FILE5 = 4,
    MAX_SIZE
};

class HomeMenuFile : public HomeMenuBase {
public:
    HomeMenuFile(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenuDisplay() override;

private:
    SaveFileIdx selectSaveFile(GameDataHolder* holder, bool isAllowCurrentSave);
};