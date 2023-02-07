#pragma once

#include "container/seadPtrArray.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/GameSystem.h"
#include "heap/seadHeap.h"
#include "math/seadVector.h"

#include "devgui/windows/DevGuiWindowBase.h"
#include "devgui/categories/DevGuiCategoryBase.h"

class DevGuiWindowMain : public DevGuiWindowBase {
public:
    DevGuiWindowMain(const char* winName);
    virtual void initGameSystem(GameSystem* system, sead::Heap* heap) override;
    virtual void initSequence(HakoniwaSequence* seq) override;

    virtual void updateWin() override;
    virtual void updateWinDisplay() override;

private:
};