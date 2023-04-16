#pragma once

#include "al/audio/AudioDirector.h"

namespace al
{
    class SeKeeper;
    class BgmKeeper;

    class AudioKeeper {
    public:
        AudioKeeper(al::AudioDirector const*);

        void* table1;                                           // 0x00
        al::AudioEventController* mEventController;             // 0x08
        void* table3;                                           // 0x10
        al::AudioRequestKeeperSyncedBgm* mRequestSyncedBgm;     // 0x18
        al::SeKeeper* mSeKeeper;                                // 0x20
        al::BgmKeeper* mBgmKeeper;                              // 0x28
        void* table5;                                           // 0x30

    };

    class IUseAudioKeeper {
    public:
        virtual al::AudioKeeper* getAudioKeeper() const = 0;
    };
};