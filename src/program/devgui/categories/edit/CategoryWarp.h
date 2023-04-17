#pragma once

#include "program/devgui/categories/CategoryBase.h"

#include "game/Player/PlayerActorHakoniwa.h"

#include "sead/math/seadQuat.h"
#include "sead/math/seadVector.h"

struct WarpSaveState {
    bool mSaved = false;
    sead::Vector3f mTrans = sead::Vector3f::zero;
    sead::Quatf mQuat = sead::Quatf::unit;
};

class CategoryWarp : public CategoryBase {
public:
    CategoryWarp(const char* catName, const char* catDesc, sead::Heap* heap);

    void updateCat() override;
    void updateCatDisplay() override;

private:
    void saveTeleportData(PlayerActorHakoniwa* player);
    void loadTeleportData(PlayerActorHakoniwa* player);

    static const int mMaxSaves = 8;
    WarpSaveState mStates[mMaxSaves];
    int mCurStateIdx = 0;

    bool mIsUseHotkeys = false;
};