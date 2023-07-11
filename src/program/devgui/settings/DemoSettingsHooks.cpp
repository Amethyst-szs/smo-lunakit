#include "SettingsHooks.h"

#include "logger/Logger.hpp"

#include "MassHookDefine.h"

namespace patch = exl::patch;
namespace inst = exl::armv8::inst;
namespace reg = exl::armv8::reg;


/*
 * So I found out that none of these <class>::isFirstDemoSkip() functions actually do anything... oops!
 */

MASS_HOOK_DEFINER(
//    BossForestHook,
//    BossKnuckleHook,
//    BossMagmaHook,
//    BossRaidHook,
//    BossStateTalkHook,
//    GiantWanderBossHook,
//    GolemClimbHook,
//    KoopaChurchHook,
//    KoopaStateHook,
//    KoopaBattleStartHook,
//    KoopaStateClashHook,
//    MofumofuHook,
//    StateGateKeeperHook,
//    ScenarioStartHook,
//    DemoStateHackHook,
//    StageEventDemoHook,
//    CarryMeatHook,
//    MoonRockHook,
//    ShineTowerHook,
//    OpeningStageHook,
//    StageSceneIntroHook
    RsDemoHook,
    FirstDemoScenarioHook,
    FirstDemoWorldHook,
    FirstDemoMoonRockHook,
    ShowDemoHackHook
    )

void exlSetupDemoHooks() {
//    BossForestHook::InstallAtSymbol("_ZNK10BossForest11isFirstDemoEv");
//    BossKnuckleHook::InstallAtSymbol("_ZNK11BossKnuckle11isFirstDemoEv");
//    BossMagmaHook::InstallAtSymbol("_ZNK9BossMagma11isFirstDemoEv");
//    BossRaidHook::InstallAtSymbol("_ZNK8BossRaid11isFirstDemoEv");
//    BossStateTalkHook::InstallAtSymbol("_ZNK17BossStateTalkDemo11isFirstDemoEv");
//    GiantWanderBossHook::InstallAtSymbol("_ZNK15GiantWanderBoss11isFirstDemoEv");
//    GolemClimbHook::InstallAtSymbol("_ZNK10GolemClimb11isFirstDemoEv");
//    KoopaChurchHook::InstallAtSymbol("_ZNK11KoopaChurch11isFirstDemoEv");
//    KoopaStateHook::InstallAtSymbol("_ZNK30KoopaStateDeadAndDemoBattleEnd11isFirstDemoEv");
//    KoopaBattleStartHook::InstallAtSymbol("_ZNK25KoopaStateDemoBattleStart11isFirstDemoEv");
//    KoopaStateClashHook::InstallAtSymbol("_ZNK27KoopaStateDemoClashBasement11isFirstDemoEv");
//    MofumofuHook::InstallAtSymbol("_ZNK8Mofumofu11isFirstDemoEv");
//    StateGateKeeperHook::InstallAtSymbol("_ZNK30StateGateKeeperBattleStartDemo11isFirstDemoEv");
//    ScenarioStartHook::InstallAtSymbol("_ZNK19ScenarioStartCamera11isFirstDemoEv");
//    DemoStateHackHook::InstallAtSymbol("_ZNK18DemoStateHackFirst11isFirstDemoEv");
//    StageEventDemoHook::InstallAtSymbol("_ZNK14StageEventDemo11isFirstDemoEv");
//    CarryMeatHook::InstallAtSymbol("_ZNK9CarryMeat11isFirstDemoEv");
//    MoonRockHook::InstallAtSymbol("_ZNK8MoonRock11isFirstDemoEv");
//    ShineTowerHook::InstallAtSymbol("_ZNK16ShineTowerRocket11isFirstDemoEv");
//    OpeningStageHook::InstallAtSymbol("_ZNK27OpeningStageStartCapManHero11isFirstDemoEv");
//    StageSceneIntroHook::InstallAtSymbol("_ZNK31StageSceneStateWorldIntroCamera11isFirstDemoEv");
    RsDemoHook::InstallAtSymbol("_ZN2rs11isFirstDemoEPKN2al5SceneE");
    FirstDemoScenarioHook::InstallAtSymbol("_ZN2rs30isFirstDemoScenarioStartCameraEPKN2al9LiveActorE");
    FirstDemoWorldHook::InstallAtSymbol("_ZN2rs27isFirstDemoWorldIntroCameraEPKN2al5SceneE");
    FirstDemoMoonRockHook::InstallAtSymbol("_ZNK12MoonRockData38isEnableShowDemoAfterOpenMoonRockFirstEv");
    ShowDemoHackHook::InstallAtSymbol("_ZNK18DemoStateHackFirst20isEnableShowHackDemoEv");

}