#include "program/devgui/homemenu/HomeMenuDebugger.h"

HomeMenuDebugger::HomeMenuDebugger(const char* menuName, sead::Heap* heap)
    : HomeMenuBase(menuName, heap)
{}

void HomeMenuDebugger::updateMenu()
{
    if (ImGui::MenuItem("ImGui Demo Window", "", DevGuiSettings::instance()->mIsDisplayImGuiDemo)) {
        bool* state = &DevGuiSettings::instance()->mIsDisplayImGuiDemo;
        *state = !(*state);
    }
}