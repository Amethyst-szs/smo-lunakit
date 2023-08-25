#include "program/devgui/categories/edit/CategoryOutfit.h"

#include "game/GameData/GameDataHolder.h"
#include "game/GameData/GameDataFunction.h"

#include "helpers/GetHelper.h"
#include "helpers.h"

#include "imgui.h"

CategoryOutfit::CategoryOutfit(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap)
{
    mTotalBody = IM_ARRAYSIZE(bodyNames);
    mTotalCap = IM_ARRAYSIZE(capNames);

    mComboFlags |= ImGuiComboFlags_HeightRegular;
}

void CategoryOutfit::updateCat()
{
    if(!mIsOverride)
        return;
    
    GameDataHolder* holder = tryGetGameDataHolder();
    if(!holder)
        return;

    holder->mGameDataFile->mBodyName = mTargetBody;
    holder->mGameDataFile->mCapName = mTargetCap;

    if(mIsReloadScene) {
        mIsReloadScene = false;
        StageScene* scene = tryGetStageScene();
        if(!scene)
            return;
        
        ChangeStageInfo stageInfo(holder, "start", GameDataFunction::getCurrentStageName(scene->mGameDataHolder), false, -1, ChangeStageInfo::SubScenarioType::UNK);
        GameDataFunction::tryChangeNextStage(scene->mGameDataHolder, &stageInfo);
    }
}

void CategoryOutfit::updateCatDisplay()
{
    CategoryBase::updateCatDisplay();

    if (ImGui::Checkbox("Edit Player Outfit", &mIsOverride)) {
        GameDataHolder* holder = tryGetGameDataHolder();
        if(holder) {
            mTargetBody = holder->mGameDataFile->mBodyName.cstr();
            mTargetCap = holder->mGameDataFile->mCapName.cstr();
        }
    }

    if(!mIsOverride)
        return;

    drawDropdown("Body", bodyNames, mTotalBody, &mTargetBody);
    drawDropdown("Cap", capNames, mTotalCap, &mTargetCap);

    if(isInStageScene() && ImGui::Button("Reload Scene"))
        mIsReloadScene = true;
}

void CategoryOutfit::drawDropdown(const char* header, const char* options[], const int totalOptions, const char** output)
{
    if(ImGui::BeginCombo(header, *output, mComboFlags)) {
        for(int n = 0; n < mTotalCap; n++) {
            bool is_selected = (*output == options[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(options[n], is_selected))
                *output = options[n];
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }

        ImGui::EndCombo();
    }
}