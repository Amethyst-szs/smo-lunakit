#pragma once

#include "game/Player/PlayerActorHakoniwa.h"

namespace PlayerHelper {
    void killPlayer(al::LiveActor *actor);

    void killPlayer(PlayerActorHakoniwa *mainPlayer);

    void warpPlayer(const char *stageName, GameDataHolderAccessor holder);
};
