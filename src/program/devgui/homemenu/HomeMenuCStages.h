#pragma once

#include "cstages/CustomStage.h"
#include "cstages/CustomStageManager.h"

#include "game/GameData/GameDataHolderAccessor.h"

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuCStages : public HomeMenuBase {
public:
    HomeMenuCStages(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenuDisplay() override;

private:
    void drawResource(CustomStageResource* res);
    void drawCategory(CustomStageCategory* cat);
    void drawEntry(CustomStageEntry* ent);

    void warpToStage(GameDataHolderAccessor* data, const char* stageName);
};