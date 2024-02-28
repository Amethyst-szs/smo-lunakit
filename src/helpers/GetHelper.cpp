#include "helpers/GetHelper.h"

#include "Library/LiveActor/LiveActor.h"
#include "Library/Nerve/Nerve.h"
#include "Library/Nerve/NerveKeeper.h"
#include "Library/Nerve/NerveStateBase.h"
#include "Library/Nerve/NerveStateCtrl.h"
#include "al/util.hpp"
#include "logger/Logger.hpp"

#include "game/System/GameDataFunction.h"
#include "game/System/Application.h"
#include "game/System/GameSystem.h"

bool isInScene() {
    al::Sequence* mSequence = GameSystemFunction::getGameSystem()->mSequence;
    if (mSequence && al::isEqualString(mSequence->mName.cstr(), "HakoniwaSequence")) {
        auto curScene = mSequence->mCurrentScene;

        return curScene && curScene->mIsAlive;
    }

    return false;
}

bool isInScene(al::Scene* curScene) {
    return curScene && curScene->mIsAlive;
}

bool isInStageScene() {
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;
    if (curSequence && al::isEqualString(curSequence->mName.cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        auto curScene = gameSeq->curScene;

        return curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene");
    }

    return false;
}

bool isInStageScene(al::Scene* scene) {
    return scene && scene->mIsAlive && al::isEqualString(scene->mName.cstr(), "StageScene");
}

al::Sequence* tryGetSequence() {
    return GameSystemFunction::getGameSystem()->mSequence;
}

HakoniwaSequence* tryGetHakoniwaSequence() {
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;
    if (curSequence && al::isEqualString(curSequence->mName.cstr(), "HakoniwaSequence")) {
        return (HakoniwaSequence*)curSequence;
    }

    return nullptr;
}

al::Scene* tryGetScene() {
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;

    if (curSequence && al::isEqualString(curSequence->mName.cstr(), "HakoniwaSequence")) {
        auto curScene = curSequence->mCurrentScene;

        if (curScene && curScene->mIsAlive)
            return curScene;
    }

    return nullptr;
}

al::Scene* tryGetScene(al::Sequence* curSequence) {
    auto curScene = curSequence->mCurrentScene;

    if (curScene && curScene->mIsAlive)
        return curScene;

    return nullptr;
}

al::Scene* tryGetScene(HakoniwaSequence* curSequence) {
    auto curScene = curSequence->mCurrentScene;

    if (curScene && curScene->mIsAlive)
        return curScene;

    return nullptr;
}

StageScene* tryGetStageScene() {
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;
    if (curSequence && al::isEqualString(curSequence->mName.cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        auto curScene = gameSeq->curScene;

        if (curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene"))
            return (StageScene*)gameSeq->curScene;
    }

    return nullptr;
}

StageScene* tryGetStageScene(HakoniwaSequence* curSequence) {
    auto curScene = curSequence->curScene;

    if (curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene"))
        return (StageScene*)curScene;

    return nullptr;
}

GameDataHolder* tryGetGameDataHolder() {
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;
    if (curSequence && al::isEqualString(curSequence->mName.cstr(), "HakoniwaSequence")) {
        HakoniwaSequence* gameSequence = (HakoniwaSequence*)curSequence;
        return gameSequence->mGameDataHolder.mData;
    }

    return nullptr;
}

GameDataHolder* tryGetGameDataHolder(HakoniwaSequence* curSequence) {
    return curSequence->mGameDataHolder.mData;
}

GameDataHolder* tryGetGameDataHolder(StageScene* scene) {
    return scene->mGameDataHolder.mData;
}

GameDataHolderAccessor* tryGetGameDataHolderAccess() {
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;
    if (curSequence && al::isEqualString(curSequence->mName.cstr(), "HakoniwaSequence")) {
        HakoniwaSequence* gameSequence = (HakoniwaSequence*)curSequence;
        return &gameSequence->mGameDataHolder;
    }

    return nullptr;
}

GameDataHolderAccessor* tryGetGameDataHolderAccess(HakoniwaSequence* curSequence) {
    return &curSequence->mGameDataHolder;
}

GameDataHolderAccessor* tryGetGameDataHolderAccess(StageScene* scene) {
    return &scene->mGameDataHolder;
}

PlayerActorBase* tryGetPlayerActor() {
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;
    if (curSequence && al::isEqualString(curSequence->mName.cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        auto curScene = gameSeq->curScene;

        if (curScene && curScene->mIsAlive) {
            return tryGetPlayerActor(curScene);
        }
    }

    return nullptr;
}

PlayerActorBase* tryGetPlayerActor(HakoniwaSequence* curSequence) {
    auto curScene = curSequence->curScene;

    if (curScene && curScene->mIsAlive) {
        return tryGetPlayerActor(curScene);
    }

    return nullptr;
}

PlayerActorBase* tryGetPlayerActor(StageScene* scene) {
    if (!isInStageScene(scene))
        return nullptr;

    al::PlayerHolder* pHolder = al::getScenePlayerHolder(scene);
    if (!pHolder)
        return nullptr;

    PlayerActorBase* playerBase = al::tryGetPlayerActor(pHolder, 0);
    return playerBase;
}

PlayerActorHakoniwa* tryGetPlayerActorHakoniwa() {
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mSequence;
    if (curSequence && al::isEqualString(curSequence->mName.cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        auto curScene = gameSeq->curScene;

        if (curScene)
            return tryGetPlayerActorHakoniwa(curScene);
    }

    return nullptr;
}

PlayerActorHakoniwa* tryGetPlayerActorHakoniwa(HakoniwaSequence* curSequence) {
    auto curScene = curSequence->curScene;

    if (curScene)
        return tryGetPlayerActorHakoniwa(curScene);

    return nullptr;
}

PlayerActorHakoniwa* tryGetPlayerActorHakoniwa(al::Scene* scene) {
    if (!isInStageScene())
        return nullptr;

    PlayerActorBase* playerBase = rs::getPlayerActor(scene);

    if (al::isEqualString(typeid(*playerBase).name(), typeid(PlayerActorHakoniwa).name()))
        return (PlayerActorHakoniwa*)playerBase;

    return nullptr;
}

bool tryReloadStage() {
    GameDataHolder* holder = tryGetGameDataHolder();
    if (!holder)
        return false;
    StageScene* scene = tryGetStageScene();
    if (!scene)
        return false;

    ChangeStageInfo stageInfo(holder, "start", GameDataFunction::getCurrentStageName(scene->mGameDataHolder), false, -1,
                              ChangeStageInfo::SubScenarioType::UNK);
    GameDataFunction::tryChangeNextStage(scene->mGameDataHolder, &stageInfo);
    return true;
}
