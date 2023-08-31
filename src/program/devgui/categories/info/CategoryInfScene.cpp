#include "program/devgui/categories/info/CategoryInfScene.h"

#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"

#include "helpers/GetHelper.h"

#include "imgui.h"

#include <cxxabi.h>

CategoryInfScene::CategoryInfScene(const char* catName, const char* catDesc, sead::Heap* heap) : CategoryBase(catName, catDesc, heap) {}

void CategoryInfScene::updateCatDisplay() {
    HakoniwaSequence* sequence = tryGetHakoniwaSequence();
    if (!sequence) {
        ImGui::Text("Hakoniwa Sequence does not exist!");
        return;
    }

    al::Scene* scene = tryGetScene(sequence);
    if (!scene) {
        ImGui::Text("Scene does not exist!");
        return;
    }

    ImGui::Text("Name: %s", sequence->stageName.cstr());
    ImGui::Text("Scenario: %u", sequence->scenarioNum);

    int status;
    al::NerveKeeper* sceneNerveKeeper = scene->getNerveKeeper();
    if (!sceneNerveKeeper)
        return;

    char* sceneName = abi::__cxa_demangle(typeid(*scene).name(), nullptr, nullptr, &status);
    ImGui::Text("Type: %s", sceneName);

    const al::Nerve* sceneNerve = sceneNerveKeeper->getCurrentNerve();
    char* sceneNerveName = abi::__cxa_demangle(typeid(*sceneNerve).name(), nullptr, nullptr, &status);
    auto prefixLen = sceneNerveName[0] == '(' ? strlen("(anonymous namespace)::") : 0;
    ImGui::Text("Nrv: %s", sceneNerveName + prefixLen + strlen(sceneName) + strlen("nrv"));
    ImGui::SameLine();
    ImGui::Text("\tStep: %d", sceneNerveKeeper->mStep);

    free(sceneName);
    free(sceneNerveName);

    if (!scene->getNerveKeeper()->mStateCtrl)
        return;
    al::State* state = scene->getNerveKeeper()->mStateCtrl->findStateInfo(sceneNerve);
    if (!state)
        return;
    const al::Nerve* stateNerve = state->mStateBase->getNerveKeeper()->getCurrentNerve();
    char* stateName = abi::__cxa_demangle(typeid(*state->mStateBase).name(), nullptr, nullptr, &status);
    char* stateNrvName = abi::__cxa_demangle(typeid(*stateNerve).name(), nullptr, nullptr, &status);
    ImGui::Text("State: %s", stateName);
    ImGui::Text("State Nrv: %s", stateNrvName + strlen("(anonymous namespace)::") + strlen(stateName) + strlen("nrv"));
    ImGui::SameLine();
    ImGui::Text("\tStep: %d", state->mStateBase->getNerveKeeper()->mStep);

    free(stateName);
    free(stateNrvName);
}