#pragma once

#include "ActorInitInfo.h"
#include "types.h"

namespace al {

class LiveActor;

struct SubActorSync {
    enum Enum {
        cNone = 0, // 0
        cAppear = 1 << 0, // 1
        cClipping = 1 << 1, // 2
        cHide = 1 << 2, // 4
        cAlphaMask = 1 << 3, // 8
        cAll = cAppear | cClipping | cHide | cAlphaMask // 15
    };
}; // struct SubActorSync

struct SubActorInfo
{
    SubActorInfo() = default;
    inline SubActorInfo(al::LiveActor *actor, SubActorSync::Enum syncType) : mSubActor(actor), mSyncType(syncType) {};
    al::LiveActor* mSubActor = nullptr;
    void* field_8 = nullptr;
    SubActorSync::Enum mSyncType = SubActorSync::cNone;
};

class SubActorKeeper {
public:
    SubActorKeeper(al::LiveActor* parentActor);
    void init(al::ActorInitInfo const&, char const*, int);

    void registerSubActor(al::LiveActor*, unsigned int);
    static SubActorKeeper* create(al::LiveActor*);
    static SubActorKeeper* tryCreate(al::LiveActor*, char const*, int);

    al::LiveActor* mRootActor;              //0x00
    int mMaxActorCount;                     //0x08
    int mActorCount;                        //0x0C
    al::SubActorInfo **mInfoList;           //0x10
};

} // namespace al