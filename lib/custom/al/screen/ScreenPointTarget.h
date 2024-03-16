#pragma once

#include "sead/prim/seadSafeString.h"
#include "sead/math/seadMatrix.h"
#include "sead/math/seadVector.h"

namespace al
{

class LiveActor;
class ParameterObj;
class ScreenPointCheckGroup;

class ScreenPointTarget {
public:
    ScreenPointTarget(al::LiveActor*, char const*, float, sead::Vector3f const*, char const*, sead::Vector3f const&);

    bool mUnk1;                                 // 0x00
    bool mUnk2;                                 // 0x01
    char padding[0x06];                         // 0x02
    al::ParameterObj* mParamObj;                // 0x08
    sead::SafeString* mTargetName;              // 0x10
    sead::SafeString* mTargetRadiusSomething;   // 0x18
    void* mUnk5;                                // 0x20
    sead::SafeString* mJointName;               // 0x28
    float mTargetRadius;                        // 0x30
    sead::Vector3f* mUnk7;                      // 0x38
    sead::Matrix34f* mFollowJointMtx;           // 0x40
    sead::Vector3f mUnk9;                       // 0x48
    sead::Vector3f mUnk10;                      // 0x54
    al::LiveActor* mActor;                      // 0x60
    al::ScreenPointCheckGroup* mCheckGroup;     // 0x68

};

} // namespace al