#pragma once

#include "game/HakoniwaSequence/HakoniwaSequence.h"

class DevGuiCategoryBase {
public:
    DevGuiCategoryBase(const char* catName) { mCatName = catName; };
    virtual void init();

    virtual void updateWin();
    virtual void updateWinDisplay();

private:
    HakoniwaSequence* mSequence;
    
    const char* mCatName;
};