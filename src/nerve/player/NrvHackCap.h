#pragma once

#include "nerve/util/NerveFindUtil.h"

const uintptr_t nrvHackCapBlow = 0x01d75bf8; // Quickly returns hat towards player, endless spinning if already hidden
const uintptr_t nrvHackCapCatch = 0x01d75b50; // Catches cappy, bugged if already caught
const uintptr_t nrvHackCapHack = 0x01d75b80; // Crashes in normal scenario
const uintptr_t nrvHackCapHide = 0x01d75b60; // Returns hat and hides model
const uintptr_t nrvHackCapLockOn = 0x01d75b70; // Crash
const uintptr_t nrvHackCapRebound = 0x01d75b78; // Bounce off object
const uintptr_t nrvHackCapRescue = 0x01d75b98; // Snap back, same as Hide
const uintptr_t nrvHackCapRethrow = 0x01d75bd0; // Functionally identical to throw(?)
const uintptr_t nrvHackCapReturn = 0x01d75b68; // Brings hat back to player
const uintptr_t nrvHackCapSpinAttack = 0x01d75b88; // Breaks, gets stuck in animation
const uintptr_t nrvHackCapThrow = 0x01d75bc0; // Instantly triggers cap throw, no npc collisions, direction random(?)
const uintptr_t nrvHackCapThrowAppend = 0x01d75bd8; // Throws puppet, slight differences in behavior
const uintptr_t nrvHackCapThrowBreak = 0x01d75bc8; // Throws puppet, slight differences in behavior
const uintptr_t nrvHackCapThrowRolling = 0x01d75bb8; // Throws puppet, slight differences in behavior
const uintptr_t nrvHackCapThrowSpiral = 0x01d75bb0; // Throws puppet, slight differences in behavior
const uintptr_t nrvHackCapThrowStart = 0x01d75b90; // Throws cap, has object and enemy collisions, supports captures!
const uintptr_t nrvHackCapThrowTornado = 0x01d75ba8; // Throws puppet, slight differences in behavior
const uintptr_t nrvHackCapThrowTrample = 0x01d75be8; // Triggers puppet throw with delay to play bounce animation
const uintptr_t nrvHackCapThrowTrampleLockOn = 0x01d75bf0; // Crash
const uintptr_t nrvHackCapThrowTrampleReturn = 0x01d75ba0; // Identical to basic Trample