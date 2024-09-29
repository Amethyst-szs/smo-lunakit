#include "PuppetActor.h"
#include "PuppetCapActor.h"
#include "Library/LiveActor/LiveActor.h"
#include "Library/LiveActor/ActorPoseKeeper.h"
#include "Library/LiveActor/SubActorKeeper.h"
#include "al/actor/ActorActionKeeper.h"
#include "al/graphics/GraphicsSystemInfo.h"
#include "al/layout/BalloonMessage.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/model/ModelMaterialCategory.h"
#include "al/model/PartsModel.h"
#include "al/model/ModelKeeper.h"
#include "Library/Base/StringUtil.h"
#include "al/util.hpp"
#include "al/util/LiveActorUtil.h"
#include "al/util/ResourceUtil.h"
#include "al/util/SensorUtil.h"
#include "devgui/DevGuiManager.h"
#include "game/System/GameDataFunction.h"
#include "game/Player/PlayerCostumeFunction.h"
#include "game/Player/PlayerCostumeInfo.h"
#include "logger/Logger.hpp"
#include "math/seadQuat.h"
#include "math/seadVector.h"
#include "nn/ro.h"
#include "rs/util/SensorUtil.h"
#include "util/modules.hpp"
#include "helpers/FunctionHelper.h"
#include <cmath>
#include <cstddef>
#include <typeinfo>

static const char* subActorNames[] = {
    "顔", // Face
    "目", // Eye
    "頭", // Head
    "左手", // Left Hand
    "右手" // Right Hand
};

PuppetActor::PuppetActor(const char* name, Ghost* parent)
    : al::LiveActor(name)
{
    mParent = parent;
    mModelHolder = new PlayerModelHolder(3); // Regular Model, 2D Model, 2D Mini Model
    mPuppetCap = new PuppetCapActor(name);
    mCaptures = new HackModelHolder();
}

PuppetActor::~PuppetActor() {
    mParent->removePuppet();
}

void PuppetActor::init(al::ActorInitInfo const& initInfo)
{
    typedef PlayerCostumeInfo *initMarioModelCommon(al::LiveActor *player, const al::ActorInitInfo &initInfo,
                                                    char const *bodyName, char const *capName, int subActorNum,
                                                    bool isDemo, al::AudioKeeper *audioKeeper, bool guessIsChromaKey,
                                                    bool isCloset);
    mPuppetCap->init(initInfo);

    al::initActorWithArchiveName(this, initInfo, "PlayerActorHakoniwa", nullptr);

    const char* bodyName = "Mario";
    const char* capName = "Mario";

    al::LiveActor* normalModel = new al::LiveActor("Normal");

    uintptr_t address = FunctionHelper::findEndOfFunc("_ZN14PlayerFunction19initMarioModelActorEPN2al9LiveActorERKNS0_13ActorInitInfoEPKcS7_PNS0_11AudioKeeperEb");
    auto* initMario = (initMarioModelCommon*)(address+4);

    if (!initMario)
        EXL_ABORT(8008, "Cannot find initMarioModelCommon!");

    mCostumeInfo = initMario(normalModel, initInfo, bodyName, capName, 0, false, nullptr, false, false);

    normalModel->mActorActionKeeper->mPadAndCamCtrl->mRumbleCount = 0; // set rumble count to zero so that no rumble actions will run

    mModelHolder->registerModel(normalModel, "Normal");

    al::LiveActor* normal2DModel = new al::LiveActor("Normal2D");

    PlayerFunction::initMarioModelActor2D(normal2DModel, initInfo, al::StringTmp<0x40>("%s2D", mCostumeInfo->mBodyInfo->mCostumeName).cstr(), PlayerFunction::isInvisibleCap(mCostumeInfo));

    mModelHolder->registerModel(normal2DModel, "Normal2D");

    al::setClippingInfo(normalModel, 50000.0f, 0);
    al::setClippingNearDistance(normalModel, 50000.0f);

    al::hideSilhouetteModelIfShow(normalModel);

    // "頭" = Head
    // "髪" = Hair
    // "キャップの目" = Cap Eyes
    // "[デモ用]キャップの目" = [Demo] Cap Eyes

    al::LiveActor* headModel = al::getSubActor(normalModel, "頭");
    al::getSubActor(headModel, "キャップの目")->kill();
    al::startVisAnimForAction(headModel, "CapOn");

    mModelHolder->changeModel("Normal");

    startAction("Wait");

    al::validateClipping(normalModel);
    al::validateClipping(normal2DModel);
    al::invalidateHitSensors(this);
}

void PuppetActor::initAfterPlacement() { al::LiveActor::initAfterPlacement(); }


void PuppetActor::movement()
{
    al::LiveActor::movement();
}

void PuppetActor::calcAnim()
{
    al::LiveActor::calcAnim();
}

void PuppetActor::control() {

    mPuppetCap->update();

    syncPose();
}

void PuppetActor::makeActorAlive()
{

    al::LiveActor* curModel = getCurrentModel();

    if (al::isDead(curModel)) {
        curModel->makeActorAlive();
    }

    al::LiveActor::makeActorAlive();
}

void PuppetActor::makeActorDead()
{

    al::LiveActor* curModel = getCurrentModel();

    if (!al::isDead(curModel)) {
        curModel->makeActorDead();
    }

    al::LiveActor::makeActorDead();
}


// this is more or less how nintendo does it with marios demo puppet
void PuppetActor::startAction(const char* actName)
{

    al::LiveActor* curModel = getCurrentModel();

    if (!actName)
        return;

    if (al::tryStartActionIfNotPlaying(curModel, actName)) {
        const char* curActName = al::getActionName(curModel);
        if (curActName) {
            if (al::isSklAnimExist(curModel, curActName)) {
                al::clearSklAnimInterpole(curModel);
            }
        }
    }

    for (size_t i = 0; i < 5; i++) {
        al::LiveActor* subActor = al::getSubActor(curModel, subActorNames[i]);
        const char* curActName = al::getActionName(curModel);
        if (subActor && curActName) {
            if (al::tryStartActionIfNotPlaying(subActor, curActName)) {
                if (al::isSklAnimExist(curModel, curActName)) {
                    al::clearSklAnimInterpole(curModel);
                }
            }
        }
    }

    al::LiveActor* faceActor = al::tryGetSubActor(curModel, "顔");

    if (faceActor) {
        al::StringTmp<0x80> faceAnim("%sFullFace", actName);
        if (al::tryStartActionIfNotPlaying(faceActor, faceAnim.cstr())) {
            if (al::isSklAnimExist(faceActor, faceAnim.cstr())) {
                al::clearSklAnimInterpole(faceActor);
            }
        }
    }
}

void PuppetActor::hairControl()
{

    al::LiveActor* curModel = getCurrentModel();

    if (mCostumeInfo->isNeedSyncBodyHair()) {
        PlayerFunction::syncBodyHairVisibility(al::getSubActor(curModel, "髪"), al::getSubActor(curModel, "頭"));
    }
    if (mCostumeInfo->isSyncFaceBeard()) {
        PlayerFunction::syncMarioFaceBeardVisibility(al::getSubActor(curModel, "顔"), al::getSubActor(curModel, "頭"));
    }
    if (mCostumeInfo->isSyncStrap()) {
        PlayerFunction::syncMarioHeadStrapVisibility(al::getSubActor(curModel, "頭"));
    }
    if (PlayerFunction::isNeedHairControl(mCostumeInfo->mBodyInfo, mCostumeInfo->mHeadInfo->mCostumeName)) {
        PlayerFunction::hideHairVisibility(al::getSubActor(curModel, "頭"));
    }
}

bool PuppetActor::isNeedBlending()
{
    const char* curActName = al::getActionName(getCurrentModel());
    if (curActName) {
        return al::isEqualSubString(curActName, "Move") || al::isEqualSubString(curActName, "Sand") || al::isEqualSubString(curActName, "MotorcycleRide");
    } else {
        return false;
    }
}

al::LiveActor* PuppetActor::getCurrentModel()
{
    return mModelHolder->mCurrentModel->mLiveActor;
}

void PuppetActor::changeModel(const char* newModel)
{
    getCurrentModel()->makeActorDead();
    mModelHolder->changeModel(newModel);
    getCurrentModel()->makeActorAlive();
}

void PuppetActor::syncPose()
{

    al::LiveActor* curModel = getCurrentModel();

    curModel->mPoseKeeper->updatePoseQuat(al::getQuat(this)); // update pose using a quaternion instead of setting quaternion rotation

    al::setTrans(curModel, al::getTrans(this));
}

void PuppetActor::emitJoinEffect()
{

    al::tryDeleteEffect(this, "Disappear"); // remove previous effect (if played previously)

    al::tryEmitEffect(this, "Disappear", nullptr);
}

/*
// Probably unused, but not sure
const char* executorName = "ＮＰＣ";

PlayerCostumeInfo* initMarioModelPuppet(al::LiveActor* player,
    const al::ActorInitInfo& initInfo,
    const char* bodyName, const char* capName,
    int subActorNum,
    al::AudioKeeper* audioKeeper)
{
    al::ActorResource* modelRes = al::findOrCreateActorResourceWithAnimResource(
        initInfo.mActorResourceHolder, al::StringTmp<0x100>("ObjectData/%s", bodyName).cstr(),
        al::StringTmp<0x100>("ObjectData/%s", "PlayerAnimation").cstr(), 0, false);

    PlayerBodyCostumeInfo* bodyInfo = PlayerCostumeFunction::createBodyCostumeInfo(modelRes->mResourceModel, bodyName);

    al::initActorSceneInfo(player, initInfo);
    al::initActorPoseTQGSV(player);
    al::initActorSRT(player, initInfo);

    al::initActorModelKeeper(player, initInfo,
        al::StringTmp<0x100>("ObjectData/%s", bodyName).cstr(), 6,
        al::StringTmp<0x100>("ObjectData/%s", "PlayerAnimation").cstr());

    al::ModelMaterialCategory::tryCreate(
        player->mModelKeeper->mModelCtrl, "Player",
        initInfo.mActorSceneInfo.mGraphicsSystemInfo->mMaterialCategoryKeeper);

    al::initPartialSklAnim(player, 1, 1, 32);
    al::addPartialSklAnimPartsListRecursive(player, "Spine1", 0);

    al::initExecutorUpdate(player, initInfo, executorName);
    al::initExecutorDraw(player, initInfo, executorName);
    al::initExecutorModelUpdate(player, initInfo);

    al::ByamlIter iter;
    if (al::tryGetActorInitFileIter(&iter, modelRes->mResourceModel, "InitEffect", 0)) {
        const char* effectKeeperName;
        if (iter.tryGetStringByKey(&effectKeeperName, "Name")) {
            al::initActorEffectKeeper(player, initInfo, effectKeeperName);
        }
    }

    PlayerFunction::initMarioAudio(player, initInfo, modelRes->mResourceModel, false, audioKeeper);
    al::initActorActionKeeper(player, modelRes, bodyName, 0);
    al::setMaterialProgrammable(player);

    al::SubActorKeeper* actorKeeper = al::SubActorKeeper::tryCreate(player, 0, subActorNum);

    if (actorKeeper) {
        player->initSubActorKeeper(actorKeeper);
    }

    actorKeeper->init(initInfo, 0, subActorNum);

    int subModelNum = al::getSubActorNum(player);

    if (subModelNum >= 1) {
        for (int i = 0; i < subModelNum; i++) {
            al::LiveActor* subActor = al::getSubActor(player, i);
            const char* actorName = subActor->getName();

            if (!al::isEqualString(actorName, "シルエットモデル")) {
                al::initExecutorUpdate(subActor, initInfo, executorName);
                al::initExecutorDraw(subActor, initInfo, executorName);
                al::setMaterialProgrammable(subActor);
            }
        }
    }

    al::initActorClipping(player, initInfo);
    al::invalidateClipping(player);

    const char* capModelName;

    if (bodyInfo->mIsUseHeadSuffix) {
        if (al::isEqualString(bodyInfo->mCostumeName, capName)) {
            capModelName = "";
        } else {
            capModelName = capName;
        }
    } else {
        capModelName = "";
    }

    const char* headType;

    if (!al::isEqualSubString(capName, "Mario64")) {
        if (bodyInfo->mIsUseShortHead && al::isEqualString(capName, "MarioPeach")) {
            headType = "Short";
        } else {
            headType = "";
        }
    } else if (al::isEqualString(bodyInfo->mCostumeName, "Mario64")) {
        headType = "";
    } else if (al::isEqualString(bodyInfo->mCostumeName, "Mario64Metal")) {
        headType = "Metal";
    } else {
        headType = "Other";
    }

    PlayerHeadCostumeInfo* headInfo = initMarioHeadCostumeInfo(
        player, initInfo, "頭", capName, headType, capModelName);

    PlayerCostumeInfo* costumeInfo = new PlayerCostumeInfo();
    costumeInfo->init(bodyInfo, headInfo);

    if (costumeInfo->isNeedBodyHair()) {

        // Logger::log("Creating Body Hair Parts Model.\n");

        al::PartsModel* partsModel = new al::PartsModel("髪");

        partsModel->initPartsFixFile(
            player, initInfo,
            al::StringTmp<0x100>("%sHair%s", bodyName,
                costumeInfo->isEnableHairNoCap() ? "NoCap" : "")
                .cstr(),
            0, "Hair");

        al::initExecutorUpdate(partsModel, initInfo, executorName);
        al::initExecutorDraw(partsModel, initInfo, executorName);
        al::setMaterialProgrammable(partsModel);
        partsModel->makeActorDead();
        al::onSyncAppearSubActor(player, partsModel);
        al::onSyncClippingSubActor(player, partsModel);
        al::onSyncAlphaMaskSubActor(player, partsModel);
        al::onSyncHideSubActor(player, partsModel);
    }

    PlayerFunction::initMarioDepthModel(player, false, false);

    rs::createPlayerSklRetargettingInfo(player, sead::Vector3f::ones);

    player->makeActorDead();
    return costumeInfo;
}

PlayerHeadCostumeInfo* initMarioHeadCostumeInfo(al::LiveActor* player,
    const al::ActorInitInfo& initInfo,
    const char* headModelName, const char* capModelName,
    const char* headType, const char* headSuffix)
{

    al::PartsModel* headModel = new al::PartsModel(headModelName);

    al::StringTmp<0x80> headArcName("%sHead%s", capModelName, headType);
    al::StringTmp<0x100> arcSuffix("Head");
    if (headSuffix)
        arcSuffix.format("Head%s", headSuffix);

    headModel->initPartsFixFile(player, initInfo, headArcName.cstr(), 0, arcSuffix.cstr());
    al::setMaterialProgrammable(headModel);

    al::initExecutorUpdate(headModel, initInfo, executorName);
    al::initExecutorDraw(headModel, initInfo, executorName);

    headModel->makeActorDead();

    al::onSyncAppearSubActor(player, headModel);
    al::onSyncClippingSubActor(player, headModel);
    al::onSyncAlphaMaskSubActor(player, headModel);
    al::onSyncHideSubActor(player, headModel);

    al::PartsModel* capEyesModel = new al::PartsModel("キャップの目");
    capEyesModel->initPartsFixFile(headModel, initInfo, "CapManHeroEyes", "", 0);

    al::onSyncClippingSubActor(headModel, capEyesModel);
    al::onSyncAlphaMaskSubActor(headModel, capEyesModel);
    al::onSyncHideSubActor(headModel, capEyesModel);

    al::setMaterialProgrammable(headModel);
    headModel->makeActorDead();

    return PlayerCostumeFunction::createHeadCostumeInfo(al::getModelResource(headModel), capModelName, false);
}
*/
