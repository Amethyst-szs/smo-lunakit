#include "WindowActorBrowse.h"
#include "devgui/DevGuiManager.h"
#include "primitives/PrimitiveQueue.h"
#include "al/model/ModelKeeper.h"
#include "Library/LiveActor/ActorPoseKeeper.h"
#include "Library/LiveActor/SubActorKeeper.h"
#include <Library/Nerve/NerveStateCtrl.h>
#include "Library/Base/StringUtil.h"
#include "Library/Nerve/NerveKeeper.h"
#include "Library/Rail/RailRider.h"

#include "helpers/GetHelper.h"

#include "imgui.h"
#include "al/model/ModelFunction.h"
#include "helpers/ImGuiHelper.h"
#include "game/Actors/KuriboHack.h"

#include <cxxabi.h>

void WindowActorBrowse::childActorInspector()
{
    ImGui::SetWindowFontScale(1.4f);

    ImVec2 listSize = ImGui::GetContentRegionAvail();
    if(mIsWindowVertical)
        listSize.y -= mHeaderSize - 2.f;

    ImGui::BeginChild("ActorInfo", listSize, true);

    sead::FixedSafeString<0x30> actorClass = getActorName(mSelectedActor, ActorBrowseNameDisplayType_CLASS);

    ImGui::LabelText("Class", "%s", actorClass.cstr());

    if(mSelectedActor->mModelKeeper) {
        ImGui::Separator();
        ImGui::LabelText("Model", "%s", mSelectedActor->mModelKeeper->mResourceName);
    }

    ImGui::Separator();
    ImGui::LabelText("Name", "%s", mSelectedActor->getName());

    ImGui::Spacing();

    // if (isInStageScene() && mSelectedActor->mPoseKeeper) {
    //     mSelectedActorTarget->actor = mSelectedActor;
    //     if (mSelectedActor->mModelKeeper) {
    //         sead::BoundBox3f boundbox;
    //         sead::Vector3f center;
    //         alModelFunction::calcBoundingBox(&boundbox, mSelectedActor->mModelKeeper->mModelCtrl);
    //         center = boundbox.getCenter();
    //         mSelectedActorTarget->pos = &center;
    //     }
        
    //     static bool focus = false;
    //     ImGui::Checkbox("Focus Camera", &focus);
    //     if (focus) {
    //         al::setCameraTarget(mSelectedActor, mSelectedActorTarget);
    //         al::requestCancelCameraInterpole(mSelectedActor, 0);
    //     } else al::resetCameraTarget(mSelectedActor, mSelectedActorTarget);
    // }
    
    if(ImGui::Button("Appear")) mSelectedActor->appear();
    ImGui::SameLine();
    if(ImGui::Button("Kill")) mSelectedActor->kill();
    
    
    drawActorInspectorTreePose(mSelectedActor->mPoseKeeper);
    drawActorInspectorTreeFlags(mSelectedActor->mFlags, listSize.x);
    drawActorInspectorTreeNrvs(mSelectedActor->getNerveKeeper(), &actorClass);
    drawActorInspectorTreeSensor(mSelectedActor->mHitSensorKeeper);
    drawActorInspectorTreeRail(mSelectedActor->getRailRider());
    drawActorInspectorTreeSubActor(mSelectedActor->mSubActorKeeper);
    drawActorInspectorTreeKuriboDebug(mSelectedActor);

    ImGui::EndChild();
}

inline void WindowActorBrowse::drawActorInspectorTreePose(al::ActorPoseKeeperBase* pose)
{
    if(!pose)
        return;

    mParent->getPrimitiveQueue()->pushAxis(pose->mTrans, 800.f);

    PlayerActorBase* player = tryGetPlayerActor();

    ImGui::SameLine();
    if(player && ImGui::Button("Warp to Object")) {
        player->startDemoPuppetable();
        player->mPoseKeeper->mTrans = pose->mTrans;
        player->endDemoPuppetable();
    } else ImGui::NewLine();

    if (ImGui::TreeNode("Actor Pose")) {
        ImGuiHelper::Vector3Drag("Trans", "Pose Keeper Translation", &pose->mTrans, 50.f, 0.f);
        ImGuiHelper::Vector3Drag("Scale", "Pose Keeper Scale", pose->getScalePtr(), 0.05f, 0.f);
        ImGuiHelper::Vector3Drag("Velocity", "Pose Keeper Velocity", pose->getVelocityPtr(), 1.f, 0.f);
        ImGuiHelper::Vector3Slide("Front", "Pose Keeper Front", pose->getFrontPtr(), 1.f, true);
        ImGuiHelper::Vector3Slide("Up", "Pose Keeper Up", pose->getUpPtr(), 1.f, true);
        ImGuiHelper::Vector3Slide("Gravity", "Pose Keeper Gravity", pose->getGravityPtr(), 1.f, true);
        ImGuiHelper::Vector3Drag("Euler", "Pose Keeper Rotation", pose->getRotatePtr(), 1.f, 360.f);
        ImGuiHelper::Quat("Pose Keeper Quaternion", pose->getQuatPtr());

        ImGui::TreePop();
    }
}

static const char* flagNames[] = {
    "Dead",
    "Clipped",
    "Cannot Clip",
    "Draw Clipped",
    "Calc Anim On",
    "Model Visible",
    "No Collide",
    "Unknown 8",
    "Valid Mat Code",
    "Area Target",
    "Move FX Sensor",
    "Unknown 12"
};

inline void WindowActorBrowse::drawActorInspectorTreeFlags(al::LiveActorFlag* flag, float childWindowWidth)
{
    if(!flag)
        return;

    if(ImGui::TreeNode("Flags")) {
        for(int i = 0; i < 12; i++) {
            ImGui::Checkbox(flagNames[i], (bool*)((uintptr_t)flag + i));
            if(childWindowWidth >= (375.f * (*mParent->getCurrentScreenSizeMulti())) && i % 2 == 0)
                ImGui::SameLine(childWindowWidth / 2.f);
        }

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
        free(nrvName2);

        if (!nrvKeep->mStateCtrl) {
            ImGui::TreePop();
            return;
        }
        auto state = nrvKeep->mStateCtrl->mCurrentState;
        if (!state) {
            ImGui::TreePop();
            return;
        }

        char* stateName = abi::__cxa_demangle(typeid(*state->state).name(), nullptr, nullptr, &status);
        ImGui::Text("State: %s", stateName);
        if (!state->state->getNerveKeeper()) {
            free(stateName);
            ImGui::TreePop();
            return;
        }
        auto stateNerve = state->state->getNerveKeeper()->getCurrentNerve();
        char* stateNrv = abi::__cxa_demangle(typeid(*stateNerve).name(), nullptr, nullptr, &status);
        ImGui::Text("State Nrv: %s", stateNrv + strlen("(anonymous namespace)::") + strlen(stateName) + strlen("nrv"));
        free(stateName);
        free(stateNrv);

        ImGui::TreePop();
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

        ImGui::Text("Progress: %.02f", railRide->mCoord);
        ImGui::DragFloat("Speed", &railRide->mRate, 0.1f, 1000.f, -1000.f, "%.1f", ImGuiSliderFlags_NoRoundToFormat);

        ImGui::Text(railRide->mIsMoveForwards ? "Forward" : "Backward");
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
    if(!sensor || !isInStageScene())
        return;

    mParent->getPrimitiveQueue()->pushHitSensor(mSelectedActor, mHitSensorTypes, 0.4f);
}

inline void WindowActorBrowse::drawActorInspectorTreeSubActor(al::SubActorKeeper* subActorKeep)
{
    if(!subActorKeep)
        return;

    if(ImGui::TreeNode("Sub-Actors")) {
        for(int i = 0; i < subActorKeep->mCurActorCount; i++) {
            al::LiveActor* subActor = subActorKeep->mBuffer[i]->mSubActor;

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

inline void WindowActorBrowse::drawActorInspectorTreeKuriboDebug(al::LiveActor* actor) {
    if (!al::isEqualString(typeid(*actor).name(), typeid(KuriboHack).name())) {
        return;
    }
    auto kuribo = static_cast<KuriboHack*>(actor);
    if (ImGui::TreeNode("Kuribo-Debug")) {

        ImGui::Text("Detach Timer: %d", kuribo->mDetachTimer);
        ImGui::Text("KuriboTowerIdx: %d", kuribo->mKuriboTowerIdx);
        ImGui::Checkbox("field_2e0", &kuribo->unused_2e0);
        ImGui::Text("ColliderTimer: %u", kuribo->mColliderTimer);

        ImGui::TreePop();
    }
}
