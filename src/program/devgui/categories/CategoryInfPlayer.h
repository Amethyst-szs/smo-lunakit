#pragma once

#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"

#include "game/GameData/GameDataFunction.h"
#include "game/Player/PlayerActorBase.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/Player/PlayerFunction.h"

#include "rs/util.hpp"

#include "program/devgui/categories/CategoryBase.h"

class CategoryInfPlayer : public CategoryBase {
public:
    CategoryInfPlayer(const char* catName, const char* catDesc);

    void updateCatDisplay() override;
};