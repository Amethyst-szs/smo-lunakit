#include "devgui/DevGuiManager.h"

#include "DevGuiSaveData.h"

DevGuiWriteStream::DevGuiWriteStream(sead::RamStreamSrc* src, sead::Stream::Modes mode)
{
    mSrc = src;
    setMode(mode);
}

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

    // Check if the program version matches the save file version, if so wipe the save and write a new one
    const char* saveVer;
    if(!root.tryGetStringByKey(&saveVer, "Version") || !al::isEqualString(saveVer, LUNAKITVERSION)) {
        Logger::log("Save file version does not match program version, resetting...\n");
        write();
        return;
    }

    const char* theme;
    if(root.tryGetStringByKey(&theme, "Theme"))
        mParent->getTheme()->setWinThemeByName(theme);

    int winAnchor;
    if(root.tryGetIntByKey(&winAnchor, "WinAnchor"))
        mParent->setAnchorType((WinAnchorType)winAnchor);
    
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
                
            windows.tryGetBoolByKey(set->getStatePtrByIdx(i), set->getNameByIdx(i));
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
            return write().isSuccess();
        }
    }

    return false;
}

nn::Result DevGuiSaveData::write()
{
    mWriteStream->rewind();

    al::ByamlWriter file = al::ByamlWriter(al::getSequenceHeap(), false);
    
    file.pushHash();

    // General information
    file.addString("Version", LUNAKITVERSION);
    file.addString("Theme", mParent->getTheme()->getThemeName());
    file.addInt("WinAnchor", (int)mParent->getAnchorType());

    // Open/close state of all windows
    file.pushHash("ActiveWins");

    for(int i = 0; i < mParent->getWindowCount(); i++) {
        file.addBool(mParent->getWindowNameAtIdx(i), *mParent->getWindowActiveStateAtIdx(i));
    }

    file.pop();

    // Current settings in the setting menu
    DevGuiSettings* set = mParent->getSettings();
    file.pushHash("Settings");

    for(int i = 0; i < set->getTotalSettings(); i++) {
        file.addBool(set->getNameByIdx(i), set->getStateByIdx(i));
    }

    file.pop();

    // Write the Actor Browser's favorites into array

    file.pushHash("FavActorBrowser");

    for(int i = 0; i < MAXFAVS; i++) {
        sead::FixedSafeString<0x40> favName = getActorBrowserFavoriteAtIdx(i);
        if(favName.isEmpty())
            continue;

        sead::FormatFixedSafeString<0x5> idxName("%i", i);
        file.addString(idxName.cstr(), favName.cstr());
    }

    file.pop();

    // Close inital hash and write data
    file.pop();
    file.write(mWriteStream);

    nn::Result result = FsHelper::writeFileToPath(mWorkBuf, file.calcPackSize(), SAVEPATH);

    return result;
}