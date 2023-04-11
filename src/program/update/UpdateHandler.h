#pragma once

#include "helpers/curlHelper.h"
#include "helpers/fsHelper.h"

#include "cjson/cJSON.h"

#include "UpdateApiInfo.h"

#define GIT_API_PATH "https://api.github.com/repos/Amethyst-szs/smo-lunakit/releases/latest"
#define GIT_RELEASE_PATH "https://github.com/Amethyst-szs/smo-lunakit/releases/latest/download/SMO-LunaKit.zip"

class UpdateHandler {
    // This class is a singleton! It does not have a typical constructor
    // This is class is created in GameSystemInit in main.cpp
    // Access this class from anywhere using DevGuiManager::instance()->...
    SEAD_SINGLETON_DISPOSER(UpdateHandler);
    UpdateHandler();
    ~UpdateHandler();

public:
    // Tries to download the data package of what the newest version is
    void init(sead::Heap* heap); 
    void downloadUpdate();

    bool isUpdateAvailable() { return mIsNewUpdate; }
    bool isUpdateCurlFailed() { return mIsCurlFail; }

    const char* getUpdateName() { if(mInfo) return mInfo->mName.cstr(); else return nullptr; }
    const char* getUpdateTag() { if(mInfo) return mInfo->mTagName.cstr(); else return nullptr; }
    const char* getUpdateAuthor() { if(mInfo) return mInfo->mAuthorName.cstr(); else return nullptr; }
    const char* getUpdateDate() { if(mInfo) return mInfo->mPublishDate.cstr(); else return nullptr; }

private:
    UpdateApiInfo* mInfo;
    bool mIsNewUpdate = false;
    bool mIsCurlFail = false;
};