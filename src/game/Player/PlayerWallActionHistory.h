#pragma once

#include "game/Interfaces/IUsePlayerCollision.h"

#include "sead/math/seadVector.h"

class PlayerWallActionHistory {
public:
    void recordWallJump(IUsePlayerCollision const*, sead::Vector3<float> const&);
    void recordWallJump(sead::Vector3<float> const&, sead::Vector3<float> const&);
    void recordWallLeave(sead::Vector3<float> const&, sead::Vector3<float> const&);
    void reset();
    void update(IUsePlayerCollision const*);

    const char unk1[4];
    sead::Vector3f mJumpPosition;
    sead::Vector3f mJumpNormal;
};