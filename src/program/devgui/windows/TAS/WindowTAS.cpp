#include "WindowTAS.h"
#include "devgui/DevGuiManager.h"

#include "devgui/categories/tas/CategoryTASReplay.h"
#include "devgui/categories/tas/CategoryTASScripts.h"

#include "ghost/GhostManager.h"
#include "imgui.h"
#include "smo-tas/TAS.h"

WindowTAS::WindowTAS(DevGuiManager* parent, const char* winName, bool isActiveByDefault) : WindowBase(parent, winName, isActiveByDefault) {
    createCategory<CategoryTASScripts>("Scripts", "TAS Scripts");
    createCategory<CategoryTASReplay>("Replay", "Replay TASes");
}

bool WindowTAS::tryUpdateWinDisplay() {
    if (!WindowBase::tryUpdateWinDisplay())
        return false;
    float height = ImGui::GetWindowHeight();
    ImGui::SetCursorPosY(height - ImGui::GetFontSize() * 9.5);
    auto* tas = TAS::instance();
    auto* ghostManager = GhostManager::instance();
    ImGui::Text("Loaded Script: %s", tas->hasScript() ? tas->getScriptName() : "None.");
    ImGui::Checkbox("TAS", &isStartTAS);
    ImGui::SameLine();
    ImGui::Checkbox("Record", &isStartRecord);
    ImGui::SameLine();
    ImGui::Checkbox("Replay", &isStartReplay);
    if (ImGui::Button("Start")) {
        if (isStartTAS)
            tas->tryStartScript();
        if (isStartRecord)
            ghostManager->tryStartRecord();
        if (isStartReplay)
            ghostManager->tryStartReplay();
    }
    if (ImGui::Button("End All")) {
        tas->endScript();
        ghostManager->endRecord();
        ghostManager->endReplay();
    }
    if (ImGui::Button("Refresh Directories")) {
        tas->updateDir();
        ghostManager->updateDir();
    }

    if (tas->isRunning())
        ImGui::Text("TAS is running (%d/%d)", tas->getFrameIndex(), tas->getFrameCount());
    else
        ImGui::Text("TAS is not running.");

    bool isGhost = false;

    for (int i = 0; i < *ghostManager->getMaxGhosts(); i++) {
        auto ghost = ghostManager->getGhost(i);
        if (ghost->isRunning()) {
            ImGui::Text("Replay %d is running (%d/%d)", i, al::getNerveStep(ghost), ghost->getFrameCount());
            isGhost = true;
        }
    }

    if (!isGhost)
        ImGui::Text("No Replays are running.");

    return true;
}