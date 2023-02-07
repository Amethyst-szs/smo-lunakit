#pragma once

#include "container/seadPtrArray.h"
#include "math/seadVector.h"
#include "prim/seadSafeString.h"

struct StageDBEntry {
    sead::FixedSafeString<0x80> mStageName;
    sead::FixedSafeString<0x40> mStageCategory;
    int mUseScenario;
};

struct WorldListEntry {
    const char *mMainStageName; // 0x0 (Name in Byml)
    const char *mWorldDevelopName; // 0x8 (WorldName in Byml)
    int mQuestInfoCount; // 0x10 (ScenarioNum in Byml)
    int mClearMainScenario; // 0x14 (ClearMainScenario in Byml)
    int mEndingScenario; // 0x18 (AfterEndingScenario in Byml)
    int mMoonRockScenario;  // 0x1C (MoonRockScenario in Byml)
    int *mMainQuestIndexes;  // 0x20 (MainQuestInfo in Byml)
    sead::PtrArray<StageDBEntry> mStageNames; // 0x28
};

class WorldList {
public:
    WorldList(void);

    void getWorldNum(void);

    void getMainQuestMin(int, int);

    const char *getMainStageName(int) const;

    int tryFindWorldIndexByMainStageName(char const *stageName) const;

    int tryFindWorldIndexByStageName(char const *stageName) const;

    int tryFindWorldIndexByDevelopName(char const *stageName) const;

    void isEqualClearMainScenarioNo(int, int);

    void getAfterEndingScenarioNo(int);

    void isEqualAfterEndingScenarioNo(int, int);

    int getMoonRockScenarioNo(int worldId) const;

    bool isEqualMoonRockScenarioNo(int, int) const;

    const char *getWorldDevelopName(int) const;

    void getWorldScenarioNum(int);

    int findUseScenarioNo(const char *stageName) const;

    void checkNeedTreasureMessageStage(char const *);

    bool checkIsMainStage(char const *stageName) const;

    void tryFindTransOnMainStageByStageName(sead::Vector3f *, char const *, int);

    void tryFindHintTransByScenarioNo(sead::Vector3f *, int, int);

    sead::PtrArray<WorldListEntry> mWorldList;
    void *field_10;
    void *field_18;
    void *field_20;
    int field_28;
    int mStagePosCount;
    sead::PtrArrayImpl field_30;
};

static_assert(sizeof(WorldList) == 0x40, "WorldList Size");