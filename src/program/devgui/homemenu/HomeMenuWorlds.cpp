#include "program/devgui/homemenu/HomeMenuWorlds.h"

HomeMenuWorlds::HomeMenuWorlds(const char* menuName, sead::Heap* heap)
    : HomeMenuBase(menuName, heap)
{}

void HomeMenuWorlds::updateMenu()
{
    GameDataHolderAccessor* holder = tryGetGameDataHolderAccess();
    if(!holder) {
        ImGui::MenuItem("World List does not exist yet!");
        return;
    }

    bool isInGame = isInStageScene();

    for (auto &entry: holder->mData->mWorldList->mWorldList) {
        if (ImGui::BeginMenu(entry.mMainStageName)) {
            if (isInGame) {
                if(ImGui::MenuItem("Warp to World (Post-Rock)"))
                    warpToStage(holder, entry.mMainStageName, entry.mMoonRockScenario);

                if(ImGui::BeginMenu("Warp to Scenario"))
                    drawScenarioPicker(holder, &entry);
            }

            if (ImGui::BeginMenu("Quest Info")) {
                for (int i = 0; i < entry.mQuestInfoCount; ++i) {
                    char item[0x20];
                    sprintf(item, "Q %d Scenario %d", i, entry.mMainQuestIndexes[i]);
                    ImGui::MenuItem(item, NULL, false, false);
                }
                
                ImGui::EndMenu();
            }

            // if (ImGui::CollapsingHeader("Database Entries")) {
            //     for (auto &dbEntry: entry.mStageNames) {
            //         if (ImGui::TreeNode(dbEntry.mStageName.cstr())) {
            //             ImGui::BulletText("Stage Category: %s", dbEntry.mStageCategory.cstr());
            //             ImGui::BulletText("Stage Use Scenario: %d", dbEntry.mUseScenario);

            //             if (isInGame) {
            //                 ImGui::Bullet();
            //                 if (ImGui::SmallButton("Warp to Stage")) {
            //                     ChangeStageInfo stageInfo(gameSeq->mGameDataHolder.mData, "start", dbEntry.mStageName.cstr(), false, scenarioSlide, ChangeStageInfo::SubScenarioType::UNK);
            //                     GameDataFunction::tryChangeNextStage(gameSeq->mGameDataHolder, &stageInfo);
            //                 }
            //             }

            //             ImGui::TreePop();
            //         }
            //     }
            // }

            ImGui::EndMenu();
        }
    }
    // ImGui::MenuItem("Amethyst-szs", "LunaKit Dev", false, false);
    // ImGui::MenuItem("CraftyBoss", "SMO ExLaunch Base, ImGui, World List", false, false);
    // ImGui::MenuItem("Mars", "Referenced TAS Mod", false, false);
    // ImGui::MenuItem("ExLaunch", "", false, false);
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
    ChangeStageInfo stageInfo(data->mData, "start", stageName, false, scenario, ChangeStageInfo::SubScenarioType::UNK);
    GameDataFunction::tryChangeNextStage(*data, &stageInfo);
}