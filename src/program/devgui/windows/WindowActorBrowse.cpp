#include "devgui/windows/WindowActorBrowse.h"
#include "devgui/DevGuiManager.h"

WindowActorBrowse::WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages)
{
    mSelectedActor = nullptr;
    mFilterActorGroup = new (mHeap) al::LiveActorGroup("FavActors", 5120);
}

void WindowActorBrowse::updateWin()
{
    WindowBase::updateWin();

    al::Scene* scene = tryGetScene();
    if (!scene || !mIsActive) {
        mSelectedActor = nullptr;
        mFilterType = ActorBrowseFilterType_NONE;
        mFilterActorGroup->removeActorAll();
        return;
    }

    if(!mIsSaveDataInited)
        getFavoritesFromSave();

    return;
}

bool WindowActorBrowse::tryUpdateWinDisplay()
{
    if (!WindowBase::tryUpdateWinDisplay())
        return false;

    al::Scene* scene = tryGetScene();
    if (!scene) {
        ImGui::TextDisabled("No scene!");
        return true;
    }

    mLineSize = ImGui::GetTextLineHeightWithSpacing();
    float winWidth = ImGui::GetWindowWidth();
    float winHeight = ImGui::GetWindowHeight();
    mIsWindowVertical = winWidth < winHeight;

    drawButtonHeader(scene);
    drawActorList(scene);

    if(!mIsWindowVertical)
        ImGui::SameLine();
    if (mSelectedActor)
        drawActorInfo();

    return true;
}

void WindowActorBrowse::drawButtonHeader(al::Scene* scene)
{
    ImGui::SetWindowFontScale(1.25f);

    ImVec2 inputChildSize = ImGui::GetContentRegionAvail();

    inputChildSize.y = mHeaderSize;
    ImGui::BeginChild("ActorInputs", inputChildSize, false);

    if (!isFilterBySearch()) {
        if (ImGui::Button("Search")) {
            mFilterType |= ActorBrowseFilterType_SEARCH;
            mParent->tryOpenKeyboard(24, KEYTYPE_QWERTY, &mSearchString, &mIsKeyboardInUse);
        }
    } else {
        if (ImGui::Button("Clear Search")) {
            mFilterType ^= ActorBrowseFilterType_SEARCH;
            mSearchString = nullptr;
            generateFilterList(scene);
        }
    }

    ImGui::SameLine();

    bool isFiltFavs = isFilterByFavorites();
    if (mTotalFavs == 0)
        ImGui::Text("No Favorites");
    else if (ImGui::Checkbox("Favorites", &isFiltFavs)) {
        mFilterType ^= ActorBrowseFilterType_FAV;
        generateFilterList(scene);
    }

    if(!isFilterByNone()) {
        ImGui::SameLine();
        ImGui::Checkbox("Mark", &mIsPrimDrawFilterGroup);
    }

    ImGui::SameLine(ImGui::GetWindowWidth() - 105);
    if (mSelectedActor && ImGui::Button("Close Actor"))
        mSelectedActor = nullptr;

    ImGui::EndChild();

    ImGui::SetWindowFontScale(mConfig.mFontSize);
}

void WindowActorBrowse::drawActorList(al::Scene* scene)
{
    al::LiveActorKit* kit = scene->mLiveActorKit;
    if(!kit) {
        ImGui::TextDisabled("No LiveActorKit!");
        mSelectedActor = nullptr;
        return;
    }

    al::LiveActorGroup* group = kit->mLiveActorGroup2;
    if(!group) {
        ImGui::TextDisabled("No LiveActorGroup!");
        mSelectedActor = nullptr;
        return;
    }

    if (isFilterBySearch() && mIsKeyboardInUse)
        generateFilterList(scene);

    if (!isFilterByNone() && mFilterActorGroup->mActorCount > 0)
        group = mFilterActorGroup;

    ImVec2 listSize = ImGui::GetContentRegionAvail();
    if(mIsWindowVertical)
        listSize.y -= mHeaderSize - 2.f;

    if (mSelectedActor) {
        if(mIsWindowVertical)
            listSize.y *= 0.3f;
        else
            listSize.x *= 0.45f;
    }

    ImGui::BeginChild("ActorList", listSize, true);

    float winWidth = ImGui::GetWindowWidth();
    float winHeight = ImGui::GetWindowHeight();
    float horizFontSize = ImGui::GetFontSize() * 0.63f;
    float curScrollPos = ImGui::GetScrollY();

    mMaxCharacters = (winWidth / horizFontSize) - 4;

    // Render empty space above the current scroll position
    ImGui::Dummy(ImVec2(50, calcRoundedNum(curScrollPos - mLineSize, mLineSize)));

    // Render all actor names and buttons within the range of scroll position -> bottom of window
    for (int i = curScrollPos / mLineSize; i < (curScrollPos + winHeight) / mLineSize; i++) {
        if (i >= group->mActorCount)
            continue;

        // Prepare name data
        al::LiveActor* actor = group->mActors[i];
        char* actorName = getActorName(actor);
        bool isFavorite = isActorInFavorites(actorName);

        sead::FixedSafeString<0x30> trimName = calcTrimNameFromRight(actorName);
        sead::FormatFixedSafeString<0x9> buttonName("%i", i);

        if(trimName.isEmpty()) {
            ImGui::TextDisabled("Actor name not found!");
            continue;
        }

        // Draw item and favorite option
        ImGui::Selectable(trimName.cstr(), &isFavorite, 0, ImVec2((mMaxCharacters - 2) * horizFontSize, mLineSize));
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip("Class: %s\nName: %s\nClick to open actor", actorName, actor->mActorName);

            if(actor->mPoseKeeper)
                mParent->getPrimitiveQueue()->pushAxis(actor->mPoseKeeper->mTranslation, 400.f);

            if(actor->mHitSensorKeeper)
                mParent->getPrimitiveQueue()->pushHitSensor(actor, mHitSensorTypes, 0.2f);
        }

        if (ImGui::IsItemClicked()) 
            mSelectedActor = actor;

        ImGui::SameLine();
        if (ImGui::ArrowButton(buttonName.cstr(), isFavorite ? ImGuiDir_Down : ImGuiDir_Up))
            toggleFavorite(actorName);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s\n%i/%i Favorites", isFavorite ? "Remove Favorite" : "Favorite", mTotalFavs, mMaxFavs);
        
        // If list is filtered and prim drawing for filter group is on, draw points
        if(!isFilterByNone() && mIsPrimDrawFilterGroup && mFilterActorGroup->mActorCount < 75 && actor->mPoseKeeper)
            mParent->getPrimitiveQueue()->pushPoint(actor->mPoseKeeper->mTranslation, 80.f, {0.9f, 0.6f, 0.9f, 0.3f});

        free(actorName);
    }

    // Fill in empty space below bottom of window for scroll
    ImGui::Dummy(ImVec2(50, calcRoundedNum((group->mActorCount - (curScrollPos / mLineSize)) * mLineSize, mLineSize)));

    ImGui::EndChild();
}

void WindowActorBrowse::drawActorInfo()
{
    ImVec2 listSize = ImGui::GetContentRegionAvail();
    if(mIsWindowVertical)
        listSize.y -= mHeaderSize - 2.f;

    ImGui::BeginChild("ActorInfo", listSize, true);

    char* actorClass = getActorName(mSelectedActor);

    ImGui::LabelText("Class", actorClass);
    if(mSelectedActor->mModelKeeper) {
        ImGui::Separator();
        ImGui::LabelText("Model", mSelectedActor->mModelKeeper->mResourceName);
    }
    ImGui::Separator();
    ImGui::LabelText("Name", mSelectedActor->getName());
    ImGui::Separator();
    
    al::ActorPoseKeeperBase* pose = mSelectedActor->mPoseKeeper;
    if(pose) {
        PlayerActorBase* player = tryGetPlayerActor();

        if(player && ImGui::Button("Warp to Object")) {
            player->startDemoPuppetable();
            player->mPoseKeeper->mTranslation = pose->mTranslation;
            player->endDemoPuppetable();
        }

        mParent->getPrimitiveQueue()->pushAxis(pose->mTranslation, 800.f);

        if (ImGui::TreeNode("Actor Pose")) {
            ImGui::Separator();

            ImGuiHelper::Vector3Drag("Trans", "Pose Keeper Translation", &pose->mTranslation, 50.f, 0.f);
            ImGuiHelper::Vector3Drag("Scale", "Pose Keeper Scale", pose->getScalePtr(), 0.05f, 0.f);
            ImGuiHelper::Vector3Drag("Velcoity", "Pose Keeper Velocity", pose->getVelocityPtr(), 1.f, 0.f);
            ImGuiHelper::Vector3Slide("Front", "Pose Keeper Front", pose->getFrontPtr(), 1.f, true);
            ImGuiHelper::Vector3Slide("Up", "Pose Keeper Up", pose->getUpPtr(), 1.f, true);
            ImGuiHelper::Vector3Slide("Gravity", "Pose Keeper Gravity", pose->getGravityPtr(), 1.f, true);
            ImGuiHelper::Vector3Drag("Eular", "Pose Keeper Rotation", pose->getRotatePtr(), 1.f, 360.f);
            ImGuiHelper::Quat("Pose Keeper Quaternion", pose->getQuatPtr());

            ImGui::TreePop();
        }
    }

    al::LiveActorFlag* flag = mSelectedActor->mLiveActorFlag;
    if(flag && ImGui::TreeNode("Flags")) {
        ImGui::Checkbox("Dead", &flag->mIsDead);
        ImGui::SameLine(listSize.x / 2.f);
        ImGui::Checkbox("Clipped", &flag->mIsClipped);

        ImGui::Checkbox("Cannot Clip", &flag->mIsClippingInvalidated);
        ImGui::SameLine(listSize.x / 2.f);
        ImGui::Checkbox("Draw Clipped", &flag->mIsDrawClipped);

        ImGui::Checkbox("Calc Anim On", &flag->mIsCalcAnimOn);
        ImGui::SameLine(listSize.x / 2.f);
        ImGui::Checkbox("Model Visible", &flag->mIsModelVisible);

        ImGui::Checkbox("No Collide", &flag->mIsNoCollide);
        ImGui::SameLine(listSize.x / 2.f);
        ImGui::Checkbox("Unknown 8", &flag->mIsFlag8);

        ImGui::Checkbox("Material Code", &flag->mIsMaterialCodeValid);
        ImGui::SameLine(listSize.x / 2.f);
        ImGui::Checkbox("Area Target", &flag->mIsAreaTarget);

        ImGui::Checkbox("Update Move FX", &flag->mIsUpdateMovementEffectAudioCollisionSensor);
        ImGui::SameLine(listSize.x / 2.f);
        ImGui::Checkbox("Unknown 12", &flag->mIsFlag12);
        
        ImGui::TreePop();
    }

    al::NerveKeeper* nrvKeep = mSelectedActor->getNerveKeeper();
    if(nrvKeep && ImGui::TreeNode("Nerves")) {
        int status = 0;
        const al::Nerve* pNrv2 = nrvKeep->getCurrentNerve();
        char* nrvName2 = abi::__cxa_demangle(typeid(*pNrv2).name(), nullptr, nullptr, &status);

        ImGui::Text("Nerve: %s", nrvName2 + 23 + strlen(actorClass) + 3);
        ImGui::Text("Step: %i", nrvKeep->mStep);

        ImGui::TreePop();
        free(nrvName2);
    }

    al::RailRider* railRide = mSelectedActor->getRailRider();
    if(railRide) {
        mParent->getPrimitiveQueue()->pushRail(railRide->mRail, mRailPercision, {0.7f, 0.1f, 0.5f, 1.f});
        if(ImGui::TreeNode("Rail")) {
            int percisonEdit = mRailPercision;
            ImGui::SliderInt("Percision", &percisonEdit, 2, 40, "%d", ImGuiSliderFlags_NoRoundToFormat);
            mRailPercision = percisonEdit;

            ImGui::Text("Progress: %.02f", railRide->mRailProgress);
            ImGui::DragFloat("Speed", &railRide->mMoveSpeed, 0.1f, 1000.f, -1000.f, "%.1f", ImGuiSliderFlags_NoRoundToFormat);

            ImGui::Text(railRide->mIsMoveForwardOnRail ? "Forward" : "Backward");
            ImGui::SameLine();
            if(ImGui::Button("Flip")) railRide->reverse();

            if(ImGui::Button("Go Start")) railRide->setMoveGoingStart();
            ImGui::SameLine();
            if(ImGui::Button("Go End")) railRide->setMoveGoingEnd();

            ImGui::TreePop();
        }
    }

    al::HitSensorKeeper* sensor = mSelectedActor->mHitSensorKeeper;
    if(sensor)
        mParent->getPrimitiveQueue()->pushHitSensor(mSelectedActor, mHitSensorTypes, 0.4f);

    ImGui::EndChild();

    free(actorClass);
}

bool WindowActorBrowse::isActorInFavorites(char* actorName)
{
    for (int i = 0; i < mMaxFavs; i++) {
        if (al::isEqualString(actorName, mFavActorNames[i].cstr()))
            return true;
    }

    return false;
}

void WindowActorBrowse::toggleFavorite(char* actorName)
{
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

void WindowActorBrowse::publishFavoritesToSave()
{
    DevGuiSaveData* save = mParent->getSaveData();

    for(int i = 0; i < mMaxFavs; i++) {
        save->setActorBrowserFavoriteAtIdx(mFavActorNames[i], i);
    }

    save->queueSaveWrite();
}

void WindowActorBrowse::getFavoritesFromSave()
{
    if(mIsSaveDataInited)
        return;

    DevGuiSaveData* save = mParent->getSaveData();

    for(int i = 0; i < mMaxFavs; i++) {
        mFavActorNames[i] = save->getActorBrowserFavoriteAtIdx(i);
        if(!mFavActorNames[i].isEmpty())
            mTotalFavs++;
    }

    mIsSaveDataInited = true;
}

void WindowActorBrowse::generateFilterList(al::Scene* scene)
{
    mFilterActorGroup->removeActorAll();

    if(isFilterBySearch() && !mSearchString) 
        return;

    al::LiveActorGroup* sceneGroup = scene->mLiveActorKit->mLiveActorGroup2;

    int requiredFilters = 0;
    if(isFilterByFavorites())
        requiredFilters++;
    if(isFilterBySearch())
        requiredFilters++;

    for (int i = 0; i < sceneGroup->mActorCount; i++) {
        char* actorName = getActorName(sceneGroup->mActors[i]);
        int filtersHit = 0;
        
        if (isFilterByFavorites() && isActorInFavorites(actorName))
            filtersHit++;

        if (isFilterBySearch() && al::isEqualSubString(actorName, mSearchString))
            filtersHit++;
        
        if(filtersHit >= requiredFilters)
            mFilterActorGroup->registerActor(sceneGroup->mActors[i]);

        free(actorName);
    }
}

char* WindowActorBrowse::getActorName(al::LiveActor* actor)
{
    int status = 0;
    char* actName = nullptr;
    actName = abi::__cxa_demangle(typeid(*actor).name(), nullptr, nullptr, &status);
    return actName;
}

sead::FixedSafeString<0x30> WindowActorBrowse::calcTrimNameFromRight(char* text)
{
    int textLen = strlen(text);
    sead::FixedSafeString<0x30> trimName;

    // If string doesn't need trimming, pad to target length and return
    if (textLen <= mMaxCharacters) {
        trimName.append(text);
        trimName.append(' ', (mMaxCharacters - textLen) + 1);
        return trimName;
    }

    // Create trimed string
    for (int trimIdx = mMaxCharacters; trimIdx >= 0; trimIdx--) {
        trimName.append(&text[textLen - trimIdx - 1], 1);
    }

    return trimName;
}

sead::FixedSafeString<0x30> WindowActorBrowse::calcTrimNameFromRight(char* text, int maxChars)
{
    int textLen = strlen(text);
    sead::FixedSafeString<0x30> trimName;

    // If string doesn't need trimming, pad to target length and return
    if (textLen <= maxChars) {
        trimName.append(text);
        trimName.append(' ', (maxChars - textLen) + 1);
        return trimName;
    }

    // Create trimed string
    for (int trimIdx = maxChars; trimIdx >= 0; trimIdx--) {
        trimName.append(&text[textLen - trimIdx - 1], 1);
    }

    return trimName;
}

int WindowActorBrowse::calcRoundedNum(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}