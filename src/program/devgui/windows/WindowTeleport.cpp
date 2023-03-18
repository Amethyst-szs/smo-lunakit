#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowTeleport.h"
#include "al/util/LiveActorUtil.h"
#include "al/util.hpp"


WindowTeleport::WindowTeleport(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages) {}

void WindowTeleport::updateWin()
{
            PlayerActorHakoniwa* player = tryGetPlayerActorHakoniwa();

    if(player){
        if(al::isPadTriggerLeft(-1) && teleportHotkeys) {saveTeleportData(*player, savestateIndex);};
        if(al::isPadTriggerRight(-1) && teleportHotkeys) {loadTeleportData(*player, savestateIndex);};
        }
    WindowBase::updateWin();
    if(!mIsActive)
        return;

    return;
}

bool WindowTeleport::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;

    PlayerActorHakoniwa* player = tryGetPlayerActorHakoniwa();

    if(!player)
        ImGui::Text("Player does not exist!");

    if(!player)
        return true;

    ImGui::SetWindowFontScale(1.2f);
    ImGui::SliderInt("Teleport Index", &savestateIndex, 1, NUMSAVES);
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("The index of the teleport position to save/load to/from.");
    if(ImGui::Button("Save Position")) {saveTeleportData(*player, savestateIndex);};
    if(ImGui::IsItemHovered())
        ImGui::SetTooltip("Saves the current position and rotation of the player to the selected index.");
    ImGui::SameLine();
    if(ImGui::Button("Load Position")) {loadTeleportData(*player, savestateIndex);};
        if(ImGui::IsItemHovered())
            ImGui::SetTooltip("Loads the position and rotation of the player from the selected index.");
    ImGui::Checkbox("Teleport Hotkeys", &teleportHotkeys);
        if(ImGui::IsItemHovered())
            ImGui::SetTooltip("Enables hotkeys to save(D-Pad Left) and load(D-Pad Right) to/from the selected index.");



    ImGui::Text("Saved: %s", savestates[savestateIndex].mSaved ? "true" : "false");
    ImGui::Text("Position: X: %.3f, Y: %.3f, Z: %.3f", savestates[savestateIndex].mTrans.x, savestates[savestateIndex].mTrans.y, savestates[savestateIndex].mTrans.z);
    ImGui::Text("Rotation: X: %.3f, Y: %.3f, Z: %.3f, W: %.3f", savestates[savestateIndex].mQuat.x, savestates[savestateIndex].mQuat.y, savestates[savestateIndex].mQuat.z, savestates[savestateIndex].mQuat.w);

    return true;
}

void WindowTeleport::saveTeleportData(PlayerActorHakoniwa& player, int idx) {
    savestates[idx].mTrans = al::getTrans(&player);
    savestates[idx].mQuat = al::getQuat(&player);
    savestates[idx].mSaved = true;
}

void WindowTeleport::loadTeleportData(PlayerActorHakoniwa& player, int idx) {
    al::LiveActor* move = &player;
    al::LiveActor* hack = player.mHackKeeper->currentHackActor;

    if (hack) {
        al::offCollide(hack);
        al::setTrans(hack, savestates[idx].mTrans);
        al::setVelocityZero(hack);
        al::onCollide(hack);
    } else {
        al::offCollide(move);
        player.startDemoPuppetable();
        player.mPlayerStainControl->clearStain();
        al::setTrans(move, savestates[idx].mTrans);
        al::updatePoseQuat(move, savestates[idx].mQuat);
        al::setVelocityZero(move);
        player.endDemoPuppetable();
        al::onCollide(move);
    }
}