#pragma once

#include "devgui/homemenu/HomeMenuBase.h"

#include "game/GameData/GameDataHolderAccessor.h"
#include "game/StageScene/StageScene.h"

class HomeMenuWorlds : public HomeMenuBase {
public:
    HomeMenuWorlds(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenuDisplay() override;

private:
    inline void drawKingdomPicker(const char* worldName, StageScene* scene, GameDataHolderAccessor holder);
    inline void drawScenarioPicker(WorldListEntry& entry, StageScene* scene, GameDataHolderAccessor holder);

    inline const char* getScenarioType(WorldListEntry& entry, int scenario);

    void warpToStage(GameDataHolderAccessor data, const char* stageName, int scenario);

    int mScenarioPicker = -1;
};