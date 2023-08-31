#include "devgui/docking/DevGuiDocking.h"
#include "devgui/DevGuiManager.h"
#include "devgui/savedata/DevGuiSaveData.h"
#include "helpers/ImGuiHelper.h"

#include "imgui_internal.h"

// Include different window classes in order to set up default anchoring placements
#include "devgui/windows/ActorBrowse/WindowActorBrowse.h"
#include "devgui/windows/Editor/WindowEditor.h"
#include "devgui/windows/Graphics/WindowGBuffer.h"
#include "devgui/windows/Graphics/WindowPresets.h"
#include "devgui/windows/Info/WindowInfo.h"
#include "devgui/windows/MemoryTools/WindowLoadLog.h"
#include "devgui/windows/MemoryTools/WindowMemoryManage.h"
#include "devgui/windows/StagePause/WindowStagePause.h"
#include "devgui/windows/TAS/WindowTAS.h"

#include "nn/oe.h"

DevGuiDocking::DevGuiDocking(DevGuiManager* parent) {
    mParent = parent;
}

void DevGuiDocking::update() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiIO& io = ImGui::GetIO();

    mScreenSize = io.DisplaySize;

    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
    ImGui::SetNextWindowSize(mScreenSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to
    // not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::SetWindowFontScale(1.5f);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    mDockSpace = ImGui::GetID("DockSpace");
    ImGui::DockSpace(mDockSpace, ImVec2(0.0f, 0.0f), dockspace_flags);

    if (!mIsFirstStep || !(io.ConfigFlags & ImGuiConfigFlags_DockingEnable)) {
        ImGui::End();
        return;
    }

    mIsFirstStep = false;

    ImGui::DockBuilderRemoveNode(mDockSpace);  // clear any previous layout
    ImGui::DockBuilderAddNode(mDockSpace, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(mDockSpace, mScreenSize);

    mDockUp = ImGui::DockBuilderSplitNode(mDockSpace, ImGuiDir_Up, 0.1f, nullptr, &mDockSpace);
    mDockDown = ImGui::DockBuilderSplitNode(mDockSpace, ImGuiDir_Down, 0.1f, nullptr, &mDockSpace);
    mDockLeft = ImGui::DockBuilderSplitNode(mDockSpace, ImGuiDir_Left, 0.4f, nullptr, &mDockSpace);
    mDockRight = ImGui::DockBuilderSplitNode(mDockSpace, ImGuiDir_Right, 0.4f, nullptr, &mDockSpace);

    ImGui::DockBuilderSetNodeSize(mDockLeft, ImVec2(345.f, 695.f));
    ImGui::DockBuilderSetNodeSize(mDockRight, ImVec2(400.f, 695.f));
    ImGui::DockBuilderSetNodeSize(mDockDown, ImVec2(400.f, 695.f));

    ImGuiID dockLM = ImGui::DockBuilderSplitNode(mDockLeft, ImGuiDir_Left, 0.82f, nullptr, &mDockLeft);
    ImGui::DockBuilderSetNodeSize(dockLM, ImVec2(345.f, 695.f));
    ImGuiID dockLU = ImGui::DockBuilderSplitNode(dockLM, ImGuiDir_Up, 0.33f, nullptr, &dockLM);
    ImGui::DockBuilderSetNodeSize(dockLU, ImVec2(345.f, 231.6f));
    ImGuiID dockLD = ImGui::DockBuilderSplitNode(dockLM, ImGuiDir_Down, 0.5f, nullptr, &dockLM);
    ImGui::DockBuilderSetNodeSize(dockLD, ImVec2(345.f, 275.f));

    if (!mParent->getSaveData()->isExistImGuiLayoutFile()) {
        // Create the default interface layout if no saved layout exists
        ImGui::DockBuilderDockWindow(memoryManageWindowName, dockLU);
        ImGui::DockBuilderDockWindow(loadLogWindowName, dockLU);
        ImGui::DockBuilderDockWindow(paramEditorWindowName, dockLM);
        ImGui::DockBuilderDockWindow(infoWindowName, dockLD);
        ImGui::DockBuilderDockWindow(presetsWindowName, dockLM);
        ImGui::DockBuilderDockWindow(gbufferWindowName, dockLD);
        ImGui::DockBuilderDockWindow(actorBrowseWindowName, mDockRight);
        ImGui::DockBuilderDockWindow(tasWindowName, dockLM);
        ImGui::DockBuilderDockWindow(stagePauseWindowName, dockLM);
    }

    ImGui::DockBuilderFinish(mDockSpace);

    ImGui::End();
}