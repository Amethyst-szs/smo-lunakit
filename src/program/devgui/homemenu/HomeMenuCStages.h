#pragma once

#include "imgui.h"

#include "game/Player/PlayerFunction.h"

#include "cstages/CustomStage.h"
#include "cstages/CustomStageManager.h"

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuCStages : public HomeMenuBase {
public:
    HomeMenuCStages(DevGuiManager* parent, const char* menuName, sead::Heap* heap);

    virtual void updateMenu();

private:
    void drawResource(CustomStageResource* res);
    void drawCategory(CustomStageCategory* cat);
    void drawEntry(CustomStageEntry* ent);

    void warpToStage(GameDataHolderAccessor* data, const char* stageName);
};