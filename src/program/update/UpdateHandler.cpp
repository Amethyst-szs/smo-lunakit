#include "UpdateHandler.h"
#include "devgui/DevGuiManager.h"

#include "al/util.hpp"

#include "sead/heap/seadHeapMgr.h"

#include "helpers/curlHelper.h"
#include "helpers/fsHelper.h"

#include "cjson/cJSON.h"

// This class is a singleton! It does not have a typical constructor
// This is class is created in GameSystemInit in main.cpp
// Access this class from anywhere using DevGuiManager::instance()->...
SEAD_SINGLETON_DISPOSER_IMPL(UpdateHandler)
UpdateHandler::UpdateHandler() = default;
UpdateHandler::~UpdateHandler() = default;

void UpdateHandler::checkForUpdates()
{
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);

    if(mInfo) {
        Logger::log("Starting UpdateHandler again, deleting previous info\n");
        mStatus = UpdateHandlerStatus_NEEDCHECK;
        delete(mInfo);
    }

    Logger::log("Initalizing Auto-Update Handler\n");

    // Get data from GitHub API with curl
    DataStream data = DataStream(0x10);
    curlHelper::DataDownloader::downloadFromUrl(data, GIT_API_PATH);

    // Verify data was downloaded
    if(data.getSize() == 0x10) {
        mStatus = UpdateHandlerStatus_CHECKFAIL;
        Logger::log("Auto-updater: CURL could not contact GitHub API for recent release JSON\n");
        return;
    }

    // Parse out JSON from buffer
    cJSON* dataJ = cJSON_ParseWithLength((const char*)data.getData(), data.getSize());
    if(!dataJ) {
        mStatus = UpdateHandlerStatus_CHECKFAIL;
        Logger::log("Auto-updater: CURL downloaded GitHub API's recent release JSON but could not parse into json!\n");
        return;
    }

    // Get the tag name from the parsed JSON data
    const cJSON* tagName = cJSON_GetObjectItemCaseSensitive(dataJ, "tag_name");
    if (!cJSON_IsString(tagName) || !tagName->valuestring){
        mStatus = UpdateHandlerStatus_CHECKFAIL;
        Logger::log("Auto-updater: Parsed JSON could not find key \"tag_name\"\n");
        return;
    }

    // Check if that tag version differs from the tag version saved at compile, if so mark new update flag and save info
    if(!al::isEqualString(GIT_VER, tagName->valuestring)) {
        Logger::log("New Update Available! (%s -> %s)\n", GIT_VER, tagName->valuestring);
        mStatus = UpdateHandlerStatus_UPDATEREADY;

        mInfo = new (mHeap) UpdateApiInfo(dataJ, tagName);
    } else mStatus = UpdateHandlerStatus_NOUPDATE;

    cJSON_Delete(dataJ);
    return;
}

void UpdateHandler::downloadUpdate()
{
    if(!isUpdateAvailable())
        return;
    
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);

    mStatus = UpdateHandlerStatus_INSTALL;
    Logger::log("Downloading update from %s\n", GIT_RELEASE_PATH);


    // Download main.npdm
    sead::FormatFixedSafeString<0x50> npdmURL("%s/main.npdm", GIT_RELEASE_PATH);
    DataStream npdmData = DataStream(0x10);
    curlHelper::DataDownloader::downloadFromUrl(npdmData, npdmURL.cstr());

    if(npdmData.getSize() == 0x10) {
        Logger::log("Auto-updater: CURL failed to get npdm data!\n");
        mStatus = UpdateHandlerStatus_INSTALLFAILDOWNLOAD;
        return;
    }

    Logger::log("main.npdm downloaded from %s\n", npdmURL.cstr());
    

    // Download subsdk9
    sead::FormatFixedSafeString<0x50> subsdkURL("%s/subsdk9", GIT_RELEASE_PATH);
    DataStream subsdkData = DataStream(0x10);
    curlHelper::DataDownloader::downloadFromUrl(subsdkData, subsdkURL.cstr());
    
    if(subsdkData.getSize() == 0x10) {
        Logger::log("Auto-updater: CURL failed to get subsdk9 data!\n");
        mStatus = UpdateHandlerStatus_INSTALLFAILDOWNLOAD;
        return;
    }

    Logger::log("subsdk9 downloaded from %s\n", subsdkURL.cstr());

    // Write downloaded data from memory to disk
    Logger::log("Writing data to disk\n");

    if(FsHelper::writeFileToPath(npdmData.getData(), npdmData.getSize(), NPDM_PATH).isFailure()) {
        Logger::log("Auto-updater: Failed to write main.npdm to SD card!\n");
        mStatus = UpdateHandlerStatus_INSTALLFAILSDCARD;
        return;
    }

    Logger::log("main.npdm written to %s\n", NPDM_PATH);
    npdmData.~DataStream();

    if(FsHelper::writeFileToPath(subsdkData.getData(), subsdkData.getSize(), SUBSDK_PATH).isFailure()) {
        Logger::log("Auto-updater: Failed to write subsdk9 to SD card!\n");
        mStatus = UpdateHandlerStatus_INSTALLFAILSDCARD;
        return;
    }

    Logger::log("subsdk9 written to %s\n", SUBSDK_PATH);
    subsdkData.~DataStream();

    mStatus = UpdateHandlerStatus_COMPLETE;
}