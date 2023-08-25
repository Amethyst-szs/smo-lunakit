#pragma once

#include "GameSystemInfo.h"
#include "al/nerve/NerveExecutor.h"

namespace al {
    class NfpDirector;
    class ApplicationMessageReceiver;
    class Sequence;
    class AccountHolder;
    class AudioInfoListWithParts;
} // namespace al

class GameConfigData;

class GameSystem : public al::NerveExecutor {
public:
    al::Sequence* mSequence; // 0x10
    al::GameSystemInfo* mGameSystemInfo; // 0x18
    al::AudioSystem* mAudioSystem; // 0x20
    al::AudioInfoListWithParts* mAudioInfoListWithParts; // 0x28
    al::AccountHolder* mAccountHolder; // 0x30
    al::NetworkSystem* mNetworkSystem; // 0x38
    char unk[8];
    al::HtmlViewer* mHtmlViewer;
    al::NfpDirector* mNfpDirector;
    al::GamePadSystem* mGamePadSystem; // 0x58
    al::ApplicationMessageReceiver* mApplicationMessageReceiver; // 0x60
    al::WaveVibrationHolder* mWaveVibrationHolder;
    bool unk1;
    GameConfigData* mGameConfigData;
    bool unk2;
};

namespace GameSystemFunction {
    GameSystem* getGameSystem();
}