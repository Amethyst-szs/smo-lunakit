#pragma once

#include "al/area/AreaObjDirector.h"

namespace al
{
    class IAudioSystemPause;
    class SeDirector;
    class BgmDirector;
    class AudioEventController;
    class AudioRequestKeeperSyncedBgm;
    class AudioSystemInfo;
    class AudioDuckingDirector;

    class AudioDirector : public IUseAreaObj {
    public:
        void* super_IAudioSystemPause;                      // 0x08
        al::SeDirector* mSeDirector;                        // 0x10
        al::BgmDirector* mBgmDirector;                      // 0x18
        void* unk;                                          // 0x20
        al::AudioEventController* mEventController;         // 0x28
        al::AudioRequestKeeperSyncedBgm* mRequestSyncedBgm; // 0x30
        al::AudioSystemInfo* mSystemInfo;                   // 0x38
        void* unk2;                                         // 0x40
        al::AudioDuckingDirector* mDuckingDirector;         // 0x48
        void* unk3;                                         // 0x50
        void* unk4;                                         // 0x58
        void* unk5;                                         // 0x60
        void* unk6;                                         // 0x68
    };

};