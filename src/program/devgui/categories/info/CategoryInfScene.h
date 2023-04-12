#pragma once

#include "program/devgui/categories/CategoryBase.h"

class CategoryInfScene : public CategoryBase {
public:
    CategoryInfScene(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCatDisplay() override;
};