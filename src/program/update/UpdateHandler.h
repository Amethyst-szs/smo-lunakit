#pragma once

#include "al/byaml/ByamlIter.h"

#include "sead/prim/seadSafeString.h"

#include "helpers/curlHelper.h"
#include "helpers/fsHelper.h"

#include "zip.h"

#define RELEASE_PATH "https://github.com/Amethyst-szs/smo-lunakit/releases/latest/download/SMO-LunaKit.zip"

class UpdateHandler {
    // This class is a singleton! It does not have a typical constructor
    // This is class is created in GameSystemInit in main.cpp
    // Access this class from anywhere using DevGuiManager::instance()->...
    SEAD_SINGLETON_DISPOSER(UpdateHandler);
    UpdateHandler();
    ~UpdateHandler();

public:
    // Tries to download the data package of what the newest version is
    void init(); 

    void downloadUpdate();

    bool isUpdateAvailable() { return mIsNewUpdate; }
    bool isUpdateCurlFailed() { return mIsCurlFail; }

private:
    bool mIsNewUpdate = false;
    bool mIsCurlFail = false;
};