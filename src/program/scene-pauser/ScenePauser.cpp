#pragma once

#include "game/StageScene/StageScene.h"

namespace {
    NERVE_IMPL(StageScene, StartStageBgm);
    NERVE_IMPL(StageScene, CollectBgm);
    NERVE_IMPL(StageScene, CollectionList);
    NERVE_IMPL(StageScene, MiniGameRanking);
    NERVE_IMPL(StageScene, Shop);
    NERVE_IMPL(StageScene, Closet);
    NERVE_IMPL(StageScene, DemoShineGet);
    NERVE_IMPL(StageScene, DemoTalk);
    NERVE_IMPL(StageScene, Radicon);
    NERVE_IMPL(StageScene, Warp);
    NERVE_IMPL(StageScene, DemoGetLifeMaxUpItem);
    NERVE_IMPL(StageScene, DemoWorldIntroCamera);
    NERVE_IMPL_(StageScene, DemoWorldIntroCameraBeforeAppearElectricDemo, DemoWorldIntroCamera);
    NERVE_IMPL(StageScene, SnapShot);
    NERVE_IMPL(StageScene, DemoShineMainGet);
    NERVE_IMPL(StageScene, DemoShineGrandGet);
    NERVE_IMPL(StageScene, SkipDemo);
    NERVE_IMPL(StageScene, Miss);
    NERVE_IMPL(StageScene, DemoCarryMeat);
    NERVE_IMPL(StageScene, RaceYukimaru);
    NERVE_IMPL(StageScene, RaceYukimaruTutorial);
    NERVE_IMPL(StageScene, RaceManRace);
    NERVE_IMPL(StageScene, DemoTitleLogo);
    NERVE_IMPL(StageScene, Pause);
    NERVE_IMPL(StageScene, ArriveAtCheckpoint);
    NERVE_IMPL(StageScene, TimeBalloon);
    NERVE_IMPL(StageScene, DemoScenarioCamera);
    NERVE_IMPL(StageScene, AppearFromWorldWarpHole);
    NERVE_IMPL_(StageScene, DemoStageStartOpening, DemoStageStart);
    NERVE_IMPL(StageScene, DemoStageStart);
    NERVE_IMPL(StageScene, DemoPlayerDown);
    NERVE_IMPL(StageScene, DemoStageStartCapManHeroTalk);
    NERVE_IMPL_(StageScene, DemoCapManHeroTalkMoonRock, DemoStageStartCapManHeroTalk);
    NERVE_IMPL(StageScene, DemoReturnToHome);
    NERVE_IMPL(StageScene, DemoHackStart);
    NERVE_IMPL(StageScene, Play);
    NERVE_IMPL_(StageScene, DemoWithPlayerUseCoinNoFirst, DemoWithPlayerUseCoin);
    NERVE_IMPL(StageScene, DemoDamageStopPlayer);
    NERVE_IMPL(StageScene, DemoSceneStartPlayerWalk);
    NERVE_IMPL(StageScene, DemoRiseMapParts);
    NERVE_IMPL(StageScene, DemoShineChipComplete);
    NERVE_IMPL(StageScene, DemoHackStartFirst);
    NERVE_IMPL(StageScene, DemoNormalBazookaElectric);
    NERVE_IMPL(StageScene, DemoWithPlayerUseCoin);
    NERVE_IMPL(StageScene, DemoWithPlayer);
    NERVE_IMPL(StageScene, DemoNormal);
    NERVE_IMPL(StageScene, Amiibo);
    NERVE_IMPL_(StageScene, DemoStageStartElectricDemo, DemoStageStart);
    NERVE_IMPL(StageScene, WaitStartWarpForSession);
    NERVE_IMPL(StageScene, DemoCountCoin);
    NERVE_IMPL(StageScene, WarpToCheckpoint);
    NERVE_IMPL(StageScene, DemoAppearFromHome);
    NERVE_IMPL(StageScene, DemoRisePyramid);
    NERVE_IMPL(StageScene, WaitWarpToCheckpoint);
    struct {
        NERVE_MAKE(StageScene, StartStageBgm);
        NERVE_MAKE(StageScene, CollectBgm);
        NERVE_MAKE(StageScene, CollectionList);
        NERVE_MAKE(StageScene, MiniGameRanking);
        NERVE_MAKE(StageScene, Shop);
        NERVE_MAKE(StageScene, Closet);
        NERVE_MAKE(StageScene, DemoShineGet);
        NERVE_MAKE(StageScene, DemoTalk);
        NERVE_MAKE(StageScene, Radicon);
        NERVE_MAKE(StageScene, Warp);
        NERVE_MAKE(StageScene, DemoGetLifeMaxUpItem);
        NERVE_MAKE(StageScene, DemoWorldIntroCamera);
        NERVE_MAKE(StageScene, DemoWorldIntroCameraBeforeAppearElectricDemo);
        NERVE_MAKE(StageScene, SnapShot);
        NERVE_MAKE(StageScene, DemoShineMainGet);
        NERVE_MAKE(StageScene, DemoShineGrandGet);
        NERVE_MAKE(StageScene, SkipDemo);
        NERVE_MAKE(StageScene, Miss);
        NERVE_MAKE(StageScene, DemoCarryMeat);
        NERVE_MAKE(StageScene, RaceYukimaru);
        NERVE_MAKE(StageScene, RaceYukimaruTutorial);
        NERVE_MAKE(StageScene, RaceManRace);
        NERVE_MAKE(StageScene, DemoTitleLogo);
        NERVE_MAKE(StageScene, Pause);
        NERVE_MAKE(StageScene, ArriveAtCheckpoint);
        NERVE_MAKE(StageScene, TimeBalloon);
        NERVE_MAKE(StageScene, DemoScenarioCamera);
        NERVE_MAKE(StageScene, AppearFromWorldWarpHole);
        NERVE_MAKE(StageScene, DemoStageStartOpening);
        NERVE_MAKE(StageScene, DemoStageStart);
        NERVE_MAKE(StageScene, DemoPlayerDown);
        NERVE_MAKE(StageScene, DemoStageStartCapManHeroTalk);
        NERVE_MAKE(StageScene, DemoCapManHeroTalkMoonRock);
        NERVE_MAKE(StageScene, DemoReturnToHome);
        NERVE_MAKE(StageScene, DemoHackStart);
        NERVE_MAKE(StageScene, Play);
        NERVE_MAKE(StageScene, DemoWithPlayerUseCoinNoFirst);
        NERVE_MAKE(StageScene, DemoDamageStopPlayer);
        NERVE_MAKE(StageScene, DemoSceneStartPlayerWalk);
        NERVE_MAKE(StageScene, DemoRiseMapParts);
        NERVE_MAKE(StageScene, DemoShineChipComplete);
        NERVE_MAKE(StageScene, DemoHackStartFirst);
        NERVE_MAKE(StageScene, DemoNormalBazookaElectric);
        NERVE_MAKE(StageScene, DemoWithPlayerUseCoin);
        NERVE_MAKE(StageScene, DemoWithPlayer);
        NERVE_MAKE(StageScene, DemoNormal);
        NERVE_MAKE(StageScene, Amiibo);
        NERVE_MAKE(StageScene, DemoStageStartElectricDemo);
        NERVE_MAKE(StageScene, WaitStartWarpForSession);
        NERVE_MAKE(StageScene, DemoCountCoin);
        NERVE_MAKE(StageScene, WarpToCheckpoint);
        NERVE_MAKE(StageScene, DemoAppearFromHome);
        NERVE_MAKE(StageScene, DemoRisePyramid);
        NERVE_MAKE(StageScene, WaitWarpToCheckpoint);
    } nrvStageScene;
}

namespace rs {
    void endDemoCommonProc(al::Scene* scene, ProjectItemDirector* projItemDir);
    bool isPlayerHackRadiconNpc(const al::LiveActor* actor);
    void setKidsModeLayoutDisable(const al::IUseSceneObjHolder*);
    void killCoinColletHintEffect(const al::IUseSceneObjHolder*);
    void updateKitListDemoPlayerWithPauseEffect(al::Scene*);
    bool isActiveDemo(al::Scene*);
} // namespace rs

void StageScene::exeDemoGetLifeMaxUpItem() {
    if (mUpdateKitAndGraphics) {
        al::updateKit(this);
        al::updateGraphicsPrev(this);
        mUpdateKitAndGraphics = false;
        return;
    }
    if (al::updateNerveState(this)) {
        rs::endDemoCommonProc(this, this->mProjectItemDirector);
        al::updateKitListPostOnNerveEnd(this);
        al::setNerve(this, &nrvStageScene.Play);
        return;
    }
    al::updateKitListPostOnNerveEnd(this);
}

void StageScene::exeDemoHackStart() {
    auto dataHolder = GameDataHolderAccessor(this);
    bool isRadicon;
    if (GameDataFunction::isMainStage(dataHolder)) {
        isRadicon = false;
    } else {
        isRadicon = rs::isPlayerHackRadiconNpc(this->mDemoShine);
    }

    if (al::isFirstStep(this)) {
        if (isRadicon) {
            mStageSceneLayout->end();
            rs::setKidsModeLayoutDisable(this);
        }
        rs::killCoinColletHintEffect(this);
    }
    al::updateKitListPrev(this);
    rs::updateKitListDemoPlayerWithPauseEffect(this);

    if (isRadicon)
        mStageSceneLayout->update();

    al::updateKitListPostDemoWithPauseNormalEffect(this);
    if (!rs::isActiveDemo(this)) {
        endDemoAndChangeNerve();
        if (isRadicon) {
            al::setNerve(this, &nrvStageScene.Radicon);
        }
    } else {
        al::updateKitListPostOnNerveEnd(this);
    }
}