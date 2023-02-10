#include "program/devgui/homemenu/HomeMenuCredits.h"

HomeMenuCredits::HomeMenuCredits(const char* menuName, sead::Heap* heap)
    : HomeMenuBase(menuName, heap)
{}

void HomeMenuCredits::updateMenu()
{
    ImGui::MenuItem("Amethyst-szs", "LunaKit Dev", false, false);
    ImGui::MenuItem("CraftyBoss", "SMO ExLaunch Base, ImGui, World List", false, false);
    ImGui::MenuItem("Mars", "Referenced TAS Mod", false, false);
    ImGui::MenuItem("ExLaunch", "", false, false);
}