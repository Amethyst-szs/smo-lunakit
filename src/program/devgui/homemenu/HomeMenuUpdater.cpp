#include "devgui/DevGuiManager.h"
#include "HomeMenuUpdater.h"
#include "devgui/savedata/DevGuiSaveData.h"

#include "al/util.hpp"

#include "helpers/InputHelper.h"

#include "imgui.h"

HomeMenuUpdater::HomeMenuUpdater(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
    : HomeMenuBase(parent, menuName, isDisplayInListByDefault)
{}

void HomeMenuUpdater::updateMenu()
{
    if(!UpdateHandler::instance()->isUpdateSilenced() && UpdateHandler::instance()->isUpdateAvailable())
        mIsDisplayInList = true;
    else
        mIsDisplayInList = false;
    
    if(mIsStartInstall) {
        mIsStartInstall = false;
        UpdateHandler::instance()->downloadUpdate();
    }
}

void HomeMenuUpdater::updateMenuDisplay()
{
    UpdateHandler* update = UpdateHandler::instance();
    
    sead::FormatFixedSafeString<0x30> versionCompare("%s to %s", GIT_VER, update->getUpdateTag());
    ImGui::Text("%s", versionCompare.cstr());
    ImGui::TextDisabled("Name: %s", update->getUpdateName());
    ImGui::TextDisabled("Author: %s", update->getUpdateAuthor());
    ImGui::TextDisabled("Date: %s", update->getUpdateDate());
    ImGui::NewLine();

    if(ImGui::MenuItem("Silence Update")) {
        update->setSilenceState(true);
        mParent->getSaveData()->queueSaveWrite();
    }

    if(ImGui::MenuItem("Install Update"))
        mIsOpenInterface = true;
}

void HomeMenuUpdater::updatePostDisplay()
{
    if(mIsOpenInterface) {
        mIsOpenInterface = false;
        mIsDisplayingInterface = true;
        ImGui::OpenPopup("Install Update");
    }

    if(!mIsDisplayingInterface)
        return;

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoResize;;

    if(ImGui::BeginPopupModal("Install Update", nullptr, flags)) {
        UpdateHandler* update = UpdateHandler::instance();
        interfaceHeader(update);
        
        if(!update->isUpdateInstalling() && !update->isUpdateComplete() && !mIsStartInstall)
            interfaceSetup();

        if(update->isUpdateInstallFailDownload())
            interfaceFailedDownload();

        if(update->isUpdateInstallFailWriteToSD())
            interfaceFailedSDCard();

        if(update->isUpdateComplete())
            interfaceComplete();

        ImGui::EndPopup();
    }
}

void HomeMenuUpdater::interfaceHeader(UpdateHandler* update)
{
    ImGui::SetWindowFontScale(2.f);
    ImGui::SetWindowPos(ImVec2(mInterfaceBorder, mInterfaceBorder));
    ImGui::SetWindowSize(ImVec2(1280.f - (mInterfaceBorder * 2.f), 720.f - (mInterfaceBorder * 2.f)));

    ImGui::Text("%s ", update->getUpdateName());
    ImGui::SameLine();
    ImGui::TextDisabled("(%s - %s)", update->getUpdateAuthor(), update->getUpdateDate());

    ImGui::NewLine();

    ImGui::Text("Current Version: %s", GIT_VER);
    ImGui::Text("New Version: %s", update->getUpdateTag());

    ImGui::NewLine();
}

void HomeMenuUpdater::interfaceSetup()
{
    if(ImGui::Button("Cancel Update")) {
        mIsDisplayingInterface = false;
        ImGui::CloseCurrentPopup();
        return;
    }

    if(ImGui::Button("Install Update")) {
        mIsStartInstall = true;
        ImGui::Text("Installing...\n");
    }
}

void HomeMenuUpdater::interfaceFailedDownload()
{
    InputHelper::setInputToggled(true);
    ImGui::Text("Update could not be downloaded!\nTroubleshooting ideas:");
    ImGui::Text("Switch is not connected to the internet");
    ImGui::Text("Using 90DNS or some other DNS blocker");
}

void HomeMenuUpdater::interfaceFailedSDCard()
{
    InputHelper::setInputToggled(true);
    ImGui::Text("Update could not be written to your SD card!\nTroubleshooting ideas:");
    ImGui::Text("Your SD card is in read-only mode");
    ImGui::Text("A specific folder is in read-only mode");
    ImGui::Text("Something is corrupted with your switch's SD card reader");
}

void HomeMenuUpdater::interfaceComplete()
{
    InputHelper::setInputToggled(true);
    ImGui::Text("Update installed successfully!\nPlease restart the software");
}