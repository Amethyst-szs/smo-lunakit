#include "program/devgui/categories/edit/CategorySpeed.h"

#include "game/Player/PlayerFunction.h"
#include "helpers/PlayerHelper.h"
#include "game/Player/PlayerConst.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "logger/Logger.hpp"


CategorySpeed::CategorySpeed(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap)
{
}

void CategorySpeed::updateCat()
{

    // Get the player actor and check if they are dead
    PlayerActorHakoniwa* playerHak = tryGetPlayerActorHakoniwa();
    if (!playerHak)
        return;

    // Override the player's speed if they exist and are alive
    if (mIsOverride && playerHak) {
        playerHak->mPlayerConst->mNormalMaxSpeed = mTargetSpeed;
        if(mTargetSpeed != 14){
            playerHak->mPlayerConst->mJumpBaseSpeedMax = mTargetSpeed + 50;
            playerHak->mPlayerConst->mJumpMoveSpeedMax = mTargetSpeed + 50;
            }
        else{
            playerHak->mPlayerConst->mJumpBaseSpeedMax = 24;
            playerHak->mPlayerConst->mJumpMoveSpeedMax = 30;
        }
    }
    else {
        playerHak->mPlayerConst->mNormalMaxSpeed = 14;
        playerHak->mPlayerConst->mJumpBaseSpeedMax = 24;
        playerHak->mPlayerConst->mJumpMoveSpeedMax = 30;
    }
}

void CategorySpeed::updateCatDisplay()
{
    CategoryBase::updateCatDisplay();
    PlayerActorHakoniwa* playerHak = tryGetPlayerActorHakoniwa();

    if (ImGui::Checkbox("Edit Speed", &mIsOverride) && playerHak) {
        mTargetSpeed = playerHak->mPlayerConst->mNormalMaxSpeed;

    }

    if (mIsOverride) {

        ImGui::SliderInt("Speed", &mTargetSpeed, 0, 100);
    }

    if (isInStageScene() && mIsOverride && ImGui::Button("Reset Speed"))
        mTargetSpeed = 14.0f;
}