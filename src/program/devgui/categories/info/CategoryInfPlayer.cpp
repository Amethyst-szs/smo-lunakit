#include "program/devgui/categories/info/CategoryInfPlayer.h"

#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"

#include "game/Player/PlayerActorBase.h"
#include "game/Player/PlayerActorHakoniwa.h"
#include "game/Player/PlayerFunction.h"
#include "game/Player/PlayerAnimator.h"

#include "rs/util.hpp"
#include "helpers/GetHelper.h"

#include "imgui.h"

#include <cxxabi.h>

CategoryInfPlayer::CategoryInfPlayer(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap) {}

void CategoryInfPlayer::updateCatDisplay()
{
    PlayerActorBase* player = tryGetPlayerActor();

    if(!player) {
        ImGui::Text("Player does not exist!");
        return;
    }

    /*
        // GENERIC BOOLEAN INFO
    */

    bool isDead = PlayerFunction::isPlayerDeadStatus(player);
    bool isDemo = rs::isActiveDemo(player);
    bool isGround = rs::isPlayerOnGround(player);

    ImGui::Checkbox("Dead", &isDead);
    ImGui::SameLine();
    ImGui::Checkbox("Demo", &isDemo);
    ImGui::SameLine();
    ImGui::Checkbox("Grounded", &isGround);

    /*
        // PLAYER CLASS, STATE, AND NERVES
    */
    
    // Actor name and nerve

    char* playerName = nullptr;
    char* stateName = nullptr;
    char* stateNrvName = nullptr;

    int status;
    const al::Nerve* playerNerve = player->getNerveKeeper()->getCurrentNerve();
    playerName = abi::__cxa_demangle(typeid(*player).name(), nullptr, nullptr, &status);
    
    if (player->getNerveKeeper()->mStateCtrl) {
        al::State* state = player->getNerveKeeper()->mStateCtrl->findStateInfo(playerNerve);
        if(state) {
            const al::Nerve* stateNerve = state->mStateBase->getNerveKeeper()->getCurrentNerve();
            stateName = abi::__cxa_demangle(typeid(*state->mStateBase).name(), nullptr, nullptr, &status);
            stateNrvName = abi::__cxa_demangle(typeid(*stateNerve).name(), nullptr, nullptr, &status);
        }
    }

    if (playerName) {
        ImGui::Text("Class: %s", playerName);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Type of Player Actor\nHakoniwa is normal Mario\nYukimaru is Shiverian Racer");
        free(playerName);
    }

    if(stateName && stateNrvName) {
        ImGui::Text("State: %s", stateName);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Current type of action\nthe player is performing");

        ImGui::Text("State Nrv: %s", stateNrvName + 23 + strlen(stateName) + 3);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Basically the sub-action\nCurrent nerve of the state");

        free(stateName);
        free(stateNrvName);
    }

    /*
        // PLAYER ANIMATIONS (ONLY IF PlayerActorHakoniwa)
    */

    PlayerActorHakoniwa* playerHak = tryGetPlayerActorHakoniwa();
    if(!playerHak) {
        ImGui::TextDisabled("Cannot display additional info, not Hakoniwa");
        return;
    }

    PlayerAnimator* anim = playerHak->mPlayerAnimator;
    ImGui::Text("Anim: %s (%.00f/%.00f)", anim->curAnim.cstr(), anim->getAnimFrame(), anim->getAnimFrameMax());
    ImGui::Text("Sub Anim: %s (%.00f/%.00f)", anim->curSubAnim.cstr(), anim->getSubAnimFrame(), anim->getSubAnimFrameMax());

    sead::Vector3f kidsPos = playerHak->mPlayerRecoverySafetyPoint->mSafetyPointPos;
    ImGui::InputFloat3("Assist Pos", &kidsPos.x, "%.00f", ImGuiInputTextFlags_ReadOnly);
}