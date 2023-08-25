#pragma once

#include "program/devgui/categories/CategoryBase.h"

class CategoryTASReplay : public CategoryBase {
public:
    CategoryTASReplay(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCatDisplay() override;
private:
    int mSelectedReplays = 0;
};