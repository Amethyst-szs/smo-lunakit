#pragma once

#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"

#include "game/GameData/GameDataFunction.h"
#include "game/Player/PlayerActorBase.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/Player/PlayerFunction.h"

#include "rs/util.hpp"

#include <cxxabi.h>

#include "program/devgui/categories/CategoryBase.h"

class CategoryInfScene : public CategoryBase {
public:
    CategoryInfScene(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCatDisplay() override;
};