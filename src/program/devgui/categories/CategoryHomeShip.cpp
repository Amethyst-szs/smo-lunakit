#include "program/devgui/categories/CategoryHomeShip.h"

#include "helpers.h"

CategoryHomeShip::CategoryHomeShip(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap)
{
    mUpdateStatusListSize = IM_ARRAYSIZE(updateStatusList);
    mUpdateWaterfallListSize = IM_ARRAYSIZE(updateWaterfallList);
}

void CategoryHomeShip::updateCat()
{
    GameDataHolder* holder = tryGetGameDataHolder();
    if(!holder)
        return;

    GameProgressData* progress = holder->mGameDataFile->mProgressData;

    if(mIsUpdateWorld) {
        mIsUpdateWorld = false;
        progress->mUnlockWorldNum = mUpdateWorldIdx;
    }

    if(mIsUpdateStatus) {
        mIsUpdateStatus = false;
        progress->mHomeStatus = (HomeShipStates)mUpdateWorldIdx;
    }

    if(mIsUpdateLevel) {
        mIsUpdateLevel = false;
        progress->mHomeLevel = mUpdateLevelIdx;
    }

    if(mIsUpdateWaterfall) {
        mIsUpdateWaterfall = false;
        progress->mWaterfallWorldProgress = (WaterfallWorldProgressStates)mUpdateWorldIdx;
    }
}

void CategoryHomeShip::updateCatDisplay()
{
    CategoryBase::updateCatDisplay();
    
    GameDataHolder* holder = tryGetGameDataHolder();
    if(!holder)
        return;

    GameProgressData* progress = holder->mGameDataFile->mProgressData;

    if (ImGui::BeginTabBar("Sub-categories")) {
        if (ImGui::BeginTabItem("Worlds")) {
            if(mUpdateWorldIdx == -1)
                mUpdateWorldIdx = progress->mUnlockWorldNum;

            drawSelectionIndex("World Count", &mUpdateWorldIdx, &mIsUpdateWorld, ImVec2(1, 17));

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Status")) {
            if(mUpdateStatusIdx == -1)
                mUpdateStatusIdx = (int)progress->mHomeStatus;

            drawSelectionList("Status", &mUpdateStatusIdx, &mIsUpdateStatus, updateStatusList, mUpdateStatusListSize);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Level")) {
            if(mUpdateLevelIdx == -1)
                mUpdateLevelIdx = progress->mHomeLevel;

            drawSelectionIndex("Level", &mUpdateLevelIdx, &mIsUpdateLevel, ImVec2(0, 9));

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Waterfall")) {
            if(mUpdateWaterfallIdx == -1)
                mUpdateWaterfallIdx = (int)progress->mWaterfallWorldProgress;

            drawSelectionList("Waterfall", &mUpdateWaterfallIdx, &mIsUpdateWaterfall, updateWaterfallList, mUpdateWaterfallListSize);

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}

void CategoryHomeShip::drawSelectionIndex(const char* header, int* idx, bool* activation, ImVec2 minmax)
{
    ImGui::SliderInt(header, idx, minmax.x, minmax.y);
    if(ImGui::Button("Set Parameter"))
        *activation = true;
}

void CategoryHomeShip::drawSelectionList(const char* header, int* idx, bool* activation, const char* list[], int listSize)
{
    const char* currentString = list[*idx];

    if(ImGui::BeginCombo(header, currentString)) {
        for(int n = 0; n < listSize; n++) {
            bool is_selected = (currentString == list[n]); // You can store your selection however you want, outside or inside your objects
            
            if (ImGui::Selectable(list[n], is_selected))
                *idx = n;

            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }

        ImGui::EndCombo();
    }

    if(ImGui::Button("Set Parameter"))
        *activation = true;
}