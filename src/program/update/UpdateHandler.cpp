#include "UpdateHandler.h"
#include "devgui/DevGuiManager.h"

// This class is a singleton! It does not have a typical constructor
// This is class is created in GameSystemInit in main.cpp
// Access this class from anywhere using DevGuiManager::instance()->...
SEAD_SINGLETON_DISPOSER_IMPL(UpdateHandler)
UpdateHandler::UpdateHandler() = default;
UpdateHandler::~UpdateHandler() = default;

void UpdateHandler::init()
{
    Logger::log("Starting version handler\n");
    
    DataStream data = DataStream(0x10);
    
    curlHelper::DataDownloader::downloadFromUrl(data, "https://sanae6.ca/share/amy/version.byml");
    al::ByamlIter dataByml = al::ByamlIter(data.getData());

    const char* newVerName;
    if (!dataByml.tryGetStringByKey(&newVerName, "Ver")) {
        Logger::log("Version data byml from curl missing \"Ver\" key!\n");
        mIsCurlFail = true;
        return;
    }

    Logger::log("Local: %s - Server: %s\n", GIT_VER, newVerName);

    // DataStream release = DataStream(0x10);
    // curlHelper::DataDownloader::downloadFromUrl(release, "https://sanae6.ca/share/amy/balls.zip");

    // zip_extract("foo.zip", "/tmp", on_extract_entry, &arg);
    // zip_entry_open
}