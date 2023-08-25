#pragma once

#include "types.h"
#include "devgui/settings/DevGuiSettings.h"

// black magic

#define HOOK_CALLBACK(NAME)                                                                     \
HOOK_DEFINE_TRAMPOLINE(NAME) {                                                                  \
    static bool Callback(void* thisPtr) {                                                       \
        DevGuiSettings* set = DevGuiManager::instance()->getSettings();                         \
        if (set->getStateByName("Always Manually Skip Cutscenes"))                              \
            return true;                                                                        \
        return Orig(thisPtr);                                                                   \
    }                                                                                           \
};


#define MASS_HOOK_DEFINER(...)                                                                  \
                                                                                                \
    FOR_EACH(HOOK_CALLBACK, __VA_ARGS__)
