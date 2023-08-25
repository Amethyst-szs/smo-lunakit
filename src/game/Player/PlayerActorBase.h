#pragma once
#include <al/LiveActor/LiveActor.h>
#include "PlayerHackKeeper.h"

class PlayerInitInfo;
class IUsePlayerCollision;
class PlayerInfo;
class PlayerPuppet;
class PlayerAnimator;

namespace al {
    class DemoActor;
}

class PlayerActorBase : public al::LiveActor, public IUsePlayerHack {
public:
    sead::Matrix34f* mViewMtx;
    s32 mPortNo;
    virtual void movement() override;
    virtual void initPlayer(al::ActorInitInfo const&,PlayerInitInfo const&);
    void init(const al::ActorInitInfo& info) override;
    virtual IUsePlayerCollision* getPlayerCollision() const;
    virtual PlayerHackKeeper* getPlayerHackKeeper() const override;
    virtual bool isEnableDemo();
    virtual void startDemo();
    virtual void endDemo();
    virtual void startDemoPuppetable();
    virtual void endDemoPuppetable();
    virtual void startDemoShineGet();
    virtual void endDemoShineGet();
    virtual void startDemoMainShineGet();
    virtual void endDemoMainShineGet();
    virtual void startDemoHack();
    virtual void endDemoHack();
    virtual void startDemoKeepBind();
    virtual void noticeDemoKeepBindExecute();
    virtual void endDemoKeepBind();
    virtual void startDemoKeepCarry();
    virtual void endDemoKeepCarry();
    virtual al::DemoActor* getDemoActor();
    virtual PlayerAnimator* getDemoAnimator();
    virtual bool isDamageStopDemo() const;
    virtual PlayerPuppet* getPlayerPuppet();
    virtual PlayerInfo* getPlayerInfo() const;
    virtual s32 getPortNo() const;
    virtual void getViewMtx();
    virtual void checkDeathArea();
    virtual void sendCollisionMsg();
    virtual void receivePushMsg(al::SensorMsg const*,al::HitSensor *,al::HitSensor *,float);
};