#pragma once

#include "Library/Audio/AudioDirector.h"
#include "Library/Layout/LayoutSceneInfo.h"
#include "Library/Message/MessageSystem.h"
#include "al/rumble/PadRumbleDirector.h"
#include "Library/Camera/CameraDirector.h"
#include "Library/Execute/ExecuteDirector.h"
#include "al/layout/LayoutKit.h"
#include "Library/Effect/EffectSystemInfo.h"
#include "Library/Scene/Scene.h"

namespace al {
    class LayoutSystem;

    class LayoutInitInfo : public LayoutSceneInfo {
    public:
        void init(al::ExecuteDirector*, al::EffectSystemInfo const*, al::SceneObjHolder*,
                  al::AudioDirector const*, al::CameraDirector*, al::LayoutSystem const*,
                  al::MessageSystem const*, al::GamePadSystem const*, al::PadRumbleDirector*);

        al::MessageSystem *getMessageSystem(void) const;

        void *qword30;
        void *qword38;
        void *qword40;
        al::ExecuteDirector *mExecuteDirector;
        al::EffectSystemInfo *mEffectSysInfo;
        al::AudioDirector *mAudioDirector;
        al::LayoutSystem *mLayoutSystem;
    };
    void initLayoutInitInfo(al::LayoutInitInfo *,al::Scene const*,al::SceneInitInfo const&);
    void initLayoutInitInfo(al::LayoutInitInfo *,al::LayoutKit const*,al::SceneObjHolder *,al::AudioDirector const*,al::LayoutSystem const*,al::MessageSystem const*,al::GamePadSystem const*);
} // namespace al
