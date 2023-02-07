#pragma once

#include "game/WorldList/WorldList.h"
#include "types.h"

enum HomeShipStates {
    BROKEN = 0,
    ACTIVATE = 1,
    LAUNCH = 2,
    CLOUDLAND = 3,
    CRASH = 4,
    REPAIR = 5,
    CRASHRUINED = 6,
    REPAIRRUINED = 7 // Never updates status after ruined kingdom
};

enum WaterfallWorldProgressStates {
    ARRIVE = 0,
    FIRSTMOON = 1,
    TALKCAP = 2
};

enum UnlockBranchStates {
    LOCKED = 0,
    FOREST = 1,
    LAKE = 2,
    SEA = 3,
    SNOW = 4
};

class GameProgressData {
    public:
        int getHomeLevel(void) const;
        void upHomeLevel(void);
        void talkCapNearHomeInWaterfall(void);

        const char* unkVTable;
        undefined* mWorldMapArray;
        undefined* mWorldWarpHoleArray;
        undefined* mShineListArray;
        undefined* unk;
        int mUnlockWorldNum; // Total unlocked worlds, starts at 1
        UnlockBranchStates mUnlockStateFirstBranch;
        UnlockBranchStates mUnlockStateSecondBranch;
        HomeShipStates mHomeStatus;
        int mHomeLevel; // 100% save has value at 9
        int padding;
        WorldList* mWorldList;
        bool* mIsFirstTimeGoWorld; // Array
        WaterfallWorldProgressStates mWaterfallWorldProgress;
};