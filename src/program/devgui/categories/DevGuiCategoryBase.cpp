#include "program/devgui/categories/DevGuiCategoryBase.h"

#include "imgui.h"

void DevGuiCategoryBase::init()
{
    // Blah
}

void DevGuiCategoryBase::updateWin()
{
    // Run code for the game here
}

void DevGuiCategoryBase::updateWinDisplay()
{
    ImGui::BulletText(mCatName);
}