#pragma once

#include "imgui.h"

#include "al/util.hpp"

#include "heap/seadDisposer.h"
#include "heap/seadHeap.h"

#include "program/GetterUtil.h"

class CategoryBase {
public:
    CategoryBase(const char* catName, const char* catDesc);

    virtual void updateCat();
    virtual void updateCatDisplay();

    virtual const char* getCategoryName() { return mCatName; };

protected:
    const char* mCatName = nullptr;
    const char* mCatDesc = nullptr;

    sead::Heap* mDevGuiHeap = nullptr;
};