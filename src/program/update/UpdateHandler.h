#pragma once

#include "helpers/curlHelper.h"
#include "helpers/fsHelper.h"

#include "cjson/cJSON.h"

#include "UpdateApiInfo.h"

#define GIT_API_PATH "https://api.github.com/repos/Amethyst-szs/smo-lunakit/releases/latest"
#define GIT_RELEASE_PATH "https://github.com/Amethyst-szs/smo-lunakit/releases/latest/download/SMO-LunaKit.zip"

enum UpdateHandlerStatus{
    UpdateHandlerStatus_NEEDCHECK,
    UpdateHandlerStatus_NOUPDATE,
    UpdateHandlerStatus_CHECKFAIL,
    UpdateHandlerStatus_UPDATEREADY,

    UpdateHandlerStatus_DOWNLOADING,
    UpdateHandlerStatus_COMPLETE,
};

class UpdateHandler {
    // This class is a singleton! It does not have a typical constructor
    // This is class is created in GameSystemInit in main.cpp
    // Access this class from anywhere using DevGuiManager::instance()->...
    SEAD_SINGLETON_DISPOSER(UpdateHandler);
    UpdateHandler();
    ~UpdateHandler();

public:
    // Tries to download the data package of what the newest version is
    void checkForUpdates(sead::Heap* heap); 
    void downloadUpdate();

    void setSilenceState(bool isSilenced) { mIsUpdateSilenced = isSilenced; }

    // Status checks
    bool isUpdateStillNeedCheck() { return mStatus == UpdateHandlerStatus_NEEDCHECK; }
    bool isUpdateNoNew() { return mStatus == UpdateHandlerStatus_NOUPDATE; }
    bool isUpdateCheckFailed() { return mStatus == UpdateHandlerStatus_CHECKFAIL; }

    bool isUpdateAvailable() { return mStatus >= UpdateHandlerStatus_UPDATEREADY; }
    bool isUpdateInstalling() { return mStatus < UpdateHandlerStatus_UPDATEREADY; }
    
    bool isUpdateDownloading() { return mStatus == UpdateHandlerStatus_DOWNLOADING; }
    bool isUpdateComplete() { return mStatus == UpdateHandlerStatus_COMPLETE; }

    bool isUpdateSilenced() { return mIsUpdateSilenced; }

    // Get metadata from mInfo
    const char* getUpdateName() { if(mInfo) return mInfo->mName.cstr(); else return nullptr; }
    const char* getUpdateTag() { if(mInfo) return mInfo->mTagName.cstr(); else return nullptr; }
    const char* getUpdateAuthor() { if(mInfo) return mInfo->mAuthorName.cstr(); else return nullptr; }
    const char* getUpdateDate() { if(mInfo) return mInfo->mPublishDate.cstr(); else return nullptr; }

private:
    UpdateApiInfo* mInfo;
    UpdateHandlerStatus mStatus;
    bool mIsUpdateSilenced = false;
};