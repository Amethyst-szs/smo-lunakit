#pragma once

#include "imgui.h"

#include "game/SaveData/SaveDataAccessFunction.h"

#include "devgui/homemenu/HomeMenuBase.h"

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
    HomeMenuFile(DevGuiManager* parent, const char* menuName, sead::Heap* heap);

    virtual void updateMenu();
    // Unlike categories, these don't have a seperation between run and display since code is triggered once on input (or sets flags)

private:
    SaveFileIdx selectSaveFile();
};