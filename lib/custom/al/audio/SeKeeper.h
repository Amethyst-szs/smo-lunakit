#pragma once

#include "AudioDirector.h"

namespace al
{
    class SeEmitterHolder;
    class SeUserInfo;
    
    class SeKeeper {
    public:
        al::SeEmitterHolder* mEmitterHolder;        // 0x00
        al::SeDirector* mSeDirector;                // 0x08
        al::SeUserInfo* mUserInfo;                  // 0x10
        char* unkChar;                              // 0x18
        char padding[0x71-0x20];
    };
};