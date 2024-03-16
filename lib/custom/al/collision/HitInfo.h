#pragma once

#include "al/collision/Triangle.h"
#include <sead/math/seadVector.h>

namespace al {
class HitInfo {
public:
    al::Triangle mTri;
    float fVar1;
    sead::Vector3f mCollisionHitPos;
    sead::Vector3f vVar1;
    sead::Vector3f mCollisionMovingReaction;
    bool bVar1;
};

class SphereHitInfo : public al::HitInfo {

};

class DiskHitInfo : public al::HitInfo {

};
}
