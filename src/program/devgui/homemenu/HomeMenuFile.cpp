#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuFile.h"

HomeMenuFile::HomeMenuFile(DevGuiManager* parent, const char* menuName, sead::Heap* heap)
    : HomeMenuBase(parent, menuName, heap)
{}

void HomeMenuFile::updateMenu()
{
    GameDataHolder* holder = tryGetGameDataHolder();

    if(!holder)
        return;
    
    // Temporary previewer thing
    sead::FormatFixedSafeString<0x20> curSave("Current Save %i", holder->getPlayingFileId());
    ImGui::MenuItem(curSave.cstr(), NULL, false, false);

    // Quick save file loader (Maybe add custom save archive support?)

    if(addMenu("Load")) {
        SaveFileIdx targetIdx = selectSaveFile(true);
        
        if(targetIdx != SaveFileIdx::NONE) {
            holder->setPlayingFileId((int)targetIdx);
            SaveDataAccessFunction::startSaveDataLoadFile(holder);
        }

        ImGui::EndMenu();
    }
    
    // Quick save

    if(ImGui::MenuItem("Save"))
        SaveDataAccessFunction::startSaveDataWriteSync(holder);

    // Write current save into another slot

    if(addMenu("Save As")) {
        SaveFileIdx targetIdx = selectSaveFile(false);
        int curIdx = holder->getPlayingFileId();

        // FIND A WAY TO GET THE CURRENT SAVE FILE'S INDEX FOR THE FIRST PARAM!!
        if(targetIdx != SaveFileIdx::NONE)
            SaveDataAccessFunction::startSaveDataCopyWithWindow(holder, curIdx, (int)targetIdx);

        ImGui::EndMenu();
    }

    // Delete a save file.

    if(addMenu("Delete")) {
        SaveFileIdx targetIdx = selectSaveFile(false);

        if(targetIdx != SaveFileIdx::NONE)
            SaveDataAccessFunction::startSaveDataDeleteWithWindow(holder, (int)targetIdx);

        ImGui::EndMenu();
    }
}

SaveFileIdx HomeMenuFile::selectSaveFile(bool isAllowCurrentSave)
{
    SaveFileIdx sel = SaveFileIdx::NONE;

    for(int i = 0; i < SaveFileIdx::MAX_SIZE; i++) {
        sead::FormatFixedSafeString<0x10> buttonName("File %i", i);
        if(ImGui::MenuItem(buttonName.cstr()))
            sel = (SaveFileIdx)i;
    }

    return sel;
}