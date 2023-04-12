#include "devgui/docking/DevGuiDocking.h"
#include "devgui/DevGuiManager.h"

DevGuiDocking::DevGuiDocking(DevGuiManager* parent)
{
    mParent = parent;
}

void DevGuiDocking::update()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGuiIO& io = ImGui::GetIO();

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

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
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

    if(!mIsFirstStep || !(io.ConfigFlags & ImGuiConfigFlags_DockingEnable)) {
        ImGui::End();
        return;
    }

    mIsFirstStep = false;

    ImGui::DockBuilderRemoveNode(mDockSpace); // clear any previous layout
    ImGui::DockBuilderAddNode(mDockSpace, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(mDockSpace, mScreenSize);

    mDockUp = ImGui::DockBuilderSplitNode(mDockSpace, ImGuiDir_Up, 0.1f, nullptr, &mDockSpace);
    mDockDown = ImGui::DockBuilderSplitNode(mDockSpace, ImGuiDir_Down, 0.1f, nullptr, &mDockSpace);
    mDockLeft = ImGui::DockBuilderSplitNode(mDockSpace, ImGuiDir_Left, 0.4f, nullptr, &mDockSpace);
    mDockRight = ImGui::DockBuilderSplitNode(mDockSpace, ImGuiDir_Right, 0.4f, nullptr, &mDockSpace);

    // if(!mParent->getSaveData()->isReadImGuiLayoutFile()) {
    //     WindowBase* memWin = mParent->getWindow("Memory Manager");
    //     ImGui::DockBuilderDockWindow(mParent->getWindowNameAtIdx(0), mDockLeft);
    // }

    ImGui::DockBuilderFinish(mDockSpace);

    ImGui::End();
}

ImGuiID DevGuiDocking::getDockPoint(ImGuiDir direction)
{
    switch(direction) {
        case ImGuiDir_Up:
            return mDockUp;

        case ImGuiDir_Down:
            return mDockDown;
            
        case ImGuiDir_Left:
            return mDockLeft;

        case ImGuiDir_Right:
            return mDockRight;
    }

    return 0;
}

ImGuiDir DevGuiDocking::getDockDirection(ImGuiID id)
{
    if(id == mDockUp) return ImGuiDir_Up;
    else if(id == mDockDown) return ImGuiDir_Down;
    else if(id == mDockLeft) return ImGuiDir_Left;
    else if(id == mDockRight) return ImGuiDir_Right;

    return ImGuiDir_None;
}