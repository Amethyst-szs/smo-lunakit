#pragma once

#include "al/collision/ICollisionPartsKeeper.h"
#include <sead/container/seadListImpl.h>
#include <sead/container/seadPtrArray.h>
#include <sead/container/seadTList.h>
#include <sead/math/seadBoundBox.h>

namespace al {
class CollisionPartsKeeperOctree : public al::ICollisionPartsKeeper {
public:
    class OctNode {
        OctNode* uVar1;
        OctNode* mSubNodes[8];
        sead::BoundBox3f mBoundBox;
        float fVar1;
        int iVar1;
        sead::TList<al::CollisionParts*> mCollisionParts;
        sead::ListNode uVar2;
    };

    sead::BoundBox3f mBoundBox;
    float fVar1;
    unsigned char gap1[0x4];
    OctNode mRootNode;
    int iVar1;
    OctNode* uVar1;
    void* uVar2;
    int iVar2;
};

class CollisionPartsKeeperPtrArray : public al::ICollisionPartsKeeper {
public:
    sead::PtrArray<al::CollisionParts>* mCollisionParts;
};
}
