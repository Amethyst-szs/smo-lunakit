#pragma once

#include "Library/Effect/EffectKeeper.h"

namespace al {
    class ActionEffectCtrl {
        public:
            void startAction(char const *);
            IUseEffectKeeper *mEffectKeeper;
    };
}
