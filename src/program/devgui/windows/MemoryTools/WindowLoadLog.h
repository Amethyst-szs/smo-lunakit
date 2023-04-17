
/*
    - LunaKit File Load Logging Window -

    This window displays a log of files which are loaded via al::FileLoader::loadArchive(). 
    The window will automatically scroll as files are loaded.
    Uses same text performance tool as the actor browser list

    Does not use categories!

    (TODO) https://github.com/Amethyst-szs/smo-lunakit/wiki
*/

#pragma once

#include "program/devgui/windows/WindowBase.h"

__attribute__((used)) static const char* loadLogWindowName = "Load Log";

class WindowLoadLog : public WindowBase {
public:
    WindowLoadLog(DevGuiManager* parent, const char* winName, bool isActiveByDefault);
    bool tryUpdateWinDisplay() override;
    
    void pushTextToWindow(const char* text);

    bool isAutoScrollEnabled() { return mIsAutoScrollEnabled; }
    int calcRoundedNum(int numToRound, int multiple);
    
private:
    bool mIsAutoScrollEnabled = true;
};