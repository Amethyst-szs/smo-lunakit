#include "UpdateHandler.h"
#include "devgui/DevGuiManager.h"

// This class is a singleton! It does not have a typical constructor
// This is class is created in GameSystemInit in main.cpp
// Access this class from anywhere using DevGuiManager::instance()->...
SEAD_SINGLETON_DISPOSER_IMPL(UpdateHandler)
UpdateHandler::UpdateHandler() = default;
UpdateHandler::~UpdateHandler() = default;

void UpdateHandler::checkForUpdates(sead::Heap* heap)
{
    if(mInfo) {
        Logger::log("Starting UpdateHandler again, deleting previous info\n");
        mIsNewUpdate = false;
        mIsCurlFail = false;
        delete(mInfo);
    }

    Logger::log("Initalizing Auto-Update Handler\n");

    // Get data from GitHub API with curl
    DataStream data = DataStream(0x10);
    curlHelper::DataDownloader::downloadFromUrl(data, GIT_API_PATH);

    // Verify data was downloaded
    if(data.getSize() == 0x10) {
        mIsCurlFail = true;
        Logger::log("Auto-updater: CURL could not contact GitHub API for recent release JSON\n");
        return;
    }

    // Parse out JSON from buffer
    cJSON* dataJ = cJSON_ParseWithLength((const char*)data.getData(), data.getSize());
    if(!dataJ) {
        mIsCurlFail = true;
        Logger::log("Auto-updater: CURL downloaded GitHub API's recent release JSON but could not parse into json!\n");
        return;
    }

    // Get the tag name from the parsed JSON data
    const cJSON* tagName = cJSON_GetObjectItemCaseSensitive(dataJ, "tag_name");
    if (!cJSON_IsString(tagName) || !tagName->valuestring){
        mIsCurlFail = true;
        Logger::log("Auto-updater: Parsed JSON could not find key \"tag_name\"\n");
        return;
    }

    // Check if that tag version differs from the tag version saved at compile, if so mark new update flag and save info
    if(!al::isEqualString(GIT_VER, tagName->valuestring)) {
        Logger::log("New Update Available! (%s -> %s)\n", GIT_VER, tagName->valuestring);
        mIsNewUpdate = true;

        mInfo = new (heap) UpdateApiInfo(dataJ, tagName);
    }

    cJSON_Delete(dataJ);
    return;
}