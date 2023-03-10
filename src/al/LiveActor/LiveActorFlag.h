#pragma once

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