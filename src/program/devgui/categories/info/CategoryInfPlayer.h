#pragma once

#include "program/devgui/categories/CategoryBase.h"

class CategoryInfPlayer : public CategoryBase {
public:
    CategoryInfPlayer(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCatDisplay() override;
};