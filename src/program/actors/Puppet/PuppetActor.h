#pragma once

#include "Library/LiveActor/LiveActor.h"
#include "Library/Thread/FunctorV0M.h"
#include "al/layout/BalloonMessage.h"
#include "Library/Base/StringUtil.h"
#include "al/util.hpp"

#include "game/Player/PlayerConst.h"
#include "game/Player/PlayerFunction.h"
#include "game/Player/PlayerJointControlPartsDynamics.h"
#include "game/Player/PlayerModelHolder.h"

#include "ghost/Ghost.h"

#include "PuppetCapActor.h"
#include "HackModelHolder.h"
#include "math/seadVector.h"
#include "heap/seadDisposer.h"



class PuppetActor : public al::LiveActor, public sead::IDisposer {
    friend class Ghost;
public:
    PuppetActor(const char* name, Ghost* parent);
    ~PuppetActor() override;
    virtual void init(al::ActorInitInfo const&) override;
    virtual void initAfterPlacement(void) override;
    virtual void control(void) override;
    virtual void movement(void) override;
    virtual void makeActorAlive(void) override;
    virtual void makeActorDead(void) override;
    virtual void calcAnim(void) override;

    void startAction(const char* actName);
    void hairControl();

    void setBlendWeight(int index, float weight) { al::setSklAnimBlendWeight(getCurrentModel(), weight, index); };

    bool isNeedBlending();

    al::LiveActor* getCurrentModel();

    void debugTeleportCaptures(const sead::Vector3f& pos);

    void debugTeleportCapture(const sead::Vector3f& pos, int index);

    void emitJoinEffect();

private:
    void changeModel(const char* newModel);

    bool setCapture(const char* captureName);

    void syncPose();

    Ghost* mParent = nullptr;
    PuppetCapActor* mPuppetCap = nullptr;
    HackModelHolder* mCaptures = nullptr;

    PlayerCostumeInfo* mCostumeInfo = nullptr;
    PlayerModelHolder* mModelHolder = nullptr;

    bool mIs2DModel = false;
    bool mIsCaptureModel = false;
};
/*
PlayerCostumeInfo* initMarioModelPuppet(al::LiveActor* player, const al::ActorInitInfo& initInfo,
                                        char const* bodyName, char const* capName, int subActorNum,
                                        al::AudioKeeper* audioKeeper);
PlayerHeadCostumeInfo* initMarioHeadCostumeInfo(al::LiveActor* player, const al::ActorInitInfo& initInfo, const char* headModelName, const char* capModelName, const char* headType, const char* headSuffix);
*/
