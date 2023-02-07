#pragma once

#include "nerve/util/NerveFindUtil.h"

const uintptr_t nrvPlayerActorHakoniwaAbyss = 0x01d789f0; // Falling animation, doesn't collide with objects
const uintptr_t nrvPlayerActorHakoniwaBind = 0x01d789e0; // Instantly cancelled with no object to bind to
const uintptr_t nrvPlayerActorHakoniwaCamera = 0x01d789e8; // First person camera
const uintptr_t nrvPlayerActorHakoniwaCapCatchPop = 0x01d78950; // Rainbow Spin
const uintptr_t nrvPlayerActorHakoniwaDamage = 0x01d789b0; // Bonk
const uintptr_t nrvPlayerActorHakoniwaDamageFire = 0x01d789c0;
const uintptr_t nrvPlayerActorHakoniwaDamageSwim = 0x01d789b8; // Only works when in a WaterArea, does not actually require swimming
const uintptr_t nrvPlayerActorHakoniwaDead = 0x01d78a00; // Locks player, like Demo
const uintptr_t nrvPlayerActorHakoniwaDemo = 0x01d789f8; // Locks player in place
const uintptr_t nrvPlayerActorHakoniwaEndHack = 0x01d789d8; // Stutters, no noticeable affect
const uintptr_t nrvPlayerActorHakoniwaFall = 0x01d78910;
const uintptr_t nrvPlayerActorHakoniwaGrabCeil = 0x01d78968; // Warps player to 0x 0y 0z
const uintptr_t nrvPlayerActorHakoniwaHack = 0x01d789d0; // No affect on normal Mario, replays capture anim if captured
const uintptr_t nrvPlayerActorHakoniwaHeadSliding = 0x01d78980; // Triggers dive
const uintptr_t nrvPlayerActorHakoniwaHipDrop = 0x01d78978; // Trigger ground pound
const uintptr_t nrvPlayerActorHakoniwaJump = 0x01d78948; // Triggers jump, can push up midair, only counts up jump count on ground
const uintptr_t nrvPlayerActorHakoniwaLongJump = 0x01d78988;
const uintptr_t nrvPlayerActorHakoniwaPoleClimb = 0x01d78970; // Warps to 0x 0y 0z without valid pole
const uintptr_t nrvPlayerActorHakoniwaPress = 0x01d789c8; // Similar affect to Dead and Demo
const uintptr_t nrvPlayerActorHakoniwaRise = 0x01d789a0; // Game crash
const uintptr_t nrvPlayerActorHakoniwaRolling = 0x01d78938; // Starts a roll, slightly odd momentum
const uintptr_t nrvPlayerActorHakoniwaRun = 0x01d78928; // Does nothing
const uintptr_t nrvPlayerActorHakoniwaSandGeyser = 0x01d78998; // Pushes upwards
const uintptr_t nrvPlayerActorHakoniwaSandSink = 0x01d78990; // No affect
const uintptr_t nrvPlayerActorHakoniwaSlope = 0x01d78930; // Starts the steep/slippery slope slide
const uintptr_t nrvPlayerActorHakoniwaSpinCap = 0x01d78940; // Throws cappy, even if cappy is already out
const uintptr_t nrvPlayerActorHakoniwaSquat = 0x01d78920; // Triggers crouch
const uintptr_t nrvPlayerActorHakoniwaSwim = 0x01d789a8; // Generic state, only applicable in water
const uintptr_t nrvPlayerActorHakoniwaWait = 0x01d78918; // Generic state
const uintptr_t nrvPlayerActorHakoniwaWallAir = 0x01d78958; // Warps player to last wall they touched
const uintptr_t nrvPlayerActorHakoniwaWallCatch = 0x01d78960; // Warps to 0x 0y 0z