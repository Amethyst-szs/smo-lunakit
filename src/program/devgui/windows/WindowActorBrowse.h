
/*
    - LunaKit Actor Browser Window -
*/

#pragma once

#include "imgui.h"

#include "program/devgui/windows/WindowBase.h"

enum ActorBrowseFilterType {
    FILTER_NONE,
    FILTER_FAV,
    FILTER_SEARCH
};

class WindowActorBrowse : public WindowBase {
public:
    WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);

    void updateWin() override;
    bool tryUpdateWinDisplay() override;

private:
    void drawButtonHeader(al::Scene* scene);
    void drawActorList(al::Scene* scene);
    void drawActorInfo();

    bool isActorInFavorites(char* actorName);
    void toggleFavorite(char* actorName);

    char* getActorName(al::LiveActor* actor);
    sead::FixedSafeString<0x30> calcTrimNameFromRight(char* text);
    int calcRoundedNum(int numToRound, int multiple);

    bool isFilterByNone() { return mFilterType == ActorBrowseFilterType::FILTER_NONE; }
    bool isFilterByFavorites() { return mFilterType == ActorBrowseFilterType::FILTER_FAV; }
    bool isFilterBySearch() { return mFilterType == ActorBrowseFilterType::FILTER_SEARCH; }

    al::LiveActor* mSelectedActor = nullptr;
    al::LiveActorGroup* mFilterActorGroup = nullptr;

    ActorBrowseFilterType mFilterType = ActorBrowseFilterType::FILTER_NONE;

    // Favorite filter values
    int mTotalFavs = 0;
    static const int mMaxFavs = 32;
    sead::FixedSafeString<0x40> mFavActorNames[mMaxFavs];

    // Search filter values
    const char* mSearchString = "null";

    // Actor list rendering
    float mLineSize = 0;
    int mMaxCharacters = 1;

    // Constants
    const float mHeaderSize = 30.f;
};