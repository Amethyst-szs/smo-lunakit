#pragma once

#include "sead/math/seadVector.h"
#include "al/sensor/HitSensor.h"

class ExternalForceKeeper
{
public:
    ExternalForceKeeper();
    bool receiveMsg(const al::SensorMsg *message, al::HitSensor *source, al::HitSensor *target);
    void reset();
    void calcForce(sead::Vector3f *result) const;

    sead::Vector3f unkVec1 = sead::Vector3f::zero;
    sead::Vector3f unkVec2 = sead::Vector3f::zero;
};