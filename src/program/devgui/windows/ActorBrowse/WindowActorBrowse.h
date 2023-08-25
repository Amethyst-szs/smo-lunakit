
/*
    - LunaKit Actor Browser Window -

    Find, view, and manipulate tevery actor in the stage with search and favorite features

    https://github.com/Amethyst-szs/smo-lunakit/wiki#actor-browser
*/

#pragma once

#define MAXFAVS 32

#include "devgui/windows/WindowBase.h"
#include "al/actor/ActorCameraTarget.h"
#include "primitives/PrimitiveTypes.h"

enum ActorBrowseFilterType_ {
    ActorBrowseFilterType_NONE = 0,
    ActorBrowseFilterType_FAV = 1 << 0,
    ActorBrowseFilterType_SEARCH = 1 << 1
};
typedef int ActorBrowseFilterType;


enum ActorBrowseNameDisplayType {
    ActorBrowseNameDisplayType_CLASS = 0,
    ActorBrowseNameDisplayType_MODEL = 1,
    ActorBrowseNameDisplayType_NAME = 2,
    ActorBrowseNameDisplayType_ENUMSIZE
};

__attribute__((used)) static const char* actorBrowseNameTypeTable[ActorBrowseNameDisplayType_ENUMSIZE] = {
    "Class",
    "Model",
    "Name "
};

__attribute__((used)) static const char* actorBrowseWindowName = "Actor Browser";

class WindowActorBrowse : public WindowBase {
public:

    /*
        Main Functions
        These are implemented in the main WindowActorBrowse.cpp and are the most important to the front-end
    */

    WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault);

    void updateWin() override;
    bool tryUpdateWinDisplay() override;

    // Check if filter types are active (note multiple can be enabled at once)
    bool isFilterByNone() { return mFilterType == ActorBrowseFilterType_NONE; }
    bool isFilterByFavorites() { return mFilterType & ActorBrowseFilterType_FAV; }
    bool isFilterBySearch() { return mFilterType & ActorBrowseFilterType_SEARCH; }

    // Check what the current name display type is
    bool isNameDisplayClass() { return mNameDisplayType == ActorBrowseNameDisplayType_CLASS; }
    bool isNameDisplayModel() { return mNameDisplayType == ActorBrowseNameDisplayType_MODEL; }
    bool isNameDisplayName() { return mNameDisplayType == ActorBrowseNameDisplayType_NAME; }

private:

    /*
        Draw different child windows
        Each of these is implemented in it's own CPP file for organization
    */

    // ActorBrowseChildHeader.cpp
    void childButtonHeader(al::Scene* scene);

    // ActorBrowseChildList.cpp
    void childActorList(al::Scene* scene); 

    // ActorBrowseChildInspect.cpp
    void childActorInspector();
    inline void drawActorInspectorTreePose(al::ActorPoseKeeperBase* pose);
    inline void drawActorInspectorTreeFlags(al::LiveActorFlag* flag, float childWindowWidth);
    inline void drawActorInspectorTreeNrvs(al::NerveKeeper* nrvKeep, sead::FixedSafeString<0x30>* actorClass);
    inline void drawActorInspectorTreeRail(al::RailRider* railRide);
    inline void drawActorInspectorTreeSensor(al::HitSensorKeeper* sensor);
    inline void drawActorInspectorTreeSubActor(al::SubActorKeeper* subActorKeep);
    inline void drawActorInspectorTreeKuriboDebug(al::LiveActor* actor);

    /*
        WindowActorBrowseUtil.cpp functions
        These functions serve as general utility, implemented in the util cpp
    */

    // Filtering
    void generateFilterList(al::Scene* scene);

    // Favorite handling
    bool isActorInFavorites(const char* actorName);
    void toggleFavorite(const char* actorName);
    void getFavoritesFromSave();
    void publishFavoritesToSave();

    // Actor name getting and trimming
    sead::FixedSafeString<0x30> getActorName(al::LiveActor* actor);
    sead::FixedSafeString<0x30> getActorName(al::LiveActor* actor, ActorBrowseNameDisplayType nameType);
    sead::FixedSafeString<0x30> calcTrimNameFromRight(sead::FixedSafeString<0x30>);
    sead::FixedSafeString<0x30> calcTrimNameFromRight(sead::FixedSafeString<0x30>, int maxChars);
    void showActorTooltip(al::LiveActor* actor);
    int calcRoundedNum(int numToRound, int multiple);

    bool mIsSaveDataInited = false;

    // Filter and display type
    bool mIsWindowVertical = false;
    ActorBrowseNameDisplayType mNameDisplayType = ActorBrowseNameDisplayType_CLASS;
    ActorBrowseFilterType mFilterType = ActorBrowseFilterType_NONE;
    al::LiveActorGroup* mFilterActorGroup = nullptr;

    // Selected actor
    al::LiveActor* mSelectedActor = nullptr;
    al::ActorCameraTarget *mSelectedActorTarget = nullptr;
    HitSensorRenderTypes mHitSensorTypes = HitSensorType_ALL;
    unsigned int mRailPercision = 10;

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