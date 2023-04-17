#include "program/devgui/categories/edit/CategoryHealth.h"

#include "game/Player/PlayerFunction.h"

#include "helpers/GetHelper.h"
#include "helpers/PlayerHelper.h"

#include "imgui.h"

CategoryHealth::CategoryHealth(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap) {}

void CategoryHealth::updateCat()
{
    // Get the player's hit point data pointer if it doesn't exist already
    HakoniwaSequence* gameSeq = tryGetHakoniwaSequence();

    if (!mHitData && gameSeq)
        mHitData = gameSeq->mGameDataHolder.mData->mGameDataFile->mPlayerHitPointData;

    // Get the player actor and check if they are dead
    PlayerActorBase* player = tryGetPlayerActor(gameSeq);
    if (!player)
        return;

    bool isPlayerDead = PlayerFunction::isPlayerDeadStatus(player);

    // Override the player's health if they exist and are alive
    if (mIsOverride && !isPlayerDead) {
        mHitData->mCurrentHit = mTargetHealth;
        mHitData->mIsKidsMode = mIsKidsMode;
    }

    // Try killing the player if the kill button is pressed
    StageScene* curScene = tryGetStageScene(gameSeq);
    if (isInStageScene(curScene) && mIsKillPlayer && !isPlayerDead) {
        PlayerHelper::killPlayer(player);
        mIsKillPlayer = false;
    }
}

void CategoryHealth::updateCatDisplay()
{
    CategoryBase::updateCatDisplay();

    if (ImGui::Checkbox("Edit Health", &mIsOverride) && mHitData) {
        mTargetHealth = mHitData->mCurrentHit;
        mIsKidsMode = mHitData->mIsKidsMode;
    }

    if (mIsOverride) {
        ImGui::SameLine();
        ImGui::Checkbox("Kids", &mIsKidsMode);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Kids Mode is Assist Mode\nOnly overrides health meter,\nnot all of Assist Mode!");

        ImGui::SameLine();
        ImGui::Checkbox("Extend", &mIsExtendSlider);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Allows entering higher HP\nvalues than what is possible\nin the base game");

        ImGui::SliderInt("Health", &mTargetHealth, 1, mIsExtendSlider ? 255 : 9);
    }

    if (isInStageScene() && ImGui::Button("Kill Player"))
        mIsKillPlayer = true;
}