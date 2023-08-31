#include "devgui/DevGuiManager.h"
#include "WindowTAS.h"

#include "devgui/categories/tas/CategoryTASReplay.h"
#include "devgui/categories/tas/CategoryTASScripts.h"

#include "ghost/GhostManager.h"
#include "imgui.h"
#include "smo-tas/TAS.h"

WindowTAS::WindowTAS(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault) {
    createCategory<CategoryTASScripts>("Scripts", "TAS Scripts");
    createCategory<CategoryTASReplay>("Replay", "Replay TASes");
}

bool WindowTAS::tryUpdateWinDisplay() {
    if(!WindowBase::tryUpdateWinDisplay())
        return false;
    float height = ImGui::GetWindowHeight();
    ImGui::SetCursorPosY(height-ImGui::GetFontSize()*8.5);
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

    return true;
}