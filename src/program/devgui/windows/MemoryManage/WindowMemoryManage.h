
/*
    - LunaKit Memory Manager Window -

    This window displays current information about most of the game's heaps and the ActorKit
    More detailed ActorKit information can be found in the Actor Browser Window

    Does not use categories!

    https://github.com/Amethyst-szs/smo-lunakit/wiki#memory-manager
*/

#pragma once

#include "imgui.h"

#include "al/actor/LiveActorKit.h"

#include "game/System/GameSystem.h"
#include "game/System/Application.h"

#include "program/devgui/windows/WindowBase.h"

class WindowMemoryManage : public WindowBase {
public:
    WindowMemoryManage(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages);

    bool tryUpdateWinDisplay() override;

private:
    void drawSimpleHeapView();
    void drawProgressBarPerc(sead::Heap* heap);
    void drawProgressBarFrac(int current, int max, const char* header);

    void drawComplexHeapTreeItem(sead::Heap* rootHeap);

    bool mIsSimpleView = true;
};