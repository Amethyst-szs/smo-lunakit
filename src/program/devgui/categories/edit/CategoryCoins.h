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

class CategoryCoins : public CategoryBase {
public:
    CategoryCoins(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCat() override;
    void updateCatDisplay() override;

protected:
GameDataHolder* holder;
GameDataFile* file;
StageScene* scene;
HakoniwaSequence* gameSeq;
bool mIsOverrideCoins = false;
int mTargetCoins = 100;
bool mIsExtendSlider = false;
};