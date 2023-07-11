#pragma once

#include "al/LiveActor/LiveActor.h"

namespace rs
{
    void initItemByPlacementInfo(al::LiveActor *, al::ActorInitInfo const &, bool);
    float setShadowDropLength(al::LiveActor *,al::ActorInitInfo const&,char const*);
    bool isSeparatePlay(al::IUseSceneObjHolder const*);
    void changeSeparatePlayMode(al::Scene*, bool);
} // namespace rs
