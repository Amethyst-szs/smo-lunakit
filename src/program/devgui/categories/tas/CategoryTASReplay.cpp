#include "CategoryTASReplay.h"
#include "devgui/DevGuiManager.h"
#include "nn/fs/fs_types.h"
#include "game/Scene/StageScene.h"
#include "ghost/GhostManager.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "helpers/GetHelper.h"
#include "devgui/savedata/DevGuiSaveData.h"

CategoryTASReplay::CategoryTASReplay(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap) {}

void CategoryTASReplay::updateCatDisplay() {
    auto* ghostMgr = GhostManager::instance();
    ImGui::Text("Max No. of Replays");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Set the maximum amount of replays that can be played at once.\nThis will reload the stage!");
    ImGui::SliderInt(" ", ghostMgr->getMaxGhosts(), 0, MAX_GHOST_COUNT, "%d", ImGuiSliderFlags_AlwaysClamp);
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Set the maximum amount of replays that can be played at once.\nThis will reload the stage!");
    bool* activeReplays = ghostMgr->getActiveReplays();
    s64 entryCount = ghostMgr->getEntryCount();
    if (ImGui::IsItemDeactivatedAfterEdit()) {
        DevGuiManager::instance()->getSaveData()->queueSaveWrite();
        tryReloadStage();
        for (int i = 0; i < entryCount; i++)
            activeReplays[i] = false;
    }
    ImGui::Text("\n");
    CategoryBase::updateCatDisplay();
    ImGui::BeginChild("Scripts", ImVec2(0,-(ImGui::GetFontSize()*8.5)), true);

    nn::fs::DirectoryEntry* entries = ghostMgr->getReplays();

    for (int i = 0; i < entryCount; i++) {
        bool isDisabled = false;
        if (mSelectedReplays >= *ghostMgr->getMaxGhosts() && !activeReplays[i]) {
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            isDisabled = true;
        }
        bool isSelected = activeReplays[i];
        ImGui::Checkbox(entries[i].mName, &isSelected);
        if (isSelected != activeReplays[i]) {
            activeReplays[i] = isSelected;
            mSelectedReplays += isSelected ? 1 : -1;
        }
        if (isDisabled) {
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();
        }
    }
    ImGui::EndChild();
}
