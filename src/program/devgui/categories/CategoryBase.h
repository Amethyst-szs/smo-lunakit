/*
    - LunaKit Category System -

    Categories exist as a way to simplify and seperate out your window's code into different tabs!
    For more information, read the docs:
    
    https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#categories
*/

#pragma once

#include "heap/seadHeap.h"

class CategoryBase {
public:
    CategoryBase(const char* catName, const char* catDesc, sead::Heap* heap);

    virtual void updateCat();
    virtual void updateCatDisplay();

    virtual const char* getCategoryName() { return mCatName; };

protected:
    sead::Heap* mHeap = nullptr;
    
    const char* mCatName = nullptr;
    const char* mCatDesc = nullptr;
};