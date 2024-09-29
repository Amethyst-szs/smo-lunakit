#pragma once

#include "ActorItemInfo.h"

namespace al {

class LiveActor;

class ActorItemKeeper {
public:
    ActorItemKeeper(al::LiveActor const*, int);

    al::LiveActor* mParent;             //0x00
    al::ActorItemInfo** mItemInfoList;  //0x08
    int mUnk1;                          //0x10
    int mTotalItems;                    //0x14
    char padding[0x34-0x18];            //0x18
};

} // namespace al