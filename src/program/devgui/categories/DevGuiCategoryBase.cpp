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
    ImGui::TextColored(ImVec4(0.784f, 0.419f, 0.98f, 1.0f), mCatDesc);
}