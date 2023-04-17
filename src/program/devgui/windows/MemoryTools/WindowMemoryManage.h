
/*
    - LunaKit Memory Manager Window -

    This window displays current information about most of the game's heaps and the ActorKit
    More detailed ActorKit information can be found in the Actor Browser Window

    Does not use categories!

    https://github.com/Amethyst-szs/smo-lunakit/wiki#memory-manager
*/

#pragma once

#include "program/devgui/windows/WindowBase.h"

__attribute__((used)) static const char* memoryManageWindowName = "Heap View";

class WindowMemoryManage : public WindowBase {
public:
    WindowMemoryManage(DevGuiManager* parent, const char* winName, bool isActiveByDefault);

    bool tryUpdateWinDisplay() override;

private:
    void drawSimpleHeapView();
    void drawProgressBarPerc(sead::Heap* heap);
    void drawProgressBarFrac(int current, int max, const char* header);

    void drawComplexHeapTreeItem(sead::Heap* rootHeap);
};