#include "WindowActorBrowse.h"
#include "devgui/DevGuiManager.h"

#include "imgui.h"

void WindowActorBrowse::childButtonHeader(al::Scene* scene)
{
    ImGui::SetWindowFontScale(1.25f);

    ImVec2 inputChildSize = ImGui::GetContentRegionAvail();

    inputChildSize.y = mHeaderSize;
    ImGui::BeginChild("ActorInputs", inputChildSize, false);

    if(ImGui::BeginCombo(actorBrowseNameTypeTable[mNameDisplayType], " ", ImGuiComboFlags_NoPreview)) {
        ImGui::SetWindowFontScale(1.5f);

        for(int i = 0; i < ActorBrowseNameDisplayType_ENUMSIZE; i++) {
            bool is_selected = mNameDisplayType == (ActorBrowseNameDisplayType)i;

            if (ImGui::Selectable(actorBrowseNameTypeTable[i], is_selected)) {
                mNameDisplayType = (ActorBrowseNameDisplayType)i;
                generateFilterList(scene);
            }

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }

    ImGui::SameLine();

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
        ImGui::Text("No Favs");
    else if (ImGui::Checkbox("Favs", &isFiltFavs)) {
        mFilterType ^= ActorBrowseFilterType_FAV;
        generateFilterList(scene);
    }

    ImGui::SameLine(ImGui::GetWindowWidth() - (105 * (*mParent->getCurrentScreenSizeMulti())));

    if (mSelectedActor && ImGui::Button("Close Actor"))
        mSelectedActor = nullptr;

    ImGui::EndChild();
}