#pragma once

#include "game/System/GameDataHolder.h"

namespace SaveDataAccessFunction {

    void startSaveDataInitSync(GameDataHolder *);

    void startSaveDataReadSync(GameDataHolder *);
}
