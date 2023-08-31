#include "program/devgui/categories/info/CategoryInfSequence.h"

#include "al/nerve/Nerve.h"
#include "al/nerve/NerveKeeper.h"

#include "helpers/GetHelper.h"

#include "imgui.h"

#include <cxxabi.h>

CategoryInfSequence::CategoryInfSequence(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap) {}

void CategoryInfSequence::updateCatDisplay()
{
    al::Sequence* sequence = tryGetSequence();

    if(!sequence) {
        ImGui::Text("Sequence does not exist!");
        return;
    }

    int status;
    al::NerveKeeper* sequenceNerveKeeper = sequence->getNerveKeeper();
    
    if(sequenceNerveKeeper) {
        char* sequenceName = abi::__cxa_demangle(typeid(*sequence).name(), nullptr, nullptr, &status);
        ImGui::Text("Type: %s", sequenceName);

        const al::Nerve* sequenceNerve = sequenceNerveKeeper->getCurrentNerve();
        char* sequenceNerveName = abi::__cxa_demangle(typeid(*sequenceNerve).name(), nullptr, nullptr, &status);
        ImGui::Text("Nrv: %s", sequenceNerveName + 23 + strlen(sequenceName) + 3);

        free(sequenceName);
        free(sequenceNerveName);
    }
}