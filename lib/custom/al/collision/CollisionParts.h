#pragma once

#include "al/collision/KCollisionServer.h"
#include "al/sensor/HitSensor.h"
#include <sead/container/seadTList.h>
#include <sead/math/seadMatrix.h>

namespace al {
class CollisionParts {
public:
    unsigned char gap1[0x18];
    sead::TList<al::CollisionParts*>* mPartsList;
    sead::Matrix34f* mJointMtx;
    sead::Matrix34f mVar1;
    sead::Matrix34f mBaseMtx;
    sead::Matrix34f mBaseInvMtx;
    sead::Matrix34f mPrevBaseMtx;
    sead::Matrix34f mVar2;
    sead::Vector3f mMtxScaleVec;
    float mMtxScale;
    float mInvMtxScale;
    int mPriority;
    al::KCollisionServer* mKCollisionServer;
    al::HitSensor* mConnectedSensor;
    const char* mSpecialPurpose;
    const char* mOptionalPurpose;
    float fVar2;
    float fVar3;
    float fVar4;
    unsigned char gap2[0x4];
    float mBoundingSphereRange;
    float mBaseMtxScale;
    bool bVar1;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    bool bVar5;
    bool mIsMoving;
    bool bVar6;
};
}
