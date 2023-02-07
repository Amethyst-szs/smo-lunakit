#pragma once

#include "program/devgui/categories/DevGuiCategoryBase.h"

class DevGuiCategoryHealth : public DevGuiCategoryBase {
public:
    DevGuiCategoryHealth(const char* catName, const char* catDesc);

    void updateCat() override;
    void updateCatDisplay() override;

protected:
    PlayerHitPointData* mHitData;
    bool mIsOverrideHealth = false;
    bool mIsKillPlayer = false;
    int mTargetHealth = 3;
};