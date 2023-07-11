#pragma once

#include "al/gamepad/util.h"

class ControllerAppletFunction {
    public:
        static bool connectControllerSinglePlay(al::GamePadSystem *);
        static bool connectControllerSeparatePlay(al::GamePadSystem *);
};