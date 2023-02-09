#pragma once

#include "program/devgui/categories/CategoryBase.h"

class CategoryOutfit : public CategoryBase {
public:
    CategoryOutfit(const char* catName, const char* catDesc);

    void updateCat() override;
    void updateCatDisplay() override;

private:
    void drawDropdown(const char* header, const char* options[], const int totalOptions, const char** output);

    bool mIsOverride = false;
    bool mIsReloadScene = false;

    ImGuiComboFlags mComboFlags;
    int mTotalBody = -1;
    int mTotalCap = -1;
    const char* mTargetBody = "null";
    const char* mTargetCap = "null";
};