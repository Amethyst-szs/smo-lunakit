#pragma once

#include "program/devgui/categories/CategoryBase.h"

class CategorySpeed : public CategoryBase {
public:
    CategorySpeed(const char* catName, const char* catDesc);

    void updateCat() override;
    void updateCatDisplay() override;

protected:
bool mIsOverride = false;
int mTargetSpeed = 14.0f;
};