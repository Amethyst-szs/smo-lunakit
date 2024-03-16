#pragma once

namespace al {

class StageSwitchDirector {
public:
    StageSwitchDirector();

    void* vtable1;                          // 0x00
    void* vtable2;                          // 0x08
    int mUnk1;                              // 0x10
    unsigned int mUnk2;                     // 0x14
    void* vtable3;                          // 0x18
};

} // namespace al