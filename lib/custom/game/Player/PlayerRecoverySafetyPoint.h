#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/collision/Collider.h"
#include "al/sensor/HitSensor.h"
#include "game/Interfaces/IUseDimension.h"
#include "game/Player/HackCap.h"
#include "sead/math/seadVector.h"

class PlayerRecoverySafetyPoint {
public:
    sead::Vector3f* getSafetyPoint();
    void startRecovery(float);
    void startBubbleWait();
    void noticeDangerousPoint(sead::Vector3f const&, bool);

    al::LiveActor* mActor;                                      //0x00
    HackCap* mHackCap;                                          //0x08
    IUseDimension* mIUseDimension;                              //0x10
    al::CollisionPartsFilterBase* mCollisionPartsFilterBase;    //0x18
    al::HitSensor* mHitSensor;                                  //0x20
    const char mUnk1[0x1c];                                     //0x28
    sead::Vector3f mSafetyPointPos;                             //0x44
    sead::Vector3f mSafetyPointGrav;                            //0x50
    const char mUnk2[0x54];
    const char mUnk3[0x8];
};