#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuWorlds.h"

#include "al/util.hpp"

#include "game/GameData/GameDataFunction.h"
#include "game/Player/PlayerFunction.h"

#include "helpers/GetHelper.h"
#include "helpers/FunctionHelper.h"

#include "imgui.h"
#include "logger/Logger.hpp"

static WorldList* getWorldList(GameDataHolderAccessor accessor) {
//    Logger::log("Offset: %x\n", FunctionHelper::readLdrOffset("_ZN16GameDataFunction19getWorldScenarioNumE22GameDataHolderAccessori"));
    return *(WorldList**)((uintptr_t)accessor.mData + FunctionHelper::readLdrOffset("_ZN16GameDataFunction19getWorldScenarioNumE22GameDataHolderAccessori"));
}

HomeMenuWorlds::HomeMenuWorlds(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
    : HomeMenuBase(parent, menuName, isDisplayInListByDefault)
{}

void HomeMenuWorlds::updateMenuDisplay()
{
    StageScene* scene = tryGetStageScene();
    if(!scene) {
        mScenarioPicker = -1;
        ImGui::MenuItem("No stage is loaded!", nullptr, false, false);
        return;
    }

    GameDataHolderAccessor holder(scene);
    s32 worldID = GameDataFunction::getCurrentWorldId(holder);
    WorldListEntry* worldEntry = getWorldList(holder)->mWorldList.at(worldID);
    const char* worldName = getWorldList(holder)->getWorldDevelopName(worldID);

    // Draw the top components to select kindom and scenario
    drawKingdomPicker(worldName, scene, holder);
    if(GameDataFunction::isMainStage(holder))
        drawScenarioPicker(*worldEntry, scene, holder);

    if(addMenu("Sub-Areas")) {
        ImGui::BeginChild("Sub-Area Child", ImVec2(525, 325), false, ImGuiWindowFlags_NoBackground);

        for (auto &dbEntry: worldEntry->mStageNames) {
//            Logger::log("Stage name: %s\n", dbEntry.mStageName.cstr());
            bool isDemo = al::isEqualString(dbEntry.mStageCategory, "Demo");

            if(ImGui::MenuItem(dbEntry.mStageName.cstr(), dbEntry.mStageCategory.cstr(), false, !isDemo))
                warpToStage(holder, dbEntry.mStageName.cstr(), dbEntry.mUseScenario);
        }

        ImGui::EndChild();
        ImGui::EndMenu();
    }
}

inline void HomeMenuWorlds::drawKingdomPicker(const char* worldName, StageScene* scene, GameDataHolderAccessor holder)
{
    ImGui::SetNextItemWidth(140.f);
    if(ImGui::BeginCombo("Kingdom", worldName, ImGuiComboFlags_HeightLargest)) {
        ImGui::SetWindowFontScale(1.66f);

        for (auto &entry: getWorldList(holder)->mWorldList) {
            if(ImGui::Selectable(entry.mWorldDevelopName, false)) {
                warpToStage(holder, entry.mMainStageName, -1);
            }
        }

        ImGui::EndCombo();
    }
}

inline void HomeMenuWorlds::drawScenarioPicker(WorldListEntry& entry, StageScene* scene, GameDataHolderAccessor holder)
{
    PlayerActorBase* player = tryGetPlayerActor(scene);
    if(player && mScenarioPicker == -1)
        mScenarioPicker = GameDataFunction::getScenarioNo(player);
    
    ImGui::Text("Scenario (%s)", getScenarioType(entry, mScenarioPicker));

    ImGui::SetNextItemWidth(60.f);
    ImGui::DragInt("\n\0", &mScenarioPicker, 0.075f, 1, 15, nullptr, ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_NoInput);
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("Click and drag to change the scenario!\nClick load to reload the kingdom with this scenario");

    ImGui::SameLine();
    if(ImGui::Button(" Load "))
        warpToStage(holder, entry.mMainStageName, mScenarioPicker);
}

inline const char* HomeMenuWorlds::getScenarioType(WorldListEntry& entry, int scenario)
{
    if(scenario == entry.mClearMainScenario)
        return "Peace";
    if(scenario == entry.mEndingScenario)
        return "Post-game";
    if(scenario == entry.mMoonRockScenario)
        return "Moon Rock";

    return "Unknown";
}

void HomeMenuWorlds::warpToStage(GameDataHolderAccessor data, const char* stageName, int scenario)
{
    PlayerActorBase* player = tryGetPlayerActor();
    if(!player)
        return;
    
    if(PlayerFunction::isPlayerDeadStatus(player))
        return;
    
    ChangeStageInfo stageInfo(data.mData, "start", stageName, false, scenario, ChangeStageInfo::SubScenarioType::UNK);
    GameDataFunction::tryChangeNextStage(data, &stageInfo);
}