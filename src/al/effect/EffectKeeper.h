#pragma once

#include "al/effect/Effect.h"
#include "al/effect/EffectSystemInfo.h"

#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"

namespace al
{
    class MtxPtrHolder;

    class EffectKeeper {
    public:
       EffectKeeper(al::EffectSystemInfo const*, char const*, sead::Vector3f const*, sead::Vector3f const*, sead::Matrix34f const*);

       const char* mUnk;                // 0x00
       unsigned int mTotalFX;           // 0x08
       al::Effect** mEffects;           // 0x10
       void* unk3;                      // 0x18
       bool unkBool1;                   // 0x20
       bool unkBool2;                   // 0x21
       bool unkBool3;                   // 0x22
       void* unk5;                      // 0x28
       al::MtxPtrHolder* mMtxHolder;    // 0x30
       
    };

    class IUseEffectKeeper {
    public:
        virtual al::EffectKeeper* getEffectKeeper() const = 0;
    };
}