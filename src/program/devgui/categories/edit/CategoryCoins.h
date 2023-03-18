#pragma once

#include "program/devgui/categories/CategoryBase.h"

class CategoryCoins : public CategoryBase {
public:
    CategoryCoins(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCat() override;
    void updateCatDisplay() override;

private:
    bool mIsOverrideCoins = false;
    bool mIsExtendSlider = false;
    int mTargetCoins = 100;
};