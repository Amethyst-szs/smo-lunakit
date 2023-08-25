#pragma once

#include "al/LiveActor/LiveActor.h"

#include "game/Player/PlayerJointControlPartsDynamics.h"
#include "game/Player/PlayerConst.h"

#include "PlayerCostumeInfo.h"

namespace al {
    class Resource;
}

class PlayerFunction
{
    public:
        static int getPlayerInputPort(const al::LiveActor *);
        static bool tryActivateAmiiboPreventDamage(const al::LiveActor *);
        static bool isPlayerDeadStatus(const al::LiveActor *player);
        static void syncBodyHairVisibility(al::LiveActor *, al::LiveActor *);
        static void syncMarioFaceBeardVisibility(al::LiveActor *, al::LiveActor *);
        static void syncMarioHeadStrapVisibility(al::LiveActor *);
        static bool isNeedHairControl(PlayerBodyCostumeInfo const *, const char *);
        static bool isInvisibleCap(PlayerCostumeInfo const *);
        static void hideHairVisibility(al::LiveActor *);

        static PlayerConst *createMarioConst(char const *);
        static void createCapModelName(sead::BufferedSafeStringBase<char> *, char const *);

        static void initMarioModelActor2D(al::LiveActor *actor, al::ActorInitInfo const &initInfo, char const *model2DName, bool isInvisCap);
        static al::Resource *initCapModelActor(al::LiveActor *, al::ActorInitInfo const &, char const *);
        static al::Resource *initCapModelActorDemo(al::LiveActor *, al::ActorInitInfo const &, char const *);
        static PlayerCostumeInfo *initMarioModelActor(al::LiveActor *player, const al::ActorInitInfo &initInfo, const char *modelName, const char *capType, al::AudioKeeper *keeper, bool isCloset);
        // joint, init, pconst, nosescale, earscale
        static PlayerCostumeInfo *initMarioModelActorDemo(PlayerJointControlPartsDynamics **jointCtrlPtr, al::LiveActor *player, const al::ActorInitInfo &initInfo, char const *bodyName, char const *capName, PlayerConst const *pConst,sead::Vector3f *noseScale, sead::Vector3f *earScale, bool isCloset);

        // not a real symbol, func at 0x444028
        static PlayerCostumeInfo *initMarioModelCommon(al::LiveActor *player, const al::ActorInitInfo &initInfo, char const *bodyName, char const *capName, int subActorNum, bool isDemo, al::AudioKeeper *audioKeeper, bool guessIsChromaKey, bool isCloset);

        // not a real symbol, func at 0x445A24
        static void initMarioAudio(al::LiveActor* player, const al::ActorInitInfo& initInfo,
                                   al::Resource* modelRes, bool isDemo,
                                   al::AudioKeeper* audioKeeper);
        // not a real symbol, func at 0x448B8C
        static void initMarioSubModel(al::LiveActor* subactor, const al::ActorInitInfo& initInfo,
                                      bool isInvisible, bool isDemo, bool isChromaKey,
                                      bool isCloset);
        // not a real symbol, func at 0x445128
        static PlayerHeadCostumeInfo* initMarioHeadCostumeInfo(al::LiveActor* player,
                                                               const al::ActorInitInfo& initInfo,
                                                               const char*, const char*,
                                                               const char*, const char*, bool, bool,
                                                               bool, bool, bool);
        // not a real symbol, func at 0x445DF4
        static void initMarioDepthModel(al::LiveActor *player, bool isDemo, bool isChromaKey);
};