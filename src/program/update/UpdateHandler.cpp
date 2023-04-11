#include "UpdateHandler.h"
#include "devgui/DevGuiManager.h"

#include "cjson/cJSON.h"

// This class is a singleton! It does not have a typical constructor
// This is class is created in GameSystemInit in main.cpp
// Access this class from anywhere using DevGuiManager::instance()->...
SEAD_SINGLETON_DISPOSER_IMPL(UpdateHandler)
UpdateHandler::UpdateHandler() = default;
UpdateHandler::~UpdateHandler() = default;

void UpdateHandler::init()
{
    Logger::log("Initalizing automatic update handler\n");

    DataStream data = DataStream(0x10);
    curlHelper::DataDownloader::downloadFromUrl(data, "https://api.github.com/repos/Amethyst-szs/smo-lunakit/releases/latest");

    if(data.getSize() == 0x10) {
        mIsCurlFail = true;
        Logger::log("Auto-updater: CURL could not contact GitHub API for recent release JSON\n");
        return;
    }

    cJSON* dataJ = cJSON_ParseWithLength((const char*)data.getData(), data.getSize());
    if(!dataJ) {
        mIsCurlFail = true;
        Logger::log("Auto-updater: CURL downloaded GitHub API's recent release JSON but could not parse into json!\n");
        return;
    }

    const cJSON* tagName = cJSON_GetObjectItemCaseSensitive(dataJ, "tag_name");
    if (!cJSON_IsString(tagName) || !tagName->valuestring){
        mIsCurlFail = true;
        Logger::log("Auto-updater: Parsed JSON could not find key \"tag_name\"\n");
        return;
    }

    if(!al::isEqualString(GIT_VER, tagName->valuestring)) {
        Logger::log("New update available\nBuild Version: %s\nServer Version: %s\n", GIT_VER, tagName->valuestring);
        mIsNewUpdate = true;
    }

    cJSON_Delete(dataJ);
    return;
}