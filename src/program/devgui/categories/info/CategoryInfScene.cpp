#include "program/devgui/categories/info/CategoryInfScene.h"

CategoryInfScene::CategoryInfScene(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap) {}

void CategoryInfScene::updateCatDisplay()
{
    al::Scene* scene = tryGetScene();

    if(!scene) {
        ImGui::Text("Scene does not exist!");
        return;
    }

    PlayerActorBase* player = tryGetPlayerActor(scene);

    ImGui::Text("Name: %s", GameDataFunction::getCurrentStageName(scene));
    if(player)
        ImGui::Text("Scenario: %u", GameDataFunction::getScenarioNo(player));

    int status;
    al::NerveKeeper* sceneNerveKeeper = scene->getNerveKeeper();
    
    if(sceneNerveKeeper) {
        char* sceneName = abi::__cxa_demangle(typeid(*scene).name(), nullptr, nullptr, &status);
        ImGui::Text("Type: %s", sceneName);

        al::Nerve* sceneNerve = sceneNerveKeeper->getCurrentNerve();
        char* sceneNerveName = abi::__cxa_demangle(typeid(*sceneNerve).name(), nullptr, nullptr, &status);
        ImGui::Text("Nrv: %s", sceneNerveName + 23 + strlen(sceneName) + 3);

        free(sceneName);
        free(sceneNerveName);
    }
}