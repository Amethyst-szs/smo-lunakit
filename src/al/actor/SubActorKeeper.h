#pragma once

#include "ActorInitInfo.h"
#include "types.h"

namespace al {

class LiveActor;

class SubActorKeeper {
public:
    SubActorKeeper(al::LiveActor* parentActor);
    void init(al::ActorInitInfo const&, char const*, int);

    void registerSubActor(al::LiveActor*, unsigned int);
    void create(al::LiveActor*);
    void tryCreate(al::LiveActor*, char const*, int);

    al::LiveActor* mParent;             //0x00
    int mUnk;                           //0x08
    u32 mTotalActors;                   //0x0C
    al::LiveActor** mSubActors;         //0x10
};

} // namespace al