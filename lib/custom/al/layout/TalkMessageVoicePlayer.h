#pragma once

#include "Library/Audio/AudioKeeper.h"
#include "Library/Message/IUseMessageSystem.h"

namespace al {
class TalkMessageVoicePlayer {
public:
    TalkMessageVoicePlayer();
    
    void start(al::IUseMessageSystem const*, al::IUseAudioKeeper const*, char16_t const*, int);
    void stop(void);
    void update(void);
    void calcVoicePitch(int);
    bool isPlaying(void) const;

    char size[0x440];
};
}
