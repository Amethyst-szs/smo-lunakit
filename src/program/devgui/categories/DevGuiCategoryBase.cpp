#include "program/devgui/categories/DevGuiCategoryBase.h"

DevGuiCategoryBase::DevGuiCategoryBase(const char* catName, const char* catDesc)
{
    mCatName = catName;
    mCatDesc = catDesc;
}

void DevGuiCategoryBase::updateCat()
{
    // Run code for the game here
}

void DevGuiCategoryBase::updateCatDisplay()
{
    ImGui::TextColored(ImVec4(0.884f, 0.619f, 1.f, 1.0f), mCatDesc);
}