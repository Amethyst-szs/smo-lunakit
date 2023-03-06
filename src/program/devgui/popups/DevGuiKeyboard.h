#pragma once

#include "imgui.h"

#include "sead/container/seadPtrArray.h"
#include "sead/prim/seadSafeString.h"
#include "sead/heap/seadHeap.h"

#include "logger/Logger.hpp"

#include "types.h"

class DevGuiKeyboard {
public:
    DevGuiKeyboard(){}

    void update();
    bool tryOpenKeyboard(uint16_t maxChars, const char** output);

private:
    void endKeyboard();
    void drawKeyboardLine(const char* keys);

    bool mIsKeyboardOpen = false;
    bool mIsFirstStep = false;

    bool mIsShift = false;
    bool mIsCapsLock = false;

    uint16_t mMaxCharacters = -1;
    sead::FixedSafeString<0xff> mBuffer;
    const char** mOutputDest = nullptr;

    const int mKeyLineHeight = 42;
};