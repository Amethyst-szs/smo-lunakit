#pragma once

#include "program/devgui/categories/CategoryBase.h"

class CategoryTASScripts : public CategoryBase {
public:
    CategoryTASScripts(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCatDisplay() override;
};
