#include "devgui/DevGuiManager.h"
#include "HomeMenuUpdater.h"
#include "imgui.h"

HomeMenuUpdater::HomeMenuUpdater(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
    : HomeMenuBase(parent, menuName, isDisplayInListByDefault)
{
    for (sead::Heap& childRef : mHeap->mChildren) {
        sead::Heap* child = &childRef;

        const char* childName = child->getName().cstr();
        if (al::isEqualString(childName, "UpdateHeap"))
            mUpdateHeap = child;
    }
}

void HomeMenuUpdater::updateMenu()
{
    if(!UpdateHandler::instance()->isUpdateSilenced() && UpdateHandler::instance()->isUpdateAvailable())
        mIsDisplayInList = true;
    else
        mIsDisplayInList = false;
    
    if(mIsStartInstall) {
        mIsStartInstall = false;
        UpdateHandler::instance()->downloadUpdate(mUpdateHeap);
    }
}

void HomeMenuUpdater::updateMenuDisplay()
{
    UpdateHandler* update = UpdateHandler::instance();
    
    sead::FormatFixedSafeString<0x30> versionCompare("%s to %s", GIT_VER, update->getUpdateTag());
    ImGui::MenuItem(versionCompare.cstr());

    ImGui::MenuItem("Name", update->getUpdateName(), false, false);
    ImGui::MenuItem("Author", update->getUpdateAuthor(), false, false);
    ImGui::MenuItem("Date", update->getUpdateDate(), false, false);
    ImGui::MenuItem(" ", nullptr, false, false);

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

        if(update->isUpdateInstallFail())
            interfaceFailed();

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

void HomeMenuUpdater::interfaceFailed()
{
    InputHelper::setInputToggled(true);
    ImGui::Text("Update could not be installed correctly!\nTroubleshooting ideas:");
    ImGui::Text("Switch is not connected to the internet");
    ImGui::Text("Using 90DNS or some other DNS blocker");
}

void HomeMenuUpdater::interfaceComplete()
{
    InputHelper::setInputToggled(true);
    ImGui::Text("Update installed successfully!\nPlease restart the software");
}