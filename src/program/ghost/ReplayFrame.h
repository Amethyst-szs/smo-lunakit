#pragma once

#include "PlayerAnims.h"
#include "math/seadQuat.h"

struct ReplayFrame {
    PlayerAnims::Enum playerAnim = PlayerAnims::Enum::Unknown;
    PlayerAnims::Enum capAnim = PlayerAnims::Enum::Unknown;
    float blendWeights[6];
    sead::Vector3f pTrans = sead::Vector3f::zero;
    sead::Quatf pRotation = sead::Quatf::unit;
    sead::Vector3f cTrans = sead::Vector3f::zero;
    sead::Quatf cRotation = sead::Quatf::unit;
    sead::Vector3f cJoint = sead::Vector3f::zero;
    float cSkew = 0.f;
    bool isCapVisible = false;
    bool is2D = false;
    bool isHack = false;
};

struct ReplayHeader {
    char mStageName[0x80];
    s32 mScenario = -1;
    char** mHackList;
};

struct ReplayScript {
    ReplayHeader mHeader;
    ReplayFrame* mFrames;
};