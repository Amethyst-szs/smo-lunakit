#pragma once

#include "Library/System/GameSystemInfo.h"

namespace al {
    class SequenceInitInfo {
        public:
            SequenceInitInfo(al::GameSystemInfo const *sysInf) : mSystemInfo(sysInf) {}
            const GameSystemInfo *mSystemInfo;
    };
}
