/*
    - Teleport Window -
*/

#pragma once

#include "imgui.h"

#include "program/devgui/windows/WindowBase.h"
#include "game/Player/PlayerStainControl.h"

#define NUMSAVES 16

struct SaveState {
    bool mSaved = false;
    sead::Vector3f mTrans = { 0, 0, 0 };
    sead::Quatf mQuat = { 0, 0, 0, 0 };
};


class WindowTeleport : public WindowBase {
public:
    WindowTeleport(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);

    void updateWin() override;
    bool tryUpdateWinDisplay() override;

private:
void saveTeleportData(PlayerActorHakoniwa& player, int idx);
void loadTeleportData(PlayerActorHakoniwa& player, int idx);

SaveState savestates[NUMSAVES];
int savestateIndex = 1;
bool teleportHotkeys = true;


};