#pragma once

#include "al/actor/IUseName.h"
#include "al/actor/Placement.h"
#include "types.h"

#include "StageSwitchDirector.h"
#include "StageSwitchAccesser.h"

namespace al
{

class StageSwitchKeeper {
public:
    StageSwitchKeeper();
    void init(al::StageSwitchDirector*, al::PlacementInfo const&);
    al::StageSwitchAccesser* tryGetStageSwitchAccesser(char const*) const;

    al::StageSwitchAccesser* mAccesser;     //0x00
    int64_t mTotalSwitches;                 //0x08
    int64_t mUnk;                           //0x10
};

class IUseStageSwitch : virtual public al::IUseName {
public:
    virtual al::StageSwitchKeeper* getStageSwitchKeeper() const = 0;
    virtual void initStageSwitchKeeper() = 0;
};
};