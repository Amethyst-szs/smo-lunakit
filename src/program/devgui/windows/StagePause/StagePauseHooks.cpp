#include "StagePauseHooks.h"
#include <al/util/NerveUtil.h>
#include <game/StageScene/StageScene.h>
#include <lib.hpp>
#include "stage-pause/StageSceneStateStagePause.h"

namespace patch = exl::patch;
namespace inst = exl::armv8::inst;
namespace reg = exl::armv8::reg;

// clang-format off
HOOK_DEFINE_TRAMPOLINE(StageSceneInitHook) {
    static void Callback(StageScene* thisPtr, al::SceneInitInfo* initInfo) {
        Orig(thisPtr, initInfo);
        thisPtr->mStatePause = new StageSceneStateStagePause("StagePause", thisPtr, thisPtr->mAudioSystemPauseController);
        if (thisPtr->mStatePause) {
            al::initNerveState(thisPtr, thisPtr->mStatePause, &StageSceneNrvStagePause::sInstance, "StagePause");
        }
    }
};

// clang-format on
void exlSetupStageSceneHooks() {
    StageSceneInitHook::InstallAtSymbol("_ZN10StageScene4initERKN2al13SceneInitInfoE");
    exl::patch::CodePatcher p("_ZN16HakoniwaSequence12exeLoadStageEv", 0x1f4);
    p.WriteInst(inst::Movz(reg::X0, sizeof(StageScene)));
    p.Seek("_ZN16HakoniwaSequence7exeMissEv", 0x13c);
    p.WriteInst(inst::Movz(reg::X0, sizeof(StageScene)));
}