#pragma once

#include "program/devgui/DevGuiPrimitive.h"
#include "program/devgui/categories/CategoryBase.h"

class CategoryPrimitive : public CategoryBase {
public:
    CategoryPrimitive(const char* catName, const char* catDesc, sead::Heap* heap);

    /*
    updateCat is not implemented here because all functionality is handled by singleton DevGuiPrimitive
    This seperation was made to allow running the primitive renderer at the correct time in the renderering process
    Look there to view any functionality!
    */

    void updateCatDisplay() override;
};