#include "program/devgui/categories/CategoryInfPlayer.h"

CategoryInfPlayer::CategoryInfPlayer(const char* catName, const char* catDesc)
    : CategoryBase(catName, catDesc)
{
}

void CategoryInfPlayer::updateCatDisplay()
{
    PlayerActorBase* player = tryGetPlayerActor();

    if(!player) {
        ImGui::Text("Player does not exist!");
        return;
    }

    // Log generic boolean info about player

    bool isDead = PlayerFunction::isPlayerDeadStatus(player);
    bool isDemo = rs::isActiveDemo(player);
    bool isGround = rs::isPlayerOnGround(player);

    ImGui::Checkbox("Dead", &isDead);
    ImGui::SameLine();
    ImGui::Checkbox("Demo", &isDemo);
    ImGui::SameLine();
    ImGui::Checkbox("Grounded", &isGround);

    /*
        // Log player's nerve and state information
    */
    
    // Actor name and nerve

    int status;
    al::Nerve* playerNerve = player->getNerveKeeper()->getCurrentNerve();
    char* playerName = abi::__cxa_demangle(typeid(*player).name(), nullptr, nullptr, &status);
    char* nrvName = abi::__cxa_demangle(typeid(*playerNerve).name(), nullptr, nullptr, &status);

    ImGui::Text("%s - %s", playerName, nrvName + 23 + strlen(playerName) + 3);

    free(playerName);
    free(nrvName);

    // Log player's state and state nerve

    al::State* state = player->getNerveKeeper()->mStateCtrl->findStateInfo(playerNerve);
    if(state) {
        al::Nerve* stateNerve = state->mStateBase->getNerveKeeper()->getCurrentNerve();
        char* stateName = abi::__cxa_demangle(typeid(*state->mStateBase).name(), nullptr, nullptr, &status);
        char* stateNrvName = abi::__cxa_demangle(typeid(*stateNerve).name(), nullptr, nullptr, &status);

        ImGui::Text("%s - %s", stateName, stateNrvName + 23 + strlen(stateName) + 3);

        free(stateName);
        free(stateNrvName);
    }
}