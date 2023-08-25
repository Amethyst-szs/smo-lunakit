#pragma once

#include <sead/controller/seadController.h>

namespace al {
    class NpadController : public sead::Controller {
    public:
        int mIndexControllerMode;
        int mNpadId;
        int unk;
        int mPadAccelerationDeviceNum;
    };
}