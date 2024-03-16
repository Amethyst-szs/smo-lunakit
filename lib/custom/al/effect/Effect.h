#pragma once

#include "EffectInfo.h"

#include "sead/math/seadVector.h"

namespace al
{
    class Effect {
    public:
        char padding[0x20];                 // 0x00
        al::EffectInfo* mEffectInfo;        // 0x20
        sead::Vector3f* mVec;               // 0x28
        sead::Vector3f* mVec2;              // 0x30
        char padding2[0xc8-0x38];
    };
};