#include "WindowActorBrowse.h"
#include "devgui/DevGuiManager.h"
#include "primitives/PrimitiveQueue.h"

#include "helpers/GetHelper.h"

#include "imgui.h"
#include "al/model/ModelFunction.h"
#include "helpers/ImGuiHelper.h"

#include <cxxabi.h>

void WindowActorBrowse::childActorInspector()
{
    ImGui::SetWindowFontScale(1.4f);

    ImVec2 listSize = ImGui::GetContentRegionAvail();
    if(mIsWindowVertical)
        listSize.y -= mHeaderSize - 2.f;

    ImGui::BeginChild("ActorInfo", listSize, true);

    sead::FixedSafeString<0x30> actorClass = getActorName(mSelectedActor, ActorBrowseNameDisplayType_CLASS);

    ImGui::LabelText("Class", actorClass.cstr());

    if(mSelectedActor->mModelKeeper) {
        ImGui::Separator();
        ImGui::LabelText("Model", mSelectedActor->mModelKeeper->mResourceName);
    }

    ImGui::Separator();
    ImGui::LabelText("Name", mSelectedActor->getName());

    ImGui::Spacing();

    if (isInStageScene() && mSelectedActor->mPoseKeeper) {
        mSelectedActorTarget->actor = mSelectedActor;
        if (mSelectedActor->mModelKeeper) {
            sead::BoundBox3f boundbox;
            sead::Vector3f center;
            alModelFunction::calcBoundingBox(&boundbox, mSelectedActor->mModelKeeper->mModelCtrl);
            center = boundbox.getCenter();
            mSelectedActorTarget->pos = &center;
        }
        
        static bool focus = false;
        ImGui::Checkbox("Focus Camera", &focus);
        if (focus) {
            al::setCameraTarget(mSelectedActor, mSelectedActorTarget);
            al::requestCancelCameraInterpole(mSelectedActor, 0);
        } else al::resetCameraTarget(mSelectedActor, mSelectedActorTarget);
    }
    
    if(ImGui::Button("Appear")) mSelectedActor->appear();
    ImGui::SameLine();
    if(ImGui::Button("Kill")) mSelectedActor->kill();
    
    
    drawActorInspectorTreePose(mSelectedActor->mPoseKeeper);
    drawActorInspectorTreeFlags(mSelectedActor->mLiveActorFlag, listSize.x);
    drawActorInspectorTreeNrvs(mSelectedActor->getNerveKeeper(), &actorClass);
    drawActorInspectorTreeSensor(mSelectedActor->mHitSensorKeeper);
    drawActorInspectorTreeRail(mSelectedActor->getRailRider());
    drawActorInspectorTreeSubActor(mSelectedActor->mSubActorKeeper);

    ImGui::EndChild();
}

inline void WindowActorBrowse::drawActorInspectorTreePose(al::ActorPoseKeeperBase* pose)
{
    if(!pose)
        return;

    mParent->getPrimitiveQueue()->pushAxis(pose->mTranslation, 800.f);

    PlayerActorBase* player = tryGetPlayerActor();

    ImGui::SameLine();
    if(player && ImGui::Button("Warp to Object")) {
        player->startDemoPuppetable();
        player->mPoseKeeper->mTranslation = pose->mTranslation;
        player->endDemoPuppetable();
    } else ImGui::NewLine();

    if (ImGui::TreeNode("Actor Pose")) {
        ImGuiHelper::Vector3Drag("Trans", "Pose Keeper Translation", &pose->mTranslation, 50.f, 0.f);
        ImGuiHelper::Vector3Drag("Scale", "Pose Keeper Scale", pose->getScalePtr(), 0.05f, 0.f);
        ImGuiHelper::Vector3Drag("Velcoity", "Pose Keeper Velocity", pose->getVelocityPtr(), 1.f, 0.f);
        ImGuiHelper::Vector3Slide("Front", "Pose Keeper Front", pose->getFrontPtr(), 1.f, true);
        ImGuiHelper::Vector3Slide("Up", "Pose Keeper Up", pose->getUpPtr(), 1.f, true);
        ImGuiHelper::Vector3Slide("Gravity", "Pose Keeper Gravity", pose->getGravityPtr(), 1.f, true);
        ImGuiHelper::Vector3Drag("Eular", "Pose Keeper Rotation", pose->getRotatePtr(), 1.f, 360.f);
        ImGuiHelper::Quat("Pose Keeper Quaternion", pose->getQuatPtr());

        ImGui::TreePop();
    }
}

inline void WindowActorBrowse::drawActorInspectorTreeFlags(al::LiveActorFlag* flag, float childWindowWidth)
{
    if(!flag)
        return;

    if(ImGui::TreeNode("Flags")) {
        ImGui::Checkbox("Dead", &flag->mIsDead);
        ImGui::SameLine(childWindowWidth / 2.f);
        ImGui::Checkbox("Clipped", &flag->mIsClipped);

        ImGui::Checkbox("Cannot Clip", &flag->mIsClippingInvalidated);
        ImGui::SameLine(childWindowWidth / 2.f);
        ImGui::Checkbox("Draw Clipped", &flag->mIsDrawClipped);

        ImGui::Checkbox("Calc Anim On", &flag->mIsCalcAnimOn);
        ImGui::SameLine(childWindowWidth / 2.f);
        ImGui::Checkbox("Model Visible", &flag->mIsModelVisible);

        ImGui::Checkbox("No Collide", &flag->mIsNoCollide);
        ImGui::SameLine(childWindowWidth / 2.f);
        ImGui::Checkbox("Unknown 8", &flag->mIsFlag8);

        ImGui::Checkbox("Material Code", &flag->mIsMaterialCodeValid);
        ImGui::SameLine(childWindowWidth / 2.f);
        ImGui::Checkbox("Area Target", &flag->mIsAreaTarget);

        ImGui::Checkbox("Update Move FX", &flag->mIsUpdateMovementEffectAudioCollisionSensor);
        ImGui::SameLine(childWindowWidth / 2.f);
        ImGui::Checkbox("Unknown 12", &flag->mIsFlag12);
        
        ImGui::TreePop();
    }
}

inline void WindowActorBrowse::drawActorInspectorTreeNrvs(al::NerveKeeper* nrvKeep, sead::FixedSafeString<0x30>* actorClass)
{
    if(!nrvKeep)
        return;

    if(ImGui::TreeNode("Nerves")) {
        int status = 0;
        const al::Nerve* pNrv2 = nrvKeep->getCurrentNerve();
        char* nrvName2 = abi::__cxa_demangle(typeid(*pNrv2).name(), nullptr, nullptr, &status);

        ImGui::Text("Nerve: %s", nrvName2 + 23 + strlen(actorClass->cstr()) + 3);
        ImGui::Text("Step: %i", nrvKeep->mStep);

        ImGui::TreePop();
        free(nrvName2);
    }
}

inline void WindowActorBrowse::drawActorInspectorTreeRail(al::RailRider* railRide)
{
    if(!railRide)
        return;

    mParent->getPrimitiveQueue()->pushRail(railRide->mRail, mRailPercision, {0.7f, 0.1f, 0.5f, 1.f});

    if(ImGui::TreeNode("Rail")) {
        int percisonEdit = mRailPercision;
        ImGui::SliderInt("Percision", &percisonEdit, 2, 40, "%d", ImGuiSliderFlags_NoRoundToFormat);
        mRailPercision = percisonEdit;

        ImGui::Text("Progress: %.02f", railRide->mRailProgress);
        ImGui::DragFloat("Speed", &railRide->mMoveSpeed, 0.1f, 1000.f, -1000.f, "%.1f", ImGuiSliderFlags_NoRoundToFormat);

        ImGui::Text(railRide->mIsMoveForwardOnRail ? "Forward" : "Backward");
        ImGui::SameLine();
        if(ImGui::Button("Flip")) railRide->reverse();

        if(ImGui::Button("Go Start")) railRide->setMoveGoingStart();
        ImGui::SameLine();
        if(ImGui::Button("Go End")) railRide->setMoveGoingEnd();

        ImGui::TreePop();
    }
}

inline void WindowActorBrowse::drawActorInspectorTreeSensor(al::HitSensorKeeper* sensor)
{
    if(!sensor)
        return;

    mParent->getPrimitiveQueue()->pushHitSensor(mSelectedActor, mHitSensorTypes, 0.4f);
}

inline void WindowActorBrowse::drawActorInspectorTreeSubActor(al::SubActorKeeper* subActorKeep)
{
    if(!subActorKeep)
        return;

    if(ImGui::TreeNode("Sub-Actors")) {
        for(int i = 0; i < subActorKeep->mActorCount; i++) {
            al::LiveActor* subActor = subActorKeep->mInfoList[i]->mSubActor;

            sead::FixedSafeString<0x30> actorName = getActorName(subActor);
            sead::FixedSafeString<0x30> trimName = calcTrimNameFromRight(actorName);

            if(trimName.isEmpty()) {
                ImGui::TextDisabled("Actor name not found!");
                continue;
            }
            
            bool isFalse = false;

            ImGui::Selectable(trimName.cstr(), &isFalse, 0, ImVec2(ImGui::GetWindowWidth(), mLineSize));
            if (ImGui::IsItemHovered())
                showActorTooltip(subActor);

            if (ImGui::IsItemClicked()) {
                mSelectedActor = subActor;
                ImGui::SetScrollY(0.f);
            }
        }

        ImGui::TreePop();
    }
}