#pragma once

#include "al/scene/Scene.h"
#include "game/StageScene/StageSceneLayout.h"
#include "game/StageScene/StageSceneStatePauseMenu.h"

namespace al {
    struct LayoutTextureRenderer;
    struct SimpleAudioUser;
    struct ParabolicPath;
    struct DemoSyncedEventKeeper;
    struct ChromakeyDrawer;
    struct WipeHolder;
}

class StageScene : public al::Scene {
public:
    bool isPause() const;

    void exeAppearFromWorldWarpHole();

    sead::FixedSafeString<0x40> mStageName;
    int field_130;
    struct StageSceneStateWorldMap *mStateWorldMap;
    struct StageSceneStateShop *mStateShop;
    struct StageSceneStateSnapShot *mStateSnapShot;
    struct StageSceneStateGetShine *mStateGetShine;
    struct StageSceneStateGetShineMain *mStateGetShineMain;
    struct StageSceneStateGetShineGrand *mStateGetShineGrand;
    struct StageSceneStateCollectBgm *mStateCollectBgm;
    struct StageSceneStateCollectionList *mStateCollectionList;
    struct StageSceneStateMiniGameRanking *mStateMiniGameRanking;
    StageSceneStatePauseMenu *mStatePauseMenu;
    struct StageSceneStateCloset *mStateCloset;
    struct StageSceneStateSkipDemo *mStateSkipDemo;
    struct StageSceneStateCheckpointWarp *mStateCheckpointWarp;
    struct StageSceneStateCarryMeat *mStateCarryMeat;
    void *field_1A8;
    void *field_1B0;
    struct StageSceneStateMiss *mStateMiss;
    struct StageSceneStateYukimaruRace *mStateYukimaruRace;
    struct StageSceneStateYukimaruRaceTutorial *mStateYukimaruRaceTutorial;
    struct StageSceneStateRaceManRace *mStateRaceManRace;
    struct StageSceneStateRadicon *mStateRadicon;
    struct StageSceneStateScenarioCamera *mStateScenarioCamera;
    struct StageSceneStateRecoverLife *mStateRecoverLife;
    struct StageSceneStateGetShineMainSandWorld *mStateGetShineMainSandWorld;
    void *field_1F8;
    struct StageSceneStateWarp *field_200;
    void *field_208;
    struct ScenarioStartCameraHolder *field_210;
    sead::FixedSafeString<0x40> field_218;
    sead::FixedSafeString<0x40> field_270;
    void *qword2C8;
    GameDataHolderAccessor mHolder;
    void *qword2D8;
    al::LayoutTextureRenderer *qword2E0;
    struct PlayGuideSkip *qword2E8;
    struct CinemaCaption *qword2F0;
    StageSceneLayout *mSceneLayout;
    char field_300;
    char field_301;
    al::SimpleLayoutAppearWaitEnd *char308;
    al::SimpleLayoutAppearWaitEnd *field_310;
    al::SimpleLayoutAppearWaitEnd *field_318;
    struct ControllerGuideSnapShotCtrl *field_320;
    InputSeparator *field_328;
    al::WipeSimple *field_330;
    al::WipeHolder *field_338;
    void *field_340;
    al::WindowConfirm *field_348;
    struct MiniGameMenu *field_350;
    bool field_358;
    char gap359[15];
    char char368;
    struct MapLayout *field_370;
    al::SimpleLayoutAppearWaitEnd *field_378;
    al::LiveActorGroup *field_380;
    void *field_388;
    void *mKoopaLv1Actor;
    struct TimeBalloonNpc *mTimeBalloonNpc;
    struct ProjectItemDirector *field_3A0;
    struct Pyramid *field_3A8;
    void *field_3B0;
    al::Nerve *field_3B8;
    SceneAudioSystemPauseController *field_3C0;
    struct DemoSoundSynchronizer *mDemoSoundSynchronizer;
    al::SimpleAudioUser *mStageStartAtmosSe;
    al::SimpleAudioUser *mSePlayArea;
    al::SimpleAudioUser *mSnapShotCameraCtrlAudio;
    struct ProjectSeNamedList *field_3E8;
    void *field_3F0;
    struct TimeBalloonDirector *mTimeBalloonDirector;
    struct TimeBalloonSequenceInfo *mTimeBalloonSequenceInfo;
    void *qword408;
    void *qword410;
    sead::Vector3f qword418;
    sead::Vector3f qword424;
    void *qword430;
    int dword438;
    const al::LiveActor *field_440;
    al::ParabolicPath *field_448;
    al::LiveActor *field_450;
    void *qword458;
    int dword460;
    struct CollectBgmPlayer *qword468;
    struct CollectBgmRegister *qword470;
    struct BgmAnimeSyncDirector *qword478;
    al::DemoSyncedEventKeeper *field_480;
    void *field_488;
    int field_490;
    struct NpcEventDirector *qword498;
    al::ChromakeyDrawer *field_4A0;
    void *qword4A8;
    ProjectNfpDirector *qword4B0;
    void *qword4B8;
};
