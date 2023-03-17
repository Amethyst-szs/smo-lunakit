#include "HooksSettings.h"
#include "logger/Logger.hpp"
namespace patch = exl::patch;
namespace inst = exl::armv8::inst;
namespace reg = exl::armv8::reg;

HOOK_DEFINE_TRAMPOLINE(ControlHook) {
    static void Callback(StageScene *scene) {
        DevGuiSettings* set = DevGuiManager::instance()->getSettings();

        if(!set->getStateByName("Display HUD") && scene->mSceneLayout->isWait()) {
            scene->mSceneLayout->end();
            MapMini* compass = scene->mSceneLayout->mMapMiniLyt;
            if (compass->mIsAlive) compass->end();
        }

        if(!set->getStateByName("Play Music")) {
            if (al::isPlayingBgm(scene)) {
                al::stopAllBgm(scene, 0);
            }
        }

        Orig(scene);
    }
};

HOOK_DEFINE_TRAMPOLINE(NoclipMovementHook) {
    static void Callback(PlayerActorHakoniwa *player) {
        bool isNoclip = DevGuiManager::instance()->getSettings()->getStateByName("Noclip");
        bool noCollide = DevGuiManager::instance()->getSettings()->getStateByName("Turn Off Collision");

        if (noCollide) {
            al::offCollide(player);
        } else if(!rs::isActiveDemo(player)) {
            al::onCollide(player);
        }

        if(!isNoclip && !rs::isActiveDemo(player) && !noCollide)
            al::onCollide(player);

        if(!isNoclip && !noCollide) {
            Orig(player);
            return;
        }

        if (isNoclip) {
            static float speed = 25.0f;
            static float speedMax = 150.0f;
            static float vspeed = 20.0f;
            static float speedGain = 0.0f;

            sead::Vector3f *playerPos = al::getTransPtr(player);
            sead::Vector3f *cameraPos = al::getCameraPos(player, 0);
            sead::Vector2f *leftStick = al::getLeftStick(-1);

            // Its better to do this here because loading zones reset this.
            al::offCollide(player);
            al::setVelocityZero(player);

            // Mario slightly goes down even when velocity is 0. This is a hacky fix for that.
            playerPos->y += 1.5f;

            float d = sqrt(al::powerIn(playerPos->x - cameraPos->x, 2) + (al::powerIn(playerPos->z - cameraPos->z, 2)));
            float vx = ((speed + speedGain) / d) * (playerPos->x - cameraPos->x);
            float vz = ((speed + speedGain) / d) * (playerPos->z - cameraPos->z);

            if (!al::isPadHoldZR(-1)) {
                playerPos->x -= leftStick->x * vz;
                playerPos->z += leftStick->x * vx;

                playerPos->x += leftStick->y * vx;
                playerPos->z += leftStick->y * vz;

                if (al::isPadHoldX(-1)) speedGain -= 0.5f;
                if (al::isPadHoldY(-1)) speedGain += 0.5f;
                if (speedGain <= 0.0f) speedGain = 0.0f;
                if (speedGain >= speedMax) speedGain = speedMax;

                if (al::isPadHoldZL(-1) || al::isPadHoldA(-1)) playerPos->y -= (vspeed + speedGain / 6);
                if (al::isPadHoldB(-1)) playerPos->y += (vspeed + speedGain / 6);
            }
        }
        Orig(player);
    }
};

HOOK_DEFINE_TRAMPOLINE(SaveHook) {
    static bool Callback(StageScene* scene) {
        if (DevGuiManager::instance()->getSettings()->getStateByName("Autosave"))
            return Orig(scene);

        return false;
    }
};

HOOK_DEFINE_TRAMPOLINE(CheckpointWarpHook) {
    static bool Callback(void* thisPtr) {
        if (DevGuiManager::instance()->getSettings()->getStateByName("Always Allow Checkpoints"))
            return true;

        return Orig(thisPtr);
    }
};
HOOK_DEFINE_TRAMPOLINE(GreyShineRefreshHook) {
    static bool Callback(GameDataHolderWriter writer, ShineInfo const* shineInfo) {
        if (DevGuiManager::instance()->getSettings()->getStateByName("Grey Moon Refresh"))
            return false;

        return Orig(writer, shineInfo);
    }
};
HOOK_DEFINE_TRAMPOLINE(ButtonMotionRollHook) {
    static bool Callback(void* thisPtr) {
        if (DevGuiManager::instance()->getSettings()->getStateByName("Button Motion Roll"))
            return true;

        return Orig(thisPtr);
    }
};

HOOK_DEFINE_TRAMPOLINE(NoDamageHook){
    static void Callback(PlayerHitPointData* hitPointData) {
        if (!DevGuiManager::instance()->getSettings()->getStateByName("No Damage"))
            return Orig(hitPointData);
    }
};

HOOK_DEFINE_TRAMPOLINE(ASMSettingsHook) {
    static void Callback(StageScene *scene) {
        patch::CodePatcher p(0x000000);
        if (DevGuiManager::instance()->getSettings()->getStateByName("Infinite Cap Bounces")) {
            p.Seek(0x4083ac);
            p.WriteInst(0x52800028); // MOV W8, 1
        }
        else{
            p.Seek(0x4083ac);
            p.WriteInst(0x3940E108);  // LDRB W8, [X8, #0x38]
        }
        if(DevGuiManager::instance()->getSettings()->getStateByName("Infinite Rainbow Spins")) {
            p.Seek(0x458cb8);
            p.WriteInst(0x52800029); // MOV W8, 1
        }
        else{
            p.Seek(0x458cb8);
            p.WriteInst(0x3940E508);  // LDRB W8, [X8, #0x39]
        }
        if(DevGuiManager::instance()->getSettings()->getStateByName("Cap Bounce after Wall Jump")) {
            p.Seek(0x407f2c);
            p.WriteInst(0x2A1F03E8); // MOV W8, WZR
        }
        else{
            p.Seek(0x407f2c);
            p.WriteInst(0x39400108);  // LDRB W8, [X8]
        }
        Orig(scene);
    }
};

void exlSetupSettingsHooks()
{
    ControlHook::InstallAtSymbol("_ZN10StageScene7controlEv");
    NoclipMovementHook::InstallAtSymbol("_ZN19PlayerActorHakoniwa8movementEv");
    SaveHook::InstallAtSymbol("_ZNK10StageScene12isEnableSaveEv");
    CheckpointWarpHook::InstallAtSymbol("_ZNK9MapLayout22isEnableCheckpointWarpEv");
    GreyShineRefreshHook::InstallAtSymbol("_ZN16GameDataFunction10isGotShineE22GameDataHolderAccessorPK9ShineInfo");
    ButtonMotionRollHook::InstallAtSymbol("_ZNK23PlayerJudgeStartRolling21isTriggerRestartSwingEv");
    NoDamageHook::InstallAtSymbol("_ZN16GameDataFunction12damagePlayerE20GameDataHolderWriter");
    ASMSettingsHook::InstallAtSymbol("_ZN10StageScene7controlEv"); // random symbol to update code patches every frame
}