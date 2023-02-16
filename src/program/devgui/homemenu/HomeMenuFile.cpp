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
        SaveFileIdx targetIdx = selectSaveFile(holder, true);
        
        if(targetIdx != SaveFileIdx::NONE) {
            holder->requestSetPlayingFileId((int)targetIdx);
        }

        ImGui::EndMenu();
    }
    
    // Quick save

    if(ImGui::MenuItem("Save"))
        SaveDataAccessFunction::startSaveDataWrite(holder);

    // Write current save into another slot

    if(addMenu("Save As")) {
        int curIdx = holder->getPlayingFileId();

        SaveFileIdx targetIdx = selectSaveFile(holder, false);
        
        // FIND A WAY TO GET THE CURRENT SAVE FILE'S INDEX FOR THE FIRST PARAM!!
        if(targetIdx != SaveFileIdx::NONE)
            SaveDataAccessFunction::startSaveDataCopyWithWindow(holder, curIdx, (int)targetIdx);

        ImGui::EndMenu();
    }

    // Delete a save file.

    if(addMenu("Delete")) {
        SaveFileIdx targetIdx = selectSaveFile(holder, false);

        if(targetIdx != SaveFileIdx::NONE)
            SaveDataAccessFunction::startSaveDataDeleteWithWindow(holder, (int)targetIdx);

        ImGui::EndMenu();
    }
}

SaveFileIdx HomeMenuFile::selectSaveFile(GameDataHolder* holder, bool isAllowCurrentSave)
{
    SaveFileIdx sel = SaveFileIdx::NONE;

    for(int i = 0; i < SaveFileIdx::MAX_SIZE; i++) {
        sead::FormatFixedSafeString<0x10> buttonName("File %i", i);

        if(!isAllowCurrentSave && i == holder->getPlayingFileId()) {
            ImGui::MenuItem(buttonName.cstr(), NULL, false, false);
            continue;
        }

        if(ImGui::MenuItem(buttonName.cstr()))
            sel = (SaveFileIdx)i;
    }

    return sel;
}