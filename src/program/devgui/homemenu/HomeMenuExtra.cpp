#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuExtra.h"

HomeMenuExtra::HomeMenuExtra(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuExtra::updateMenu()
{
    bool* demoWinState = mParent->getImGuiDemoWindowState();

    if (ImGui::MenuItem("ImGui Demo Window", NULL, *demoWinState)) {
        *demoWinState = !(*demoWinState);
    }

    ImGui::MenuItem("Amethyst-szs (LunaKit Dev)", NULL, false, false);
    ImGui::MenuItem("CraftyBoss (SMO ExLaunch, SMO ImGui)", NULL, false, false);
    ImGui::MenuItem("Mars (Referenced TAS Mod)", NULL, false, false);
    ImGui::MenuItem("ExLaunch Devs", NULL, false, false);
}