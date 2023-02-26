#include "devgui/DevGuiManager.h"
#include "devgui/windows/WindowActorBrowse.h"

WindowActorBrowse::WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault, bool isAnchor, int windowPages)
    : WindowBase(parent, winName, isActiveByDefault, isAnchor, windowPages) {}

void WindowActorBrowse::updateWin()
{
    WindowBase::updateWin();
    if(!mIsActive)
        return;
    
    return;
}

bool WindowActorBrowse::tryUpdateWinDisplay()
{
    if(!WindowBase::tryUpdateWinDisplay())
        return false;

    al::Scene* scene = tryGetScene();
    if(!scene)
        return true;

    al::LiveActorGroup* group = scene->mLiveActorKit->mLiveActorGroup2;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;

    ImVec2 inputChildSize = ImGui::GetContentRegionAvail();
    inputChildSize.x *= 0.9f;
    inputChildSize.y *= 0.1f;
    ImGui::BeginChild("ActorInputs", inputChildSize, false, window_flags);
    
    ImGui::Text("WIP");

    ImGui::EndChild();


    ImVec2 listSize = ImGui::GetContentRegionAvail();
    listSize.x *= 0.485f;
    listSize.y *= 0.9f;
    ImGui::BeginChild("ActorList", listSize, true, window_flags);
    
    int status;
    for(int i = 0; i < group->mActorCount; i++) {
        al::LiveActor* actor = group->mActors[i];

        char* actName = nullptr;
        actName = abi::__cxa_demangle(typeid(*actor).name(), nullptr, nullptr, &status);
        if(actName) {
            ImGui::Text(actName);
            free(actName);
        }
    }

    ImGui::EndChild();
    ImGui::SameLine();
    ImGui::BeginChild("ActorInfo", listSize, true, window_flags);
    
    ImGui::Text("Work in progress!");

    ImGui::EndChild();

    return true;
}