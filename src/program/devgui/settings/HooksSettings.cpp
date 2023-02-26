#include "HooksSettings.h"

HOOK_DEFINE_TRAMPOLINE(ControlHook) {
    static void Callback(StageScene *scene) {
        DevGuiManager::instance()->updateNoclip();

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

void exlSetupSettingsHooks()
{
    ControlHook::InstallAtSymbol("_ZN10StageScene7controlEv");
    
    SaveHook::InstallAtSymbol("_ZNK10StageScene12isEnableSaveEv");
    CheckpointWarpHook::InstallAtOffset(0x1F2998);
    GreyShineRefreshHook::InstallAtSymbol("_ZN16GameDataFunction10isGotShineE22GameDataHolderAccessorPK9ShineInfo");
    ButtonMotionRollHook::InstallAtSymbol("_ZNK23PlayerJudgeStartRolling21isTriggerRestartSwingEv");
    NoDamageHook::InstallAtSymbol("_ZN16GameDataFunction12damagePlayerE20GameDataHolderWriter");
}