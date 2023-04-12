#pragma once

#include "devgui/homemenu/HomeMenuBase.h"

#include "game/GameData/GameDataHolderAccessor.h"

class HomeMenuWorlds : public HomeMenuBase {
public:
    HomeMenuWorlds(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault);

    void updateMenuDisplay() override;

private:
    // Please clean up this code! There has got to be a cleaner way of implementing this!
    void drawDatabaseCategoryEX(GameDataHolderAccessor* data, WorldListEntry* entry);
    void drawDatabaseCategoryZone(GameDataHolderAccessor* data, WorldListEntry* entry);
    void drawDatabaseCategoryDemo(GameDataHolderAccessor* data, WorldListEntry* entry);
    void drawDatabaseCategoryOther(GameDataHolderAccessor* data, WorldListEntry* entry);

    bool isInCategory(const char* dbCat, const char* compare);

    void drawScenarioPicker(GameDataHolderAccessor* data, WorldListEntry* entry);
    void warpToStage(GameDataHolderAccessor* data, const char* stageName, int scenario);
};