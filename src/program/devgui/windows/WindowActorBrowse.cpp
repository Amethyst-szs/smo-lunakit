#include "devgui/windows/WindowActorBrowse.h"
#include "devgui/DevGuiManager.h"

WindowActorBrowse::WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages)
{
    mSelectedActor = nullptr;
    mFilterActorGroup = new (mDevGuiHeap) al::LiveActorGroup("FavActors", 5120);
}

void WindowActorBrowse::updateWin()
{
    WindowBase::updateWin();

    al::Scene* scene = tryGetScene();
    if (!scene || !mIsActive) {
        mSelectedActor = nullptr;
        mFilterType = ActorBrowseFilterType::FILTER_NONE;
        mFilterActorGroup->removeActorAll();
        return;
    }

    return;
}

bool WindowActorBrowse::tryUpdateWinDisplay()
{
    if (!WindowBase::tryUpdateWinDisplay())
        return false;

    al::Scene* scene = tryGetScene();
    if (!scene)
        return true;

    mLineSize = ImGui::GetTextLineHeightWithSpacing();

    drawButtonHeader(scene);
    drawActorList(scene);
    if (mSelectedActor) {
        ImGui::SameLine();
        drawActorInfo();
    }

    return true;
}

void WindowActorBrowse::drawButtonHeader(al::Scene* scene)
{
    ImVec2 inputChildSize = ImGui::GetContentRegionAvail();
    inputChildSize.y = mHeaderSize;
    ImGui::BeginChild("ActorInputs", inputChildSize, false);

    bool isFiltFavs = isFilterByFavorites();
    if (mTotalFavs == 0)
        ImGui::Text("No Favorites!");
    else if (ImGui::Checkbox("Favs", &isFiltFavs))
        generateFilterListByFavs(scene);

    ImGui::SameLine();

    if (ImGui::Button("Delete Favs")) {
        mTotalFavs = 0;
        for (int i = 0; i < mMaxFavs; i++)
            mFavActorNames[i].clear();
    }

    ImGui::SameLine();

    if (!mSearchString) {
        if (ImGui::Button("Search")) {
            mFilterType = ActorBrowseFilterType::FILTER_SEARCH;
            mParent->tryOpenKeyboard(24, &mSearchString, &mIsKeyboardInUse);
        }
    } else {
        if (ImGui::Button("Clear Search")) {
            mFilterType = ActorBrowseFilterType::FILTER_NONE;
            mSearchString = nullptr;
        }
    }

    ImGui::EndChild();
}

void WindowActorBrowse::drawActorList(al::Scene* scene)
{
    al::LiveActorGroup* group = scene->mLiveActorKit->mLiveActorGroup2;

    if (isFilterBySearch() && mIsKeyboardInUse)
        generateFilterListBySearch(scene);

    if (!isFilterByNone() && mFilterActorGroup->mActorCount > 0)
        group = mFilterActorGroup;

    ImVec2 listSize = ImGui::GetContentRegionAvail();
    if (mSelectedActor)
        listSize.x *= 0.4f;
    listSize.y -= mHeaderSize + 8.f;
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

        al::LiveActor* actor = group->mActors[i];
        char* actorName = getActorName(actor);
        bool isFavorite = isActorInFavorites(actorName);

        sead::FixedSafeString<0x30> trimName = calcTrimNameFromRight(actorName);
        sead::FormatFixedSafeString<0x9> buttonName("%i", i);

        ImGui::Text(trimName.cstr());
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s\nClick to open actor", actorName);
        if (ImGui::IsItemClicked())
            mSelectedActor = actor;

        ImGui::SameLine();
        if (ImGui::ArrowButton(buttonName.cstr(), isFavorite ? ImGuiDir_Down : ImGuiDir_Up))
            toggleFavorite(actorName);

        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s\n%i/%i Favorites", isFavorite ? "Remove Favorite" : "Favorite", mTotalFavs, mMaxFavs);

        free(actorName);
    }

    // Fill in empty space below bottom of window for scroll
    ImGui::Dummy(ImVec2(50, calcRoundedNum((group->mActorCount - (curScrollPos / mLineSize)) * mLineSize, mLineSize)));

    ImGui::EndChild();
}

void WindowActorBrowse::drawActorInfo()
{
    ImVec2 listSize = ImGui::GetContentRegionAvail();
    listSize.y -= mHeaderSize + 8.f;
    ImGui::BeginChild("ActorInfo", listSize, true);

    ImGui::Text("Work in progress!");
    if (ImGui::Button("Close"))
        mSelectedActor = nullptr;

    ImGui::EndChild();
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
            return;
        }
    }
}

void WindowActorBrowse::generateFilterListByFavs(al::Scene* scene)
{
    mFilterActorGroup->removeActorAll();

    if (isFilterByFavorites()) {
        mFilterType = ActorBrowseFilterType::FILTER_NONE;
        return;
    }

    al::LiveActorGroup* sceneGroup = scene->mLiveActorKit->mLiveActorGroup2;
    mFilterType = ActorBrowseFilterType::FILTER_FAV;

    for (int i = 0; i < sceneGroup->mActorCount; i++) {
        char* actorName = getActorName(sceneGroup->mActors[i]);
        if (isActorInFavorites(actorName))
            mFilterActorGroup->registerActor(sceneGroup->mActors[i]);

        free(actorName);
    }

    if (mFilterActorGroup->mActorCount == 0)
        mFilterType = ActorBrowseFilterType::FILTER_NONE;
}

void WindowActorBrowse::generateFilterListBySearch(al::Scene* scene)
{
    mFilterActorGroup->removeActorAll();

    if (!mSearchString)
        return;

    int searchLength = strlen(mSearchString);
    if (searchLength <= 1)
        return;

    al::LiveActorGroup* sceneGroup = scene->mLiveActorKit->mLiveActorGroup2;

    for (int i = 0; i < sceneGroup->mActorCount; i++) {
        char* actorName = getActorName(sceneGroup->mActors[i]);
        if (al::isEqualSubString(actorName, mSearchString))
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

int WindowActorBrowse::calcRoundedNum(int numToRound, int multiple)
{
    if (multiple == 0)
        return numToRound;

    int remainder = numToRound % multiple;
    if (remainder == 0)
        return numToRound;

    return numToRound + multiple - remainder;
}