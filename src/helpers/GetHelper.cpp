#include "helpers/GetHelper.h"

bool isInScene()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        auto curScene = curSequence->mCurrentScene;

        return curScene && curScene->mIsAlive;
    }

    return false;
}

bool isInScene(al::Scene* curScene)
{
    return curScene && curScene->mIsAlive;
}

bool isInStageScene()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        auto curScene = gameSeq->curScene;

        return curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene");
    }

    return false;
}

bool isInStageScene(StageScene* curScene)
{
    return curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene");
}

al::Sequence* tryGetSequence()
{
    return GameSystemFunction::getGameSystem()->mCurSequence;
}

HakoniwaSequence* tryGetHakoniwaSequence()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        return (HakoniwaSequence*)curSequence;
    }

    return nullptr;
}

al::Scene* tryGetScene()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;

    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        auto curScene = curSequence->mCurrentScene;

        if (curScene && curScene->mIsAlive)
            return curScene;
    }

    return nullptr;
}

al::Scene* tryGetScene(al::Sequence* curSequence)
{
    auto curScene = curSequence->mCurrentScene;

    if (curScene && curScene->mIsAlive)
        return curScene;

    return nullptr;
}

al::Scene* tryGetScene(HakoniwaSequence* curSequence)
{
    auto curScene = curSequence->mCurrentScene;

    if (curScene && curScene->mIsAlive)
        return curScene;

    return nullptr;
}

StageScene* tryGetStageScene()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        auto curScene = gameSeq->curScene;

        if (curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene"))
            return (StageScene*)gameSeq->curScene;
    }

    return nullptr;
}

StageScene* tryGetStageScene(HakoniwaSequence* curSequence)
{
    auto curScene = curSequence->curScene;

    if (curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene"))
        return (StageScene*)curScene;

    return nullptr;
}

GameDataHolder* tryGetGameDataHolder()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        HakoniwaSequence* gameSequence = (HakoniwaSequence*)curSequence;
        return gameSequence->mGameDataHolder.mData;
    }

    return nullptr;
}

GameDataHolder* tryGetGameDataHolder(HakoniwaSequence* curSequence)
{
    return curSequence->mGameDataHolder.mData;
}

GameDataHolder* tryGetGameDataHolder(StageScene* scene)
{
    return scene->mHolder.mData;
}

GameDataHolderAccessor* tryGetGameDataHolderAccess()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        HakoniwaSequence* gameSequence = (HakoniwaSequence*)curSequence;
        return &gameSequence->mGameDataHolder;
    }

    return nullptr;
}

GameDataHolderAccessor* tryGetGameDataHolderAccess(HakoniwaSequence* curSequence)
{
    return &curSequence->mGameDataHolder;
}

GameDataHolderAccessor* tryGetGameDataHolderAccess(StageScene* scene)
{
    return &scene->mHolder;
}

PlayerActorBase* tryGetPlayerActor()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        auto curScene = gameSeq->curScene;

        if (curScene && curScene->mIsAlive) {
            if(!isInStageScene(curScene))
                return nullptr;

            al::PlayerHolder* pHolder = al::getScenePlayerHolder(curScene);
            if(!pHolder)
                return nullptr;

            PlayerActorBase* playerBase = al::tryGetPlayerActor(pHolder, 0);
            return playerBase;
        }
    }

    return nullptr;
}

PlayerActorBase* tryGetPlayerActor(HakoniwaSequence* curSequence)
{
    auto curScene = curSequence->curScene;

    if (curScene && curScene->mIsAlive) {
        if(!isInStageScene(curScene))
            return nullptr;

        al::PlayerHolder* pHolder = al::getScenePlayerHolder(curScene);
        if(!pHolder)
            return nullptr;

        PlayerActorBase* playerBase = al::tryGetPlayerActor(pHolder, 0);
        return playerBase;
    }

    return nullptr;
}

PlayerActorBase* tryGetPlayerActor(StageScene* scene)
{
    if(!isInStageScene(scene))
        return nullptr;

    al::PlayerHolder* pHolder = al::getScenePlayerHolder(scene);
    if(!pHolder)
        return nullptr;

    PlayerActorBase* playerBase = al::tryGetPlayerActor(pHolder, 0);
    return playerBase;
}

PlayerActorHakoniwa* tryGetPlayerActorHakoniwa()
{
    al::Sequence* curSequence = GameSystemFunction::getGameSystem()->mCurSequence;
    if (curSequence && al::isEqualString(curSequence->getName().cstr(), "HakoniwaSequence")) {
        auto gameSeq = (HakoniwaSequence*)curSequence;
        auto curScene = gameSeq->curScene;

        if (curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene")) {
            StageScene* stageScene = (StageScene*)gameSeq->curScene;
            PlayerActorBase* playerBase = rs::getPlayerActor(stageScene);

            bool isYukimaru = !playerBase->getPlayerInfo();

            if (!isYukimaru)
                return (PlayerActorHakoniwa*)playerBase;
        }
    }

    return nullptr;
}

PlayerActorHakoniwa* tryGetPlayerActorHakoniwa(HakoniwaSequence* curSequence)
{
    auto curScene = curSequence->curScene;

    if (curScene && curScene->mIsAlive && al::isEqualString(curScene->mName.cstr(), "StageScene")) {
        StageScene* stageScene = (StageScene*)curSequence->curScene;
        PlayerActorBase* playerBase = rs::getPlayerActor(stageScene);

        bool isYukimaru = !playerBase->getPlayerInfo();

        if (!isYukimaru)
            return (PlayerActorHakoniwa*)playerBase;
    }

    return nullptr;
}

PlayerActorHakoniwa* tryGetPlayerActorHakoniwa(StageScene* scene)
{
    PlayerActorBase* playerBase = rs::getPlayerActor(scene);
    bool isYukimaru = !playerBase->getPlayerInfo();

    if (!isYukimaru)
        return (PlayerActorHakoniwa*)playerBase;

    return nullptr;
}