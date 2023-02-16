#pragma once

#include "imgui.h"

#include "game/GameData/GameDataHolder.h"
#include "game/GameData/GameDataFunction.h"
#include "game/Player/PlayerFunction.h"

#include "program/GetterUtil.h"

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuWorlds : public HomeMenuBase {
public:
    HomeMenuWorlds(DevGuiManager* parent, const char* menuName, sead::Heap* heap);

    virtual void updateMenu();
    // Unlike categories, these don't have a seperation between run and display since code is triggered once on input (or sets flags)

private:
    void drawDatabaseCategoryEX(GameDataHolderAccessor* data, WorldListEntry* entry);
    void drawDatabaseCategoryZone(GameDataHolderAccessor* data, WorldListEntry* entry);
    void drawDatabaseCategoryDemo(GameDataHolderAccessor* data, WorldListEntry* entry);
    void drawDatabaseCategoryOther(GameDataHolderAccessor* data, WorldListEntry* entry);

    bool isInCategory(const char* dbCat, const char* compare);

    void drawScenarioPicker(GameDataHolderAccessor* data, WorldListEntry* entry);
    void warpToStage(GameDataHolderAccessor* data, const char* stageName, int scenario);
};