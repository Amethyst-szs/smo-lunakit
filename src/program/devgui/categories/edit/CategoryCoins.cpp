#include "program/devgui/categories/edit/CategoryCoins.h"
#include "game/StageScene/StageSceneLayout.h"
#include "helpers/GetHelper.h"

#include "imgui.h"

CategoryCoins::CategoryCoins(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap)
{
}

void CategoryCoins::updateCat()
{
    if (mIsOverrideCoins) {
        StageScene* scene = tryGetStageScene();
        GameDataHolder* holder = tryGetGameDataHolder(scene);

        if(!holder)
            return;

        holder->mGameDataFile->mCoinCount = mTargetCoins;
        if(scene)
            scene->mStageSceneLayout->coinCounter->updateCountImmidiate();
    }
}

void CategoryCoins::updateCatDisplay()
{
    CategoryBase::updateCatDisplay();

    GameDataHolder* holder = tryGetGameDataHolder();
    if(!holder)
        return;

    if (ImGui::Checkbox("Edit Coins", &mIsOverrideCoins))
        mTargetCoins = holder->mGameDataFile->mCoinCount;

    if (mIsOverrideCoins) {
        ImGui::SameLine();
        ImGui::Checkbox("Negative", &mIsExtendSlider);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Allows entering negative Coin\nvalues which is not possible\nin the base game");

        ImGui::SliderInt("Coins", &mTargetCoins, mIsExtendSlider ? -9999 : 0, 9999);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("The amount of Coins the player has");
    }
}