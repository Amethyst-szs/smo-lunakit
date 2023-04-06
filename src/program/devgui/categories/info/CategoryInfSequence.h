#pragma once

#include "al/sequence/Sequence.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"

#include "game/GameData/GameDataFunction.h"

#include <cxxabi.h>

#include "program/devgui/categories/CategoryBase.h"

class CategoryInfSequence : public CategoryBase {
public:
    CategoryInfSequence(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCatDisplay() override;
};