#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuDebugger.h"

HomeMenuDebugger::HomeMenuDebugger(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuDebugger::updateMenu()
{
    bool* demoWinState = mParent->getImGuiDemoWindowState();

    if (ImGui::MenuItem("ImGui Demo Window", NULL, demoWinState)) {
        *demoWinState = !(*demoWinState);
    }
}