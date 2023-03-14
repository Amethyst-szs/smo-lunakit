#include "program/devgui/categories/edit/CategoryCoins.h"

#include "game/Player/PlayerFunction.h"
#include "helpers/PlayerHelper.h"
#include "game/Player/PlayerConst.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "logger/Logger.hpp"


CategoryCoins::CategoryCoins(const char* catName, const char* catDesc)
    : CategoryBase(catName, catDesc)
{
}

void CategoryCoins::updateCat()
{

    PlayerActorBase* player = tryGetPlayerActor();

    if (!holder && !gameSeq) {
        GameDataHolder* holder = tryGetGameDataHolder();
        HakoniwaSequence* gameSeq = tryGetHakoniwaSequence();



        if (holder && gameSeq) {
            file = holder->mGameDataFile;
            scene = gameSeq->curScene;

        }
    }

    // Get the player actor and check if they are dead
    if (!player){
        return;
    }
    // Override the player's Coins if they exist and are alive
    if (mIsOverrideCoins && scene && player) {
        file->mCoinCount = mTargetCoins;
        scene->mSceneLayout->coinCounter->updateCountImmidiate();

    }
    else {

    }
}

void CategoryCoins::updateCatDisplay()
{
    CategoryBase::updateCatDisplay();

    if (ImGui::Checkbox("Edit Coins", &mIsOverrideCoins) && file ) {
        mTargetCoins = file->mCoinCount;
    }

// Sliders
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