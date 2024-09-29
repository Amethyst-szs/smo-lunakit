#include "CategoryTASScripts.h"
#include "imgui.h"
#include "smo-tas/TAS.h"

CategoryTASScripts::CategoryTASScripts(const char* catName, const char* catDesc, sead::Heap* heap)
    : CategoryBase(catName, catDesc, heap) {}

void CategoryTASScripts::updateCatDisplay() {
    CategoryBase::updateCatDisplay();
    ImGui::BeginChild("Scripts", ImVec2(0,-(ImGui::GetFontSize()*8.5)), true);
    auto* tas = TAS::instance();
    s64 entryCount = tas->getEntryCount();
    nn::fs::DirectoryEntry* entries = tas->getScripts();
    for (int i = 0; i < entryCount; i++) {
        if (ImGui::Button(entries[i].mName)) {
            //Logger::log("2 Script Name: %s\n", tas->getScriptName());
            tas->setScript(entries[i]);
            //Logger::log("3 Script Name: %s\n", tas->getScriptName());
            tas->tryLoadScript();
        }
    }
    ImGui::EndChild();
}
