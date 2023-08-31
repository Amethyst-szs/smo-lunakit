#pragma once

#include "al/collision/CollisionDirector.h"
#include "al/hio/HioNode.h"

namespace al {
class GraphicsInitArg;
class ActorResourceHolder;
class AreaObjDirector;
class ExecuteDirector;
class GravityHolder;
class EffectSystem;
class GraphicsSystemInfo;
class ModelDrawBufferUpdater;
class ExecuteAsyncExecutor;
class ModelDisplayListController;
class LiveActorGroup;
class CameraDirector;
class ClippingDirector;
class PlayerHolder;
class HitSensorDirector;
class ScreenPointDirector;
class ShadowDirector;
class SwitchAreaDirector;
class StageSwitchDirector;
class GamePadSystem;
class PadRumbleDirector;
class NatureDirector;
class ModelGroup;
;
class LiveActorKit : public al::HioNode {
public:
    LiveActorKit(int, int);
    virtual ~LiveActorKit();
    void init();
    void initGraphics(const al::GraphicsInitArg&);
    void initHitSensorDirector();
    void initGravityHolder();
    void initShadowDirector();
    void initEffectSystem();
    void initSwitchAreaDirector();
    void initNatureDirector();
    void endInit();
    void update();
    void clearGraphicsRequest();
    void updateGraphics();
    void preDrawGraphics();

    al::CameraDirector* getCameraDirector() const { return mCameraDirector; }
    al::EffectSystem* getEffectSystem() const { return mEffectSystem; }

    int mMaxActors;
    al::ActorResourceHolder* mActorResourceHolder;
    al::AreaObjDirector* mAreaObjDirector;
    al::ExecuteDirector* mExecuteDirector;
    al::GravityHolder* mGravityHolder;
    al::EffectSystem* mEffectSystem;
    al::GraphicsSystemInfo* mGraphicsSystemInfo;
    void* gap_0;
    al::ModelDrawBufferUpdater* mModelDrawBufferUpdater;
    al::ExecuteAsyncExecutor* mExecuteAsyncExecutor1;  // View Update (Core 1)
    al::ExecuteAsyncExecutor* mExecuteAsyncExecutor2;  // View Update (Core 2)
    al::ModelDisplayListController* mModelDisplayListController;
    al::ExecuteDirector* mExecuteDirector2;
    al::LiveActorGroup* mLiveActorGroup;
    al::CameraDirector* mCameraDirector;
    al::ClippingDirector* mClippingDirector;
    al::CollisionDirector* mCollisionDirector;
    void* gap_1;
    al::PlayerHolder* mPlayerHolder;
    al::HitSensorDirector* mHitSensorDirector;
    al::ScreenPointDirector* mScreenPointDirector;
    al::ShadowDirector* mShadowDirector;
    al::StageSwitchDirector* mStageSwitchDirector;
    al::SwitchAreaDirector* mSwitchAreaDirector;
    al::LiveActorGroup* mLiveActorGroup2;
    void* gap_2;
    al::GamePadSystem* mGamePadSystem;
    al::PadRumbleDirector* mPadRumbleDirector;
    al::NatureDirector* mNatureDirector;
    al::ModelGroup* mModelGroup;
};
}  // namespace al

static_assert(sizeof(al::LiveActorKit) == 0xf8);