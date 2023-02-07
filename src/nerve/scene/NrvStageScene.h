#pragma once

#include "nerve/util/NerveFindUtil.h"

const uintptr_t nrvStageSceneAmiibo = 0x01d8ccd0; // Freezes scene for 1/2-3/4 second
const uintptr_t nrvStageSceneAppearFromWorldWarpHole = 0x01d8cc38; // Appears kingdom header in corner
const uintptr_t nrvStageSceneArriveAtCheckpoint = 0x01d8cc20; // Le crash
const uintptr_t nrvStageSceneCloset = 0x01d8cb88; // If closet exists on map, opens menu, otherwise crash
const uintptr_t nrvStageSceneCollectBgm = 0x01d8cb68; // No crash, freezes
const uintptr_t nrvStageSceneCollectionList = 0x01d8cb70; // Opens map
const uintptr_t nrvStageSceneMiniGameRanking = 0x01d8cb78; // Crash(?)
const uintptr_t nrvStageSceneMiss = 0x01d8cbe8; // Death coins and camera, no actual death
const uintptr_t nrvStageScenePause = 0x01d8cc18; // Forces pause
const uintptr_t nrvStageScenePlay = 0x01d8cc78; // Cancels pause, otherwise no effect
const uintptr_t nrvStageSceneRaceManRace = 0x01d8cc08; // Crash
const uintptr_t nrvStageSceneRaceYukimaru = 0x01d8cbf8; // Crash
const uintptr_t nrvStageSceneRaceYukimaruTutorial = 0x01d8cc00; // Crash
const uintptr_t nrvStageSceneRadicon = 0x01d8cba0; // Does nothing
const uintptr_t nrvStageSceneShop = 0x01d8cb80; // Opens purple coin shop
const uintptr_t nrvStageSceneSkipDemo = 0x01d8cbe0; // No effect outside of demo
const uintptr_t nrvStageSceneSnapShot = 0x01d8cbc8; // Snapshot
const uintptr_t nrvStageSceneStartStageBgm = 0x01d8cb60; // No effect
const uintptr_t nrvStageSceneTimeBalloon = 0x01d8cc28; // Crash
const uintptr_t nrvStageSceneWaitStartWarpForSession = 0x01d8cce0; // No effect
const uintptr_t nrvStageSceneWaitWarpToCheckpoint = 0x01d8cc28; // Crash
const uintptr_t nrvStageSceneWarp = 0x01d8cba8; // Hat transition, then continues
const uintptr_t nrvStageSceneWarpToCheckpoint = 0x01d8ccf0; // Fade to white, crash