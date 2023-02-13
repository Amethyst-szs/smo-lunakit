#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuCredits.h"

HomeMenuCredits::HomeMenuCredits(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuCredits::updateMenu()
{
    ImGui::MenuItem("Amethyst-szs", "LunaKit Dev", false, false);
    ImGui::MenuItem("CraftyBoss", "SMO ExLaunch Base, ImGui, World List", false, false);
    ImGui::MenuItem("Mars", "Referenced TAS Mod", false, false);
    ImGui::MenuItem("ExLaunch", "", false, false);
}