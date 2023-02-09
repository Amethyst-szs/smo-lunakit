#pragma once

#include "program/devgui/categories/CategoryBase.h"

class CategoryHealth : public CategoryBase {
public:
    CategoryHealth(const char* catName, const char* catDesc);

    void updateCat() override;
    void updateCatDisplay() override;

protected:
    PlayerHitPointData* mHitData;
    bool mIsOverride = false;
    bool mIsKidsMode = false;

    bool mIsKillPlayer = false;
    int mTargetHealth = 3;
};