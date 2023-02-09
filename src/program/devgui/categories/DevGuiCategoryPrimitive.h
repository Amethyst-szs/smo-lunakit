#pragma once

#include "program/devgui/categories/DevGuiCategoryBase.h"
#include "program/devgui/DevGuiPrimitive.h"

class DevGuiCategoryPrimitive : public DevGuiCategoryBase {
public:
    DevGuiCategoryPrimitive(const char* catName, const char* catDesc);

    /*
    updateCat is not implemented here because all functionality is handled by singleton DevGuiPrimitive
    This seperation was made to allow running the primitive renderer at the correct time in the renderering process
    Look there to view any functionality!
    */

    void updateCatDisplay() override;
};