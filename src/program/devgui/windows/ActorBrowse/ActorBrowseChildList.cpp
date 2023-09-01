#include "WindowActorBrowse.h"
#include "al/actor/LiveActorKit.h"
#include "devgui/DevGuiManager.h"
#include "imgui.h"

void WindowActorBrowse::childActorList(al::Scene* scene) {
    al::LiveActorKit* kit = scene->mLiveActorKit;
    if (!kit) {
        ImGui::TextDisabled("No LiveActorKit!");
        mSelectedActor = nullptr;
        return;
    }

    al::LiveActorGroup* group = kit->mLiveActorGroup2;
    if (!group) {
        ImGui::TextDisabled("No LiveActorGroup!");
        mSelectedActor = nullptr;
        return;
    }

    if (isFilterBySearch() && mIsKeyboardInUse)
        generateFilterList(scene);

    if (!isFilterByNone() && mFilterActorGroup->mActorCount > 0)
        group = mFilterActorGroup;

    ImVec2 listSize = ImGui::GetContentRegionAvail();
    if (mIsWindowVertical)
        listSize.y -= mHeaderSize - 2.f;

    if (mSelectedActor) {
        if (mIsWindowVertical)
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
        sead::FixedSafeString<0x30> actorName = getActorName(actor);
        sead::FixedSafeString<0x30> className;
        if (isNameDisplayClass())
            className = actorName;
        else
            className = getActorName(actor, ActorBrowseNameDisplayType_CLASS);

        bool isFavorite = isActorInFavorites(className.cstr());

        sead::FixedSafeString<0x30> trimName = calcTrimNameFromRight(actorName);
        sead::FormatFixedSafeString<0x9> buttonName("%i", i);

        if (trimName.isEmpty()) {
            ImGui::TextDisabled("Actor name not found!");
            continue;
        }

        // Draw item and favorite option
        ImGui::Selectable(trimName.cstr(), &isFavorite, 0, ImVec2((mMaxCharacters - 2) * horizFontSize, mLineSize));
        if (ImGui::IsItemHovered())
            showActorTooltip(actor);

        if (ImGui::IsItemClicked())
            mSelectedActor = actor;

        ImGui::SameLine();
        if (ImGui::ArrowButton(buttonName.cstr(), isFavorite ? ImGuiDir_Down : ImGuiDir_Up))
            toggleFavorite(className.cstr());
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("%s\n%i/%i Favorites", isFavorite ? "Remove Favorite" : "Favorite", mTotalFavs, mMaxFavs);
    }

    // Fill in empty space below bottom of window for scroll
    ImGui::Dummy(ImVec2(50, calcRoundedNum((group->mActorCount - (curScrollPos / mLineSize)) * mLineSize, mLineSize)));

    ImGui::EndChild();
}