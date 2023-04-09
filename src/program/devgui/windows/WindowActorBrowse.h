
/*
    - LunaKit Actor Browser Window -

    Find, view, and manipulate tevery actor in the stage with search and favorite features

    https://github.com/Amethyst-szs/smo-lunakit/wiki#actor-browser
*/

#pragma once

#define MAXFAVS 32

#include "imgui.h"

#include "primitives/PrimitiveQueue.h"

#include "devgui/popups/PopupKeyboard.h"
#include "devgui/windows/WindowBase.h"

#include "helpers/ImGuiHelper.h"

enum ActorBrowseFilterType_ {
    ActorBrowseFilterType_NONE = 0,
    ActorBrowseFilterType_FAV = 1 << 0,
    ActorBrowseFilterType_SEARCH = 1 << 1
};

typedef int ActorBrowseFilterType;

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

    void publishFavoritesToSave();
    void getFavoritesFromSave();

    char* getActorName(al::LiveActor* actor);
    sead::FixedSafeString<0x30> calcTrimNameFromRight(char* text);
    sead::FixedSafeString<0x30> calcTrimNameFromRight(char* text, int maxChars);
    int calcRoundedNum(int numToRound, int multiple);
    
    // Filtering
    void generateFilterList(al::Scene* scene);

    bool isFilterByNone() { return mFilterType == ActorBrowseFilterType_NONE; }
    bool isFilterByFavorites() { return mFilterType & ActorBrowseFilterType_FAV; }
    bool isFilterBySearch() { return mFilterType & ActorBrowseFilterType_SEARCH; }

    bool mIsSaveDataInited = false;
    bool mIsWindowVertical = false;
    
    // Selected actor
    al::LiveActor* mSelectedActor = nullptr;
    HitSensorRenderTypes mHitSensorTypes = HitSensorType_ALL;
    unsigned int mRailPercision = 10;

    // Filtering
    ActorBrowseFilterType mFilterType = ActorBrowseFilterType_NONE;
    al::LiveActorGroup* mFilterActorGroup = nullptr;
    bool mIsPrimDrawFilterGroup = false;

    // Favorite filter values
    int mTotalFavs = 0;
    static const int mMaxFavs = MAXFAVS;
    sead::FixedSafeString<0x40> mFavActorNames[mMaxFavs];

    // Search filter values
    bool mIsKeyboardInUse = false;
    const char* mSearchString = nullptr;

    // Actor list rendering
    float mLineSize = 0;
    int mMaxCharacters = 1;

    // Constants
    const float mHeaderSize = 27.f;
};