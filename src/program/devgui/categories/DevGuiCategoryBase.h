#pragma once

#include "imgui.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"

class DevGuiCategoryBase {
public:
    DevGuiCategoryBase(const char* catName, const char* catDesc);

    virtual void updateCat();
    virtual void updateCatDisplay();

    virtual const char* getCategoryName() { return mCatName; };

private:
    const char* mCatName = nullptr;
    const char* mCatDesc = nullptr;
};