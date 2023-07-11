#pragma once

#include "math/seadVector.h"
#include "sead/controller/seadControllerAddon.h"

namespace al {
class PadGyroAddon : public sead::ControllerAddon {
    SEAD_RTTI_OVERRIDE(PadGyroAddon, sead::ControllerAddon);
    PadGyroAddon(sead::Controller*, int);
    ~PadGyroAddon() override;
public:
    bool calc() override;
    bool tryUpdateGyroStatus();
    void getPose(sead::Vector3f* roll, sead::Vector3f* pitch, sead::Vector3f* yaw);
public:
    char _padding[0x4];
    sead::Matrix33f mDirection; // 0x2C
    sead::Vector3f mAngularVel; // 0x50
};

}