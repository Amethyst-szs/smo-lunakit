/*
    - LunaKit On-Screen Keyboard -

    The on screen keyboard exists as a popup modal feature of the Manager class
    This class is not a base for a generic popup system, at this time that does not exist!
    For more info, read the docs
    
    https://github.com/Amethyst-szs/smo-lunakit/wiki/Code-Documentation#popups-and-on-screen-keyboard
*/

#pragma once

#include "sead/prim/seadSafeString.h"

enum PopupKeyboardType {
    KEYTYPE_QWERTY,
    KEYTYPE_NUMBER,
    KEYTYPE_IP
};

class PopupKeyboard {
public:
    PopupKeyboard() {}

    void update();
    bool tryOpenKeyboard(uint16_t maxChars, PopupKeyboardType keyType, const char** output, bool* isKeyboardOpen);
    bool tryOpenKeyboard(uint16_t maxChars, PopupKeyboardType keyType, sead::FixedSafeString<0xff>* output, bool* isKeyboardOpen);

private:
    void endKeyboard();

    void drawQuertyKeyset();
    void drawNumberKeyset();

    void drawKeyboardLine(const char* keys);

    bool* mIsKeyboardOpen = nullptr;
    bool mIsFirstStep = false;
    PopupKeyboardType mKeyboardType = PopupKeyboardType::KEYTYPE_QWERTY;

    bool mIsShift = false;
    bool mIsCapsLock = false;

    uint16_t mMaxCharacters = -1;
    sead::FixedSafeString<0xff> mBuffer;
    const char** mOutputDest = nullptr;

    const int mKeyLineHeight = 42;
};