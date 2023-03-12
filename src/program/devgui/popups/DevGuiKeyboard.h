/*
    - LunaKit On-Screen Keyboard -

    The on screen keyboard exists as a popup modal feature of the Manager class
    This class is not a base for a generic popup system, at this time that does not exist!
    For more info, read the docs
    
    https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#popups-and-on-screen-keyboard
*/

#pragma once

#include "imgui.h"

#include "sead/container/seadPtrArray.h"
#include "sead/prim/seadSafeString.h"

#include "logger/Logger.hpp"

#include "types.h"

class DevGuiKeyboard {
public:
    DevGuiKeyboard(){}

    void update();
    bool tryOpenKeyboard(uint16_t maxChars, const char** output, bool* isKeyboardOpen);

private:
    void endKeyboard();
    void drawKeyboardLine(const char* keys);

    bool* mIsKeyboardOpen = nullptr;
    bool mIsFirstStep = false;

    bool mIsShift = false;
    bool mIsCapsLock = false;

    uint16_t mMaxCharacters = -1;
    sead::FixedSafeString<0xff> mBuffer;
    const char** mOutputDest = nullptr;

    const int mKeyLineHeight = 42;
};