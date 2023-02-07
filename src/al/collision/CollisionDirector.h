#pragma once

#include "al/collision/CollisionPartsFilter.h"
#include "al/collision/CollisionPartsKeeper.h"
#include "al/collision/HitInfo.h"
#include "al/collision/TriangleFilter.h"
#include "al/hio/HioNode.h"
#include "al/collision/ICollisionPartsKeeper.h"
#include "al/execute/ExecuteDirector.h"
#include <sead/container/seadPtrArray.h>

namespace al {
class CollisionDirector : public al::HioNode, public al::IUseExecutor {
public:
    al::CollisionPartsKeeperOctree* mCollisionOctree;
    al::ICollisionPartsKeeper* mCollisionOctree2;
    al::CollisionPartsKeeperPtrArray* mCollisionPtrArray;
    al::CollisionPartsFilterBase* mPartsFilter;
    al::TriangleFilterBase* mTriFilter;
    sead::PtrArray<al::ArrowHitResultBuffer>* mStrikeArrowInfo;
    sead::PtrArray<al::SphereHitResultBuffer>* mStrikeSphereInfo;
    sead::PtrArray<al::DiskHitResultBuffer>* mStrikeDiskInfo;
    al::SphereHitInfo* uVar1;
    al::DiskHitInfo** uVar2;
};

class IUseCollision {
public:
    virtual al::CollisionDirector* getCollisionDirector() const = 0;
};
};
