#pragma once

#include "StageSwitchDirector.h"

namespace al {

class StageSwitchAccesser {
public:
    StageSwitchAccesser();

    al::StageSwitchDirector* mDirector;         //0x00
    void* mUnk;                                 //0x08
    const char* mCharValue;                     //0x10
    void* mUnk2;                                //0x18
    unsigned long mUnk3;                        //0x20
    int mUnk4;                                  //0x24
};

} // namespace al