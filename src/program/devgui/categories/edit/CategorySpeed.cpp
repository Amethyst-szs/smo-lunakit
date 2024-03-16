#include "program/devgui/categories/edit/CategorySpeed.h"

#include "game/Player/PlayerConst.h"

#include "helpers/GetHelper.h"

#include "logger/Logger.hpp"

#include "imgui.h"

CategorySpeed::CategorySpeed(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap)
{}

void CategorySpeed::updateCat()
{
    // Get the player actor and check if they are dead
    PlayerActorHakoniwa* playerHak = tryGetPlayerActorHakoniwa();
    if (!playerHak)
        return;

    // Reset the player's speed consts, before overriding them with new value if in use
    playerHak->mConst->mNormalMaxSpeed = 14;
    playerHak->mConst->mJumpBaseSpeedMax = 24;
    playerHak->mConst->mJumpMoveSpeedMax = 30;

    if (!mIsOverride)
        return;

    playerHak->mConst->mNormalMaxSpeed = mTargetSpeed;
    playerHak->mConst->mJumpBaseSpeedMax = mTargetSpeed + 50;
    playerHak->mConst->mJumpMoveSpeedMax = mTargetSpeed + 50;
}

void CategorySpeed::updateCatDisplay()
{
    CategoryBase::updateCatDisplay();

    ImGui::Checkbox("Edit Speed", &mIsOverride);

    if (mIsOverride)
        ImGui::SliderFloat("Speed", &mTargetSpeed, 0.f, 100.f);

    if (mIsOverride && ImGui::Button("Reset Speed"))
        mTargetSpeed = 14.0f;
}
