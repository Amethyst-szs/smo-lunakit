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

    drawButtonHeader();
    drawActorList(scene);
    ImGui::SameLine();
    drawActorInfo();

    return true;
}

void WindowActorBrowse::drawButtonHeader()
{
    ImVec2 inputChildSize = ImGui::GetContentRegionAvail();
    inputChildSize.y = mHeaderSize;
    ImGui::BeginChild("ActorInputs", inputChildSize, false, mChildFlags);
    
    ImGui::Text("WIP");

    ImGui::EndChild();
}

void WindowActorBrowse::drawActorList(al::Scene* scene)
{
    al::LiveActorGroup* group = scene->mLiveActorKit->mLiveActorGroup2;

    ImVec2 listSize = ImGui::GetContentRegionAvail();
    listSize.x *= 0.6f;
    listSize.y -= mHeaderSize + 8.f;
    ImGui::BeginChild("ActorList", listSize, true, mChildFlags);
    
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
}

void WindowActorBrowse::drawActorInfo()
{
    ImVec2 listSize = ImGui::GetContentRegionAvail();
    listSize.y -= mHeaderSize + 8.f;
    ImGui::BeginChild("ActorInfo", listSize, true, mChildFlags);
    
    ImGui::Text("Work in progress!");

    ImGui::EndChild();
}