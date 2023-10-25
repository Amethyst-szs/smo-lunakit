#pragma once

#include <container/seadPtrArray.h>
#include <math/seadMatrix.h>

namespace al {
class LiveActor;
class HitSensor;
class CollisionPartsFilterBase;
}  // namespace al

class PlayerRecoverySafetyPoint;
class HackCap;
class PlayerInput;
class PlayerDamageKeeper;
class IPlayerModelChanger;
class IUsePlayerHeightCheck;
class IUsePlayerHack;
class HackObjInfo;
class CapTargetInfo;
class PlayerHackStartTexKeeper;
class HackEndParam;

class PlayerHackKeeper {
public:
    al::LiveActor* mParent;
    HackCap* mHackCap;
    PlayerRecoverySafetyPoint* mRecoverySafePoint;
    void* field_18;
    void* field_20;
    PlayerInput* mInput;
    sead::Matrix34f* field_30;
    PlayerDamageKeeper* mDamageKeeper;
    IPlayerModelChanger* mModelChanger;
    IUsePlayerHeightCheck* mHeightCheck;
    al::HitSensor* mParentBodySensor;
    bool mIsPuppetable;
    bool mIsCancellingHack;
    bool mIsHackDemoStarted;
    bool mIsPuppetable2;
    bool mIsStartedHacking;
    bool mIsHack;
    bool mIsTookDamage;
    al::CollisionPartsFilterBase* mCollisionFilter;
    al::LiveActor* mHackActor;
    al::HitSensor* mHackHitSensor;
    HackObjInfo* mHackObjectInfo;
    al::HitSensor* mStageStartActorSensor;
    al::LiveActor* mStageStartActor;
    CapTargetInfo* mStageStartCapTargetInfo;
    PlayerHackStartTexKeeper* mHackStartTexKeeper;
    al::LiveActor* mHackModel;
    sead::PtrArray<sead::Matrix34f> mHackModelSlices;
    sead::Matrix34f* field_b8;
    s32 field_c0;
    s32 field_c4;
    s32 field_c8;

    PlayerHackKeeper(al::LiveActor*, HackCap*, PlayerRecoverySafetyPoint*, const PlayerInput*, const sead::Matrix34f*, const PlayerDamageKeeper*,
                     const IPlayerModelChanger*, const IUsePlayerHeightCheck*);
    void createHackModel(const al::ActorInitInfo&);
    void startHack(al::HitSensor*, al::HitSensor*, al::LiveActor*);
    void setupHack(al::HitSensor*, al::HitSensor*, al::LiveActor*);
    void endHack(const HackEndParam*);
    void endHackStartDemo(al::LiveActor*);
    void startHackStartDemo(al::LiveActor*);
    void startHackStartDemoPuppetable(al::LiveActor*);
    void addHackStartDemo(al::LiveActor*);
    void appearHackDemoModel(const sead::Matrix34f&, f32);
    void updateHackDemoModel(const sead::Matrix34f&, f32);
    void deleteHackDemoModelEffect();
    void killHackDemoModel();
    bool isActiveHackStartDemo() const;
    void recordHack();
    void cancelHackArea();
    void cancelHack();
    void cancelForceRecovery();
    bool tryEscapeHack();
    void sendTransferHack();
    void sendMarioCheckpointFlagWarp();
    void sendMarioDemo();
    void forceKillHack();
    void sendMarioDead();
    void sendMarioInWater();
    void sendMarioDeathArea();
    void sendMsgEnableMapCheckPointWarp();
    void sendMsgSelfCeilingCheckMiss();
    void receiveRequestTransferHack(al::HitSensor*);
    void requestDamage();
    void receiveRequestDamage();
    void sendSyncDamageVisibility();
    void pushWorldEndBorder(const sead::Vector3f&);
    const char* getCurrentHackName() const;
    void* getPlayerCollision() const;
    void* getHackGuideHeight() const;
    bool isHackGuideEnable() const;
    void getHackStayGravityMargine() const;
    void getCollisionPartsFilter() const;
    bool isHackGroupTalkScare() const;
    bool isHackNoCollisionMsg() const;
    bool isHackNoSeparateCameraInput() const;
    bool isHackUsePlayerCollision() const;
    bool isHackCancelCeilingCheck() const;
    bool isHackInvalidLifeRecovery() const;
    void requestForceHackStageStart(al::HitSensor*, const CapTargetInfo*, al::LiveActor*);
    void executeForceHackStageStart(al::HitSensor*, IUsePlayerHack*);
    void startDemo();
    void endDemo();
};

class IUsePlayerHack {
public:
    virtual PlayerHackKeeper* getPlayerHackKeeper() const = 0;
};