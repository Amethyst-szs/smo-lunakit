#pragma once

#include "al/LiveActor/LiveActor.h"
#include "game/Player/HackCap.h"
#include <sead/prim/seadSafeString.h>
#include <sead/container/seadPtrArray.h>

class PlayerModelChangerHakoniwa;
class PlayerEffect;

class PlayerStainControl {
private:
    enum StainType {
        Poison = 1, Fire, Ice, SandDesert, SandSea, SandMoon
    };

    struct unkstruct {
        int iVar1;
        float fVar1;
        float fVar2;
        float fVar3;
        float fVar4;
        float fVar5;
        unsigned char pad[0x4];
        float fVar6;
        int iVar2;
        int iVar3;
    };

public:
    PlayerStainControl(al::LiveActor const*, al::LiveActor*, PlayerModelChangerHakoniwa const*, HackCap const*, PlayerEffect*);

    void clearCurrentStain(bool);
    void clearStain();
    void clearStainRequest();
    int getSandType(const char*) const;
    bool isEnableInvalidateStain() const;
    bool isEnableLowPriorityStain() const;
    bool isEnableValidateStain() const;
    void noticeEndHack();
    void noticeMainShineGet();
    void noticeStartHack();
    void recordBlackSmoke();
    void recordBlizzard();
    void recordDamageFire();
    void recordDamageFireDead();
    void recordExplosion();
    void recordIceWater();
    void recordInWater();
    void recordInWet();
    void recordPoison();
    void recordSandHeavyLand(const char*);
    void recordSandMoonBySensor();
    void recordSandMove(const char*);
    void recordSnowBySensor();
    void recordSnowMove(const char*);
    void tryDeleteStainEffect(PlayerStainControl::StainType, float);
    void tryEmitClearStainEffect(PlayerStainControl::StainType, float);
    void tryEmitStainEffect(PlayerStainControl::StainType);
    void update();

    al::LiveActor* mPlayer;
    al::LiveActor* mPlayerModel;
    PlayerModelChangerHakoniwa* mModelChanger;
    HackCap* mHackCap;
    PlayerEffect* mPlayerEffect;
    sead::PtrArray<sead::SafeString> arr1;
    int iVar1;
    sead::PtrArray<unkstruct> arr2;
    StainType mStainType;
    bool bVar1;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    int iVar2;
    int iVar3;
    int iVar4;
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    int iVar5;
    int iVar6;
    bool bVar5;
    bool bVar6;
};