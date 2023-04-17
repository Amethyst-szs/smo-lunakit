#pragma once

#include "program/devgui/categories/CategoryBase.h"

class ImVec2; // Forward declaration

class CategoryHomeShip : public CategoryBase {
public:
    CategoryHomeShip(const char* catName, const char* catDesc, sead::Heap* heap);

    void init();
    void updateCat() override;
    void updateCatDisplay() override;

private:
    void drawSelectionIndex(const char* header, int* idx, bool* activation, ImVec2 minmax);
    void drawSelectionList(const char* header, int* idx, bool* activation, const char* list[], int listSize);

    bool mIsUpdateWorld = false;
    int mUpdateWorldIdx = -1;
    
    bool mIsUpdateStatus = false;
    int mUpdateStatusIdx = -1;
    int mUpdateStatusListSize = -1;

    bool mIsUpdateLevel = false;
    int mUpdateLevelIdx = -1;

    bool mIsUpdateWaterfall = false;
    int mUpdateWaterfallIdx = -1;
    int mUpdateWaterfallListSize = -1;
};