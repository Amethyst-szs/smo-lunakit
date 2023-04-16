#include "WindowActorBrowse.h"
#include "devgui/DevGuiManager.h"

#include "helpers/GetHelper.h"

#include "imgui.h"

WindowActorBrowse::WindowActorBrowse(DevGuiManager* parent, const char* winName, bool isActiveByDefault)
    : WindowBase(parent, winName, isActiveByDefault)
{
    mSelectedActor = nullptr;
    mSelectedActorTarget = new al::ActorCameraTarget(nullptr, 0.f, &sead::Vector3f::zero);
    mFilterActorGroup = new (mHeap) al::LiveActorGroup("FavActors", 5120);
}

void WindowActorBrowse::updateWin()
{
    WindowBase::updateWin();

    al::Scene* scene = tryGetScene();
    if (!scene || !mIsActive) {
        mSelectedActor = nullptr;
        mFilterType = ActorBrowseFilterType_NONE;
        mFilterActorGroup->removeActorAll();
        return;
    }

    if(!mIsSaveDataInited)
        getFavoritesFromSave();

    return;
}

bool WindowActorBrowse::tryUpdateWinDisplay()
{
    if (!WindowBase::tryUpdateWinDisplay())
        return false;

    al::Scene* scene = tryGetScene();
    if (!scene) {
        ImGui::TextDisabled("No scene!");
        return true;
    }

    mLineSize = ImGui::GetTextLineHeightWithSpacing();
    float winWidth = ImGui::GetWindowWidth();
    float winHeight = ImGui::GetWindowHeight();
    mIsWindowVertical = winWidth < winHeight;

    childButtonHeader(scene);
    childActorList(scene);

    if(!mIsWindowVertical)
        ImGui::SameLine();
    if (mSelectedActor)
        childActorInspector();
    
    return true;
}