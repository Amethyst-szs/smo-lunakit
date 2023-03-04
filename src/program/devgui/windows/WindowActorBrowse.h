
/*
    - LunaKit Actor Browser Window -
*/

#pragma once

#include "imgui.h"

#include "program/devgui/DevGuiWindowConfig.h"
#include "program/devgui/windows/WindowBase.h"

class WindowActorBrowse : public WindowBase {
public:
    WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);

    void updateWin() override;
    bool tryUpdateWinDisplay() override;

private:
    void drawButtonHeader();
    void drawActorList(al::Scene* scene);
    void drawActorInfo();

    char* getActorName(al::LiveActor* actor);
    sead::FixedSafeString<0x30> calcTrimNameFromRight(char* text);
    int calcRoundedNum(int numToRound, int multiple);

    bool isActorInFavorites(char* actorName);

    al::LiveActor* mSelectedActor = nullptr;

    static const int mMaxFavs = 32;
    sead::FixedSafeString<0x40> mFavActors[mMaxFavs];

    float mLineSize = 0;
    int mMaxCharacters = 1;

    const float mHeaderSize = 30.f;
};