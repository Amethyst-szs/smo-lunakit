#pragma once

#include <prim/seadSafeString.h>
#include "al/audio/AudioKeeper.h"
#include "al/camera/CameraDirector.h"
#include "al/nerve/NerveExecutor.h"
#include "al/scene/SceneInitInfo.h"
#include "al/scene/SceneObjHolder.h"
#include "al/camera/CameraDirector.h"
#include "al/audio/AudioKeeper.h"
#include "al/actor/LiveActorKit.h"

namespace al {
    class StageResourceKeeper;

    class LiveActorKit;

    class LayoutKit;

    class SceneStopCtrl;

    class SceneMsgCtrl;

    class ScreenCoverCtrl;

    class AudioDirector;

    class AudioKeeper;

    class NerveKeeper;

    class GraphicsInitArg;

#define GETTER(type, name, field, suffix) type name() suffix {  \
    return field;                                               \
}

#define GETTER_NOIMPL(type, name, suffix) type name() suffix;

    class Scene : public al::NerveExecutor,
                  public al::IUseAudioKeeper,
                  public al::IUseCamera,
                  public al::IUseSceneObjHolder {
    public:
        Scene(const char *name);

        virtual ~Scene();

        virtual void init(const al::SceneInitInfo &);

        virtual void appear();

        virtual void kill();

        virtual void movement();

        virtual void control();

        virtual void drawMain();

        virtual void drawSub();

        GETTER_NOIMPL(AudioKeeper*, getAudioKeeper, const override);

        GETTER_NOIMPL(SceneObjHolder*, getSceneObjHolder, const override);

        GETTER_NOIMPL(CameraDirector*, getCameraDirector, const override);

        GETTER(LayoutKit*, getLayoutKit, mLayoutKit, const);

        GETTER(SceneStopCtrl*, getSceneStopCtrl, mSceneStopCtrl, const);

        GETTER(SceneMsgCtrl*, getSceneMsgCtrl, mSceneMsgCtrl, const);

        void initializeAsync(const al::SceneInitInfo &);

        void initDrawSystemInfo(const al::SceneInitInfo &);

        void initSceneObjHolder(al::SceneObjHolder *);

        void initAndLoadStageResource(const char *, int);

        void initLiveActorKit(const al::SceneInitInfo &, int, int, int);

        void initLiveActorKitWithGraphics(const al::GraphicsInitArg &, const al::SceneInitInfo &, int, int, int);

        void initLayoutKit(const al::SceneInitInfo &);

        void initSceneStopCtrl();

        void initSceneMsgCtrl();

        void initScreenCoverCtrl();

        void endInit(const al::ActorInitInfo &);

//    private:
        void initLiveActorKitImpl(const al::SceneInitInfo &, int, int, int);

        bool mIsAlive;
        sead::FixedSafeString<0x40> mName;
        StageResourceKeeper *mStageResourceKeeper;
        LiveActorKit *mLiveActorKit;
        LayoutKit *mLayoutKit;
        SceneObjHolder *mSceneObjHolder;
        SceneStopCtrl *mSceneStopCtrl;
        SceneMsgCtrl *mSceneMsgCtrl;
        ScreenCoverCtrl *mScreenCoverCtrl;
        AudioDirector *mAudioDirector;
        AudioKeeper *mAudioKeeper;
        NerveKeeper *mNerveKeeper;
    };

    static_assert(sizeof(al::Scene) == 0xd8, "Scene size is not 0xd8");
}  // namespace al