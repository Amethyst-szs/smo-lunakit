#include "PlayerHelper.h"
#include <al/area/ChangeStageInfo.h>
#include <game/GameData/GameDataHolderAccessor.h>
#include "al/util/OtherUtil.h"
#include "game/GameData/GameDataFunction.h"
#include "game/Player/PlayerAnimator.h"

namespace PlayerHelper {
void killPlayer(al::LiveActor* actor) {
    PlayerActorHakoniwa* mainPlayer = (PlayerActorHakoniwa*)al::getPlayerActor(actor, 0);

    GameDataFunction::killPlayer(GameDataHolderAccessor(actor));
    mainPlayer->startDemoPuppetable();
    al::setVelocityZero(mainPlayer);
    mainPlayer->mPlayerAnimator->endSubAnim();
    mainPlayer->mPlayerAnimator->startAnimDead();
}

void killPlayer(PlayerActorHakoniwa* mainPlayer) {
    GameDataFunction::killPlayer(GameDataHolderAccessor(mainPlayer));
    mainPlayer->startDemoPuppetable();
    al::setVelocityZero(mainPlayer);
    mainPlayer->mPlayerAnimator->endSubAnim();
    mainPlayer->mPlayerAnimator->startAnimDead();
}

void warpPlayer(const char* stageName, GameDataHolderAccessor holder) {
    ChangeStageInfo info(holder.mData, "", stageName, false, -1, ChangeStageInfo::SubScenarioType::UNK);
    GameDataFunction::tryChangeNextStage(holder, &info);
}
}  // namespace PlayerHelper