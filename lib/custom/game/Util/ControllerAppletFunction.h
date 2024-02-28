#pragma once

namespace al {
class GamePadSystem;
}

class ControllerAppletFunction {
public:
    static bool connectControllerSinglePlay(al::GamePadSystem*);
    static bool connectControllerSeparatePlay(al::GamePadSystem*);
};
