#pragma once

#include "al/scene/Scene.h"
#include "al/sequence/Sequence.h"

#include "game/GameData/GameDataHolder.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/Player/PlayerActorBase.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/StageScene/StageScene.h"

#include "rs/util.hpp"

// Is checks
bool isInScene();
bool isInScene(al::Scene* scene);
bool isInStageScene();
bool isInStageScene(al::Scene* scene);
bool tryReloadStage();

// Safe getters
al::Sequence* tryGetSequence();
HakoniwaSequence* tryGetHakoniwaSequence();

al::Scene* tryGetScene();
al::Scene* tryGetScene(al::Sequence* curSequence);
al::Scene* tryGetScene(HakoniwaSequence* curSequence);
StageScene* tryGetStageScene();
StageScene* tryGetStageScene(HakoniwaSequence* curSequence);

GameDataHolder* tryGetGameDataHolder();
GameDataHolder* tryGetGameDataHolder(HakoniwaSequence* curSequence);
GameDataHolder* tryGetGameDataHolder(StageScene* scene);
GameDataHolderAccessor* tryGetGameDataHolderAccess();
GameDataHolderAccessor* tryGetGameDataHolderAccess(HakoniwaSequence* curSequence);
GameDataHolderAccessor* tryGetGameDataHolderAccess(StageScene* scene);

PlayerActorBase* tryGetPlayerActor();
PlayerActorBase* tryGetPlayerActor(HakoniwaSequence* curSequence);
PlayerActorBase* tryGetPlayerActor(StageScene* scene);
PlayerActorHakoniwa* tryGetPlayerActorHakoniwa();
PlayerActorHakoniwa* tryGetPlayerActorHakoniwa(HakoniwaSequence* curSequence);
PlayerActorHakoniwa* tryGetPlayerActorHakoniwa(al::Scene* scene);