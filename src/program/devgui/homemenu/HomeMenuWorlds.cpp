#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuWorlds.h"

HomeMenuWorlds::HomeMenuWorlds(DevGuiManager* parent, const char* menuName)
    : HomeMenuBase(parent, menuName)
{}

void HomeMenuWorlds::updateMenuDisplay()
{
    GameDataHolderAccessor* holder = tryGetGameDataHolderAccess();
    if(!holder) {
        ImGui::MenuItem("World List does not exist yet!");
        return;
    }

    for (auto &entry: holder->mData->mWorldList->mWorldList) {
        if (addMenu(entry.mMainStageName)) {
            if(ImGui::MenuItem("Warp to World (Post-Rock)"))
                warpToStage(holder, entry.mMainStageName, entry.mMoonRockScenario);

            if(ImGui::BeginMenu("Warp to Scenario"))
                drawScenarioPicker(holder, &entry);

            if (ImGui::BeginMenu("Quest Info")) {
                for (int i = 0; i < entry.mQuestInfoCount; ++i) {
                    char item[0x20];
                    sprintf(item, "Q %d Scenario %d", i, entry.mMainQuestIndexes[i]);
                    ImGui::MenuItem(item, NULL, false, false);
                }
                
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Sub Areas Stages"))
                drawDatabaseCategoryEX(holder, &entry);

            if (ImGui::BeginMenu("Zones"))
                drawDatabaseCategoryZone(holder, &entry);

            if (ImGui::BeginMenu("Cutscenes"))
                drawDatabaseCategoryDemo(holder, &entry);

            if (ImGui::BeginMenu("Other Stages"))
                drawDatabaseCategoryOther(holder, &entry);

            ImGui::EndMenu();
        }
    }
}

void HomeMenuWorlds::drawDatabaseCategoryEX(GameDataHolderAccessor* data, WorldListEntry* entry)
{
    for (auto &dbEntry: entry->mStageNames) {
        const char* dbCat = dbEntry.mStageCategory.cstr();
        if(!isInCategory(dbCat, "ExStage") && !isInCategory(dbCat, "MoonExStage"))
            continue;

        if(ImGui::MenuItem(dbEntry.mStageName.cstr()))
            warpToStage(data, dbEntry.mStageName.cstr(), -1);
    }

    ImGui::EndMenu();
}

void HomeMenuWorlds::drawDatabaseCategoryZone(GameDataHolderAccessor* data, WorldListEntry* entry)
{
    for (auto &dbEntry: entry->mStageNames) {
        const char* dbCat = dbEntry.mStageCategory.cstr();
        if(!isInCategory(dbCat, "Zone"))
            continue;

        if(ImGui::MenuItem(dbEntry.mStageName.cstr()))
            warpToStage(data, dbEntry.mStageName.cstr(), -1);
    }

    ImGui::EndMenu();
}

void HomeMenuWorlds::drawDatabaseCategoryDemo(GameDataHolderAccessor* data, WorldListEntry* entry)
{
    for (auto &dbEntry: entry->mStageNames) {
        const char* dbCat = dbEntry.mStageCategory.cstr();
        if(!isInCategory(dbCat, "Demo"))
            continue;

        ImGui::MenuItem(dbEntry.mStageName.cstr(), NULL, false, false);
    }

    ImGui::EndMenu();
}

void HomeMenuWorlds::drawDatabaseCategoryOther(GameDataHolderAccessor* data, WorldListEntry* entry)
{
    for (auto &dbEntry: entry->mStageNames) {
        const char* dbCat = dbEntry.mStageCategory.cstr();
        if(isInCategory(dbCat, "ExStage") || isInCategory(dbCat, "MoonExStage") || isInCategory(dbCat, "Zone") || isInCategory(dbCat, "Demo") || isInCategory(dbCat, "MainStage"))
            continue;

        if(ImGui::MenuItem(dbEntry.mStageName.cstr(), dbCat))
            warpToStage(data, dbEntry.mStageName.cstr(), -1);
    }

    ImGui::EndMenu();
}

bool HomeMenuWorlds::isInCategory(const char* dbCat, const char* compare)
{
    return al::isEqualString(dbCat, compare);
}

void HomeMenuWorlds::drawScenarioPicker(GameDataHolderAccessor* data, WorldListEntry* entry)
{
    for(int i = 1; i <= 15; i++) {
        char buttonLabel[0x15];

        if(i == entry->mClearMainScenario)
            sprintf(buttonLabel, "Scen %i (Clear)", i);
        else if(i == entry->mEndingScenario)
            sprintf(buttonLabel, "Scen %i (Ending)", i);
        else if(i == entry->mMoonRockScenario)
            sprintf(buttonLabel, "Scen %i (Moon Rock)", i);
        else
            sprintf(buttonLabel, "Scen %i", i);

        if(ImGui::MenuItem(buttonLabel))
            warpToStage(data, entry->mMainStageName, i);
    }

    ImGui::EndMenu();
}

void HomeMenuWorlds::warpToStage(GameDataHolderAccessor* data, const char* stageName, int scenario)
{
    PlayerActorBase* player = tryGetPlayerActor();
    if(!player)
        return;
    
    if(PlayerFunction::isPlayerDeadStatus(player))
        return;
    
    ChangeStageInfo stageInfo(data->mData, "start", stageName, false, scenario, ChangeStageInfo::SubScenarioType::UNK);
    GameDataFunction::tryChangeNextStage(*data, &stageInfo);
}