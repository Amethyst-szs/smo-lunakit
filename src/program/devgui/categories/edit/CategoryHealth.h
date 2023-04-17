#pragma once

#include "program/devgui/categories/CategoryBase.h"

#include "game/GameData/PlayerHitPointData.h"

class CategoryHealth : public CategoryBase {
public:
    CategoryHealth(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCat() override;
    void updateCatDisplay() override;

protected:
    PlayerHitPointData* mHitData;
    bool mIsOverride = false;
    bool mIsKidsMode = false;
    bool mIsExtendSlider = false;

    bool mIsKillPlayer = false;
    int mTargetHealth = 3;
};