#include "program/devgui/categories/CategoryBase.h"

#include "imgui.h"

#include "logger/Logger.hpp"

CategoryBase::CategoryBase(const char* catName, const char* catDesc, sead::Heap* heap)
{
    Logger::log("      Constructing Category: %s\n", catName);
    mHeap = heap;
    mCatName = catName;
    mCatDesc = catDesc;
}

void CategoryBase::updateCat()
{
    // Run code for the game here
}

void CategoryBase::updateCatDisplay()
{
    ImGui::TextColored(ImVec4(0.884f, 0.619f, 1.f, 1.0f), mCatDesc);
}