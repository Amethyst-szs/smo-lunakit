#include "WindowActorBrowse.h"
#include "al/actor/LiveActorKit.h"
#include "al/util.hpp"
#include "devgui/DevGuiManager.h"
#include "devgui/savedata/DevGuiSaveData.h"

#include "primitives/PrimitiveQueue.h"

#include "helpers/GetHelper.h"

#include <cxxabi.h>

#include "imgui.h"

void WindowActorBrowse::generateFilterList(al::Scene* scene) {
    mFilterActorGroup->removeActorAll();

    if (isFilterBySearch() && !mSearchString)
        return;

    al::LiveActorGroup* sceneGroup = scene->mLiveActorKit->mLiveActorGroup2;

    int requiredFilters = 0;
    if (isFilterByFavorites())
        requiredFilters++;
    if (isFilterBySearch())
        requiredFilters++;

    for (int i = 0; i < sceneGroup->mActorCount; i++) {
        sead::FixedSafeString<0x30> className = getActorName(sceneGroup->mActors[i], ActorBrowseNameDisplayType_CLASS);
        sead::FixedSafeString<0x30> modelName = getActorName(sceneGroup->mActors[i], ActorBrowseNameDisplayType_MODEL);

        int filtersHit = 0;

        if (isFilterByFavorites() && isActorInFavorites(className.cstr()))
            filtersHit++;

        if (isFilterBySearch() && (al::isEqualSubString(className.cstr(), mSearchString) || al::isEqualSubString(modelName.cstr(), mSearchString)))
            filtersHit++;

        if (filtersHit >= requiredFilters)
            mFilterActorGroup->registerActor(sceneGroup->mActors[i]);
    }
}

bool WindowActorBrowse::isActorInFavorites(const char* actorName) {
    for (int i = 0; i < mMaxFavs; i++) {
        if (al::isEqualString(actorName, mFavActorNames[i].cstr()))
            return true;
    }

    return false;
}

void WindowActorBrowse::toggleFavorite(const char* actorName) {
    // Check for removing a favorite
    for (int i = 0; i < mMaxFavs; i++) {
        if (al::isEqualString(actorName, mFavActorNames[i].cstr())) {
            mTotalFavs--;
            mFavActorNames[i].clear();
            publishFavoritesToSave();
            return;
        }
    }

    // Max favorites, don't allow adding one
    if (mTotalFavs >= mMaxFavs)
        return;

    // Add a favorite if not removing a favorite
    sead::FixedSafeString<0x40> favName(actorName);
    for (int i = 0; i < mMaxFavs; i++) {
        if (mFavActorNames[i].isEmpty()) {
            mTotalFavs++;
            mFavActorNames[i] = favName;
            publishFavoritesToSave();
            return;
        }
    }
}

void WindowActorBrowse::publishFavoritesToSave() {
    DevGuiSaveData* save = mParent->getSaveData();

    for (int i = 0; i < mMaxFavs; i++) {
        save->setActorBrowserFavoriteAtIdx(mFavActorNames[i], i);
    }

    save->queueSaveWrite();
}

void WindowActorBrowse::getFavoritesFromSave() {
    if (mIsSaveDataInited)
        return;

    DevGuiSaveData* save = mParent->getSaveData();

    for (int i = 0; i < mMaxFavs; i++) {
        mFavActorNames[i] = save->getActorBrowserFavoriteAtIdx(i);
        if (!mFavActorNames[i].isEmpty())
            mTotalFavs++;
    }

    mIsSaveDataInited = true;
}

sead::FixedSafeString<0x30> WindowActorBrowse::getActorName(al::LiveActor* actor) {
    al::ModelKeeper* model = actor->mModelKeeper;

    if (isNameDisplayClass() || (!model && isNameDisplayModel())) {
        int status = 0;
        char* actName = nullptr;
        actName = abi::__cxa_demangle(typeid(*actor).name(), nullptr, nullptr, &status);

        sead::FixedSafeString<0x30> classNameSafe(actName);

        free(actName);
        return classNameSafe;
    }

    if (model && isNameDisplayModel()) {
        sead::FixedSafeString<0x30> modelNameSafe(model->mResourceName);
        return modelNameSafe;
    }

    if (isNameDisplayName()) {
        sead::FixedSafeString<0x30> baseNameSafe(actor->getName());
        return baseNameSafe;
    }

    sead::FixedSafeString<0x30> failName("NO NAME FOUND");
    return failName;
}

sead::FixedSafeString<0x30> WindowActorBrowse::getActorName(al::LiveActor* actor, ActorBrowseNameDisplayType nameType) {
    al::ModelKeeper* model = actor->mModelKeeper;

    if (nameType == ActorBrowseNameDisplayType_CLASS || (!model && isNameDisplayModel())) {
        int status = 0;
        char* actName = nullptr;
        actName = abi::__cxa_demangle(typeid(*actor).name(), nullptr, nullptr, &status);

        sead::FixedSafeString<0x30> classNameSafe(actName);

        free(actName);
        return classNameSafe;
    }

    if (model && nameType == ActorBrowseNameDisplayType_MODEL) {
        sead::FixedSafeString<0x30> modelNameSafe(model->mResourceName);
        return modelNameSafe;
    }

    if (nameType == ActorBrowseNameDisplayType_NAME) {
        sead::FixedSafeString<0x30> baseNameSafe(actor->getName());
        return baseNameSafe;
    }

    sead::FixedSafeString<0x30> failName("NO NAME FOUND");
    return failName;
}

sead::FixedSafeString<0x30> WindowActorBrowse::calcTrimNameFromRight(sead::FixedSafeString<0x30> text) {
    int textLen = text.calcLength();
    sead::FixedSafeString<0x30> trimName;

    // If string doesn't need trimming, pad to target length and return
    if (textLen <= mMaxCharacters) {
        trimName.append(text.cstr());
        trimName.append(' ', (mMaxCharacters - textLen) + 1);
        return trimName;
    }

    // Create trimed string
    for (int trimIdx = mMaxCharacters; trimIdx >= 0; trimIdx--) {
        trimName.append(&text.cstr()[textLen - trimIdx - 1], 1);
    }

    return trimName;
}

sead::FixedSafeString<0x30> WindowActorBrowse::calcTrimNameFromRight(sead::FixedSafeString<0x30> text, int maxChars) {
    int textLen = text.calcLength();
    sead::FixedSafeString<0x30> trimName;

    // If string doesn't need trimming, pad to target length and return
    if (textLen <= maxChars) {
        trimName.append(text.cstr());
        trimName.append(' ', (maxChars - textLen) + 1);
        return trimName;
    }

    // Create trimed string
    for (int trimIdx = maxChars; trimIdx >= 0; trimIdx--) {
        trimName.append(&text.cstr()[textLen - trimIdx - 1], 1);
    }

    return trimName;
}

void WindowActorBrowse::showActorTooltip(al::LiveActor* actor) {
    al::ModelKeeper* model = actor->mModelKeeper;
    sead::FixedSafeString<0x30> className = getActorName(actor, ActorBrowseNameDisplayType_CLASS);

    sead::FormatFixedSafeString<0x200> tooltipText("Class: %s\nName: %s\n", className.cstr(), actor->mActorName);
    if (actor->mModelKeeper) {
        tooltipText.append("Model: ");
        tooltipText.append(model->mResourceName);
        tooltipText.append("\n");
    }

    tooltipText.append("Click to open actor");
    ImGui::SetTooltip(tooltipText.cstr());

    if (actor->mPoseKeeper)
        mParent->getPrimitiveQueue()->pushAxis(actor->mPoseKeeper->mTranslation, 400.f);

    if (actor->mHitSensorKeeper && isInStageScene())
        mParent->getPrimitiveQueue()->pushHitSensor(actor, mHitSensorTypes, 0.15f);
}

int WindowActorBrowse::calcRoundedNum(int numToRound, int multiple) {
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}