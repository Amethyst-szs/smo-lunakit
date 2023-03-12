#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuExtra.h"

HomeMenuExtra::HomeMenuExtra(DevGuiManager* parent, const char* menuName)
    : HomeMenuBase(parent, menuName)
{}

void HomeMenuExtra::updateMenuDisplay()
{
    bool* demoWinState = mParent->getImGuiDemoWindowState();

    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

    if (addMenu("Keyboard Test")) {
        if(mKeyboardString && strlen(mKeyboardString) > 0)
            ImGui::MenuItem(mKeyboardString, nullptr, false, false);

        if(ImGui::MenuItem("QWERTY"))
            mParent->tryOpenKeyboard(16, KEYTYPE_QWERTY, &mKeyboardString, &mIsKeyboardOpen);
        if(ImGui::MenuItem("Number"))
            mParent->tryOpenKeyboard(16, KEYTYPE_NUMBER, &mKeyboardString, &mIsKeyboardOpen);
        if(ImGui::MenuItem("IP"))
            mParent->tryOpenKeyboard(16, KEYTYPE_IP, &mKeyboardString, &mIsKeyboardOpen);

        ImGui::EndMenu();
    }

    ImGui::PopItemFlag();

    if (ImGui::MenuItem("ImGui Demo Window", NULL, *demoWinState)) {
        *demoWinState = !(*demoWinState);
    }

    ImGui::MenuItem("Amethyst-szs (LunaKit Dev)", NULL, false, false);
    ImGui::MenuItem("CraftyBoss", NULL, false, false);
    ImGui::MenuItem("Mars", NULL, false, false);
    ImGui::MenuItem("ExLaunch Devs", NULL, false, false);
}