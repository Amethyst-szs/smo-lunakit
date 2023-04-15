#pragma once

__attribute__((used)) static const char* flagNames[] = {
    "Dead",
    "Clipped",
    "Cannot Clip",
    "Draw Clipped",
    "Calc Anim On",
    "Model Visible",
    "No Collide",
    "Unknown 8",
    "Valid Mat Code",
    "Area Target",
    "Move FX Sensor",
    "Unknown 12"
};

namespace al {

class LiveActorFlag {
public:
    LiveActorFlag();

    bool mIsDead;
    bool mIsClipped;
    bool mIsClippingInvalidated;
    bool mIsDrawClipped;
    bool mIsCalcAnimOn;
    bool mIsModelVisible;
    bool mIsNoCollide;
    bool mIsFlag8;
    bool mIsMaterialCodeValid;
    bool mIsAreaTarget;
    bool mIsUpdateMovementEffectAudioCollisionSensor;
    bool mIsFlag12;
};

static_assert(sizeof(LiveActorFlag) == 0xC, "");

}  // namespace al