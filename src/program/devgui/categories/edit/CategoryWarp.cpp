#include "program/devgui/categories/edit/CategoryWarp.h"
#include "game/Player/PlayerStainControl.h"
#include "game/Player/PlayerHackKeeper.h"
#include "al/util.hpp"
#include "Library/LiveActor/ActorPoseKeeper.h"

#include "helpers/GetHelper.h"

#include "imgui.h"

CategoryWarp::CategoryWarp(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap) {}

void CategoryWarp::updateCat()
{
    if(!mIsUseHotkeys)
        return;
    
    PlayerActorHakoniwa* player = tryGetPlayerActorHakoniwa();
    if(!player)
        return;

    if(al::isPadTriggerLeft(-1)) { saveTeleportData(player); }
    if(al::isPadTriggerRight(-1)) { loadTeleportData(player); }
}

void CategoryWarp::updateCatDisplay()
{
    CategoryBase::updateCatDisplay();
    
    PlayerActorHakoniwa* player = tryGetPlayerActorHakoniwa();

    if(!player) {
        ImGui::TextDisabled("Player does not exist!");
        return;
    }

    ImGui::SliderInt("Teleport Idx", &mCurStateIdx, 0, mMaxSaves - 1);
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("The index of the teleport position\nto save/load to/from");

    if(ImGui::Button("Save")) { saveTeleportData(player); }
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("Saves the current position and rotation\nof the player to the selected index");

    ImGui::SameLine();
    if(ImGui::Button("Load")) { loadTeleportData(player); }
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("Loads the position and rotation of the\nplayer from the selected index");

    ImGui::SameLine();
    ImGui::Checkbox("Hotkeys", &mIsUseHotkeys);
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("Enables hotkeys\nSave - D-Pad Left\nLoad - D-Pad Right");

    WarpSaveState& curState = mStates[mCurStateIdx];
    ImGui::Text("Saved: %s", curState.mSaved ? "true" : "false");
    ImGui::TextDisabled("Pos %.0fx %.0fy %.0fz", curState.mTrans.x, curState.mTrans.y, curState.mTrans.z);
}

void CategoryWarp::saveTeleportData(PlayerActorHakoniwa* player) {
    WarpSaveState& curState = mStates[mCurStateIdx];

    curState.mSaved = true;
    curState.mTrans = al::getTrans(player);
    curState.mQuat = al::getQuat(player);
}

void CategoryWarp::loadTeleportData(PlayerActorHakoniwa* player) {
    WarpSaveState& curState = mStates[mCurStateIdx];
    al::LiveActor* hack = player->mHackKeeper->mCurrentHackActor;

    if (hack) {
        al::offCollide(hack);
        al::setTrans(hack, curState.mTrans);
        al::setVelocityZero(hack);
        al::onCollide(hack);
    } else {
        al::offCollide(player);
        player->startDemoPuppetable();
        player->mStainControl->clearStain();
        al::setTrans(player, curState.mTrans);
        al::updatePoseQuat(player, curState.mQuat);
        al::setVelocityZero(player);
        player->endDemoPuppetable();
        al::onCollide(player);
    }
}
