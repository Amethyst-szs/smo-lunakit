#pragma once

#include "program/devgui/categories/CategoryBase.h"

typedef int ImGuiComboFlags; // Forward declaration

class CategoryOutfit : public CategoryBase {
public:
    CategoryOutfit(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCat() override;
    void updateCatDisplay() override;

private:
    void drawDropdown(const char* header, const char* options[], const int totalOptions, const char** output);

    bool mIsOverride = false;
    bool mIsReloadScene = false;

    ImGuiComboFlags mComboFlags = 0;
    int mTotalBody = -1;
    int mTotalCap = -1;
    const char* mTargetBody = "null";
    const char* mTargetCap = "null";
};