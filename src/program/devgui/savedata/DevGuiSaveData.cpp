#include "DevGuiSaveData.h"
#include "devgui/DevGuiManager.h"
#include "devgui/theme/DevGuiTheme.h"
#include "devgui/settings/DevGuiSettings.h"
#include "devgui/settings/PrimMenuSettings.h"

#include "Library/Yaml/ByamlIter.h"
#include "Library/Yaml/Writer/ByamlWriter.h"
#include "al/util.hpp"

#include "nn/fs/fs_directories.h"
#include "nn/fs/fs_files.h"
#include "nn/fs/fs_types.h"

#include "helpers/fsHelper.h"
#include "helpers/DataStream.h"

#include "update/UpdateHandler.h"

#include "ghost/GhostManager.h"
#include "imgui.h"

void DevGuiSaveData::init(DevGuiManager* parent)
{
    mParent = parent;

    sead::Stream::Modes streamMode = sead::Stream::Modes::Binary;
    mRamStream = new (mHeap) sead::RamStreamSrc(&mWorkBuf, sizeof(mWorkBuf));
    mWriteStream = new (mHeap) DevGuiWriteStream(mRamStream, streamMode);
}

void DevGuiSaveData::read()
{
    FsHelper::LoadData loadData = {
        .path = SAVEPATH
    };

    if(!FsHelper::isFileExist(SAVEPATH)) {
        Logger::log("LunaKit save does not exist! Creating...\n");
        write();
        return;
    }

    FsHelper::loadFileFromPath(loadData);
    al::ByamlIter root = al::ByamlIter((u8*)loadData.buffer);

    // Before checking if the save needs to be reset, check for if the user has updates silenced
    bool isUpdatesSilenced;
    if(root.tryGetBoolByKey(&isUpdatesSilenced, "UpdateShh"))
        UpdateHandler::instance()->setSilenceState(isUpdatesSilenced);

    // Check if the program version matches the save file version, if so wipe the save and write a new one
    const char* saveVer;
    if(!root.tryGetStringByKey(&saveVer, "Version") || !al::isEqualString(saveVer, GIT_VER))
        Logger::log("Save file version does not match program version!\n");

    const char* theme;
    if(root.tryGetStringByKey(&theme, "Theme"))
        mParent->getTheme()->setWinThemeByName(theme);

    root.tryGetFloatByKey(&ImGui::GetStyle().Alpha, "Opacity");
    root.tryGetFloatByKey(mParent->getScreenSizeMultiDocked(), "DockSize");
    root.tryGetFloatByKey(mParent->getScreenSizeMultiHandheld(), "HandSize");

    if (GhostManager::instance())
        root.tryGetIntByKey(GhostManager::instance()->getMaxGhosts(), "MaxGhosts");
    else
        Logger::log("Could not load MaxGhosts. Is GhostManager null?\n");
    
    if(root.isExistKey("ActiveWins")) {
        al::ByamlIter windows = root.getIterByKey("ActiveWins");
        for(int i = 0; i < mParent->getWindowCount(); i++) {
            auto entry = mParent->getWindow(i);
            windows.tryGetBoolByKey(entry->getActiveState(), entry->getWindowName());
        }
    }

    if(root.isExistKey("Settings")) {
        al::ByamlIter windows = root.getIterByKey("Settings");
        DevGuiSettings* set = mParent->getSettings();

        for(int i = 0; i < set->getTotalSettings(); i++) {
            if(!set->getSettingEntry(i)->isAllowSave())
                continue;
            
            sead::FormatFixedSafeString<0x5> idxName("%X", i);
            windows.tryGetBoolByKey(set->getStatePtrByIdx(i), idxName.cstr());
        }
    }

    if(root.isExistKey("PrimSet")) {
        al::ByamlIter primIter = root.getIterByKey("PrimSet");
        PrimMenuSettings* primSet = mParent->getPrimitiveSettings();

        for(int i = 0; i < primSet->getTotalSettings(); i++) {
            sead::FormatFixedSafeString<0x5> idxName("%X", i);
            primIter.tryGetBoolByKey(primSet->getSettingEntry(i)->getValuePtr(), idxName.cstr());
        }
    }

    if(root.isExistKey("FavActorBrowser")) {
        al::ByamlIter favs = root.getIterByKey("FavActorBrowser");
        for(uint i = 0; i < favs.getSize(); i++) {
            const char* name = nullptr;
            sead::FormatFixedSafeString<0x5> idxName("%i", i);

            favs.tryGetStringByKey(&name, idxName.cstr());

            if(!name)
                continue;

            sead::FormatFixedSafeString<0x40> nameString(name);
            setActorBrowserFavoriteAtIdx(nameString, i);
        }
    }

    Logger::log("Successfully read save file information\n");
}

bool DevGuiSaveData::trySave()
{
    if(mIsQueueSave) {
        mSaveTimer += -0.017f; // FIX THIS, THIS SHOULD BE DElTA TIME SO IT IGNORES LAG!!
        if(mSaveTimer < 0.f) {
            mIsQueueSave = false;
            return write().IsSuccess();
        }
    }

    return false;
}

nn::Result DevGuiSaveData::write()
{
    mWriteStream->rewind();

    sead::Heap* writerHeap = sead::ExpHeap::create(1500000, "GDWriterHeap", mHeap, 8,
        sead::Heap::HeapDirection::cHeapDirection_Forward, false);

    al::ByamlWriter* file = new (writerHeap) al::ByamlWriter(writerHeap, false);
    
    file->pushHash();

    // General information
    file->addString("Version", GIT_VER);
    file->addString("Theme", mParent->getTheme()->getThemeName());
    file->addFloat("Opacity", ImGui::GetStyle().Alpha);
    file->addFloat("DockSize", *mParent->getScreenSizeMultiDocked());
    file->addFloat("HandSize", *mParent->getScreenSizeMultiHandheld());
    file->addBool("UpdateShh", UpdateHandler::instance()->isUpdateSilenced());
    file->addInt("MaxGhosts", *GhostManager::instance()->getMaxGhosts());

    // Open/close state of all windows
    file->pushHash("ActiveWins");

    for(int i = 0; i < mParent->getWindowCount(); i++) {
        file->addBool(mParent->getWindowNameAtIdx(i), *mParent->getWindowActiveStateAtIdx(i));
    }

    file->pop();

    // Current settings in the setting menu
    DevGuiSettings* set = mParent->getSettings();
    file->pushHash("Settings");

    for(int i = 0; i < set->getTotalSettings(); i++) {
        sead::FormatFixedSafeString<0x5> idxName("%X", i);
        file->addBool(idxName.cstr(), set->getStateByIdx(i));
    }

    file->pop();

    // Current primitive menu settings
    PrimMenuSettings* primSet = mParent->getPrimitiveSettings();
    file->pushHash("PrimSet");

    for(int i = 0; i < primSet->getTotalSettings(); i++) {
        sead::FormatFixedSafeString<0x5> idxName("%X", i);
        file->addBool(idxName.cstr(), primSet->getSettingEntry(i)->isTrue());
    }

    file->pop();

    // Write the Actor Browser's favorites into array

    file->pushHash("FavActorBrowser");

    for(int i = 0; i < MAXFAVS; i++) {
        sead::FixedSafeString<0x40> favName = getActorBrowserFavoriteAtIdx(i);
        if(favName.isEmpty())
            continue;

        sead::FormatFixedSafeString<0x5> idxName("%X", i);
        file->addString(idxName.cstr(), favName.cstr());
    }

    file->pop();

    // Close inital hash and write data
    file->pop();
    file->write(mWriteStream);

    uint size = file->calcPackSize();
    nn::Result result = FsHelper::writeFileToPath(mWorkBuf, size, SAVEPATH);

    Logger::log("Saved data to %s\n", SAVEPATH);

    if(static_cast<float>(size) / static_cast<float>(mWorkBufSize) > 0.8f)
        Logger::log("\n\n ! WARNING !\n The save file is close to the work buffer limit\n Consider increasing buffer size!\n\n");
    
    writerHeap->destroy();
    return result;
}

bool DevGuiSaveData::isExistImGuiLayoutFile()
{
    if(!FsHelper::isFileExist(IMGUILAYOUTPATH)) {
        Logger::log("ImGui does not have a saved layout\n");
        return false;
    }

    Logger::log("ImGui layout save exists at %s\n", IMGUILAYOUTPATH);
    return true;
}

void DevGuiSaveData::readImGuiLayout()
{
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);

    if(!FsHelper::isFileExist(IMGUILAYOUTPATH)) {
        Logger::log("ImGui does not have a saved layout.\n");
        return;
    }

    Logger::log("Loading ImGui layout from %s\n", IMGUILAYOUTPATH);

    FsHelper::LoadData loadData = {
        .path = IMGUILAYOUTPATH
    };

    FsHelper::loadFileFromPath(loadData);

    ImGui::LoadIniSettingsFromMemory((const char*)loadData.buffer, loadData.bufSize);
}

void DevGuiSaveData::writeImGuiLayout()
{
    sead::ScopedCurrentHeapSetter heapSetter(mHeap);

    size_t bufSize;
    const char* buf = ImGui::SaveIniSettingsToMemory(&bufSize);

    FsHelper::writeFileToPath((void*)buf, bufSize, IMGUILAYOUTPATH);

    Logger::log("Wrote %u bytes to %s\n", bufSize, IMGUILAYOUTPATH);
}
