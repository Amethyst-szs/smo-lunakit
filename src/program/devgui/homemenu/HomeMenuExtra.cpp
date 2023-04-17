#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuExtra.h"
#include "devgui/popups/PopupKeyboard.h"
#include "devgui/savedata/DevGuiSaveData.h"

#include "update/UpdateHandler.h"

#include "helpers/ImGuiHelper.h"
#include "helpers/InputHelper.h"

#include "logger/Logger.hpp"

#include "imgui.h"
#include "imgui_internal.h"

HomeMenuExtra::HomeMenuExtra(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
    : HomeMenuBase(parent, menuName, isDisplayInListByDefault)
{}

void HomeMenuExtra::updateMenu()
{
    if(mIsFirstStep) {
        mIsLoggerDisabled = Logger::instance().getDisabledState();
        mIsFirstStep = false;
        return;
    }

    if(!mKeyboardString)
        return;

    if(mIsIPKeyboardOpen) {
        mIPString.clear();
        mIPString.append(mKeyboardString);
    }

    if(mIsPortKeyboardOpen) {
        mPortString.clear();
        mPortString.append(mKeyboardString);
    }
}

void HomeMenuExtra::updateMenuDisplay()
{
    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
    
    ImGui::Text("Current Version: %s", GIT_VER);
    if(UpdateHandler::instance()->isUpdateSilenced() && UpdateHandler::instance()->isUpdateAvailable()) {
        ImGui::Text("Update: %s", UpdateHandler::instance()->getUpdateTag());
        ImGui::SameLine();
        if(ImGui::SmallButton("Unsilence")) {
            UpdateHandler::instance()->setSilenceState(false);
            mParent->getSaveData()->queueSaveWrite();
        }
    }

    if(ImGui::MenuItem("Check for Updates (SWITCH ONLY)"))
        UpdateHandler::instance()->checkForUpdates();

    if(!mIsLoggerDisabled && ImGui::MenuItem("Disable Logger")) {
        Logger::instance().writeLoggerSave(mHeap, true, "0", 0);
        mIsLoggerDisabled = true;
    }

    if(mIsLoggerDisabled && addMenu("Server Logging")) {
        if(ImGui::MenuItem("IP", mIPString.cstr()))
            mParent->tryOpenKeyboard(15, KEYTYPE_IP, &mKeyboardString, &mIsIPKeyboardOpen);
        
        if(ImGui::MenuItem("Port", mPortString.cstr()))
            mParent->tryOpenKeyboard(5, KEYTYPE_NUMBER, &mKeyboardString, &mIsPortKeyboardOpen);
        
        if(!mIPString.isEmpty() && !mPortString.isEmpty()) {
            ImGui::NewLine();
            ImGui::Text("Requires restart");
            ImGui::Text("Server must run on startup");
            ImGui::NewLine();
            ImGui::Text("Disable via menu or deleting:");
            ImGui::Text("LunaKit/LKData/logger.byml");

            if(ImGui::MenuItem("Activate Logger")) {
                // Jank code, converts string to number without using stoi
                mNewPort = 0;
                for(int i = 0; i < mPortString.calcLength(); i++)
                    mNewPort += (mPortString.cstr()[mPortString.calcLength() - 1 - i] - 48) * pow(10, i);

                Logger::instance().writeLoggerSave(mHeap, false, mIPString.cstr(), mNewPort);

                mIsLoggerDisabled = false;
                mIPString.clear();
                mPortString.clear();
                mKeyboardString = nullptr;
            }
        }

        ImGui::EndMenu();
    }

    static bool disableScroll = false;
    ImGui::Checkbox("Disable Scroll (For Ryujinx)", &disableScroll);

    if (disableScroll) {
        InputHelper::scrollState(!disableScroll);
    }

    bool* demoWinState = mParent->getImGuiDemoWindowState();
    if (ImGui::MenuItem("ImGui Demo Window", NULL, *demoWinState))
        *demoWinState = !(*demoWinState);

    ImGui::PopItemFlag();
}