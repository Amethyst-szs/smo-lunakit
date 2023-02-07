#pragma once

#include "program/SequenceUtil.h"
#include "imgui.h"

class DevGuiCategoryBase {
public:
    DevGuiCategoryBase(const char* catName, const char* catDesc);

    virtual void updateCat();
    virtual void updateCatDisplay();

    virtual const char* getCategoryName() { return mCatName; };

protected:
    const char* mCatName = nullptr;
    const char* mCatDesc = nullptr;
};