#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuFile.h"

#include "game/SaveData/SaveDataAccessFunction.h"

#include "helpers/GetHelper.h"

#include "imgui.h"

HomeMenuFile::HomeMenuFile(DevGuiManager* parent, const char* menuName, bool isDisplayInListByDefault)
    : HomeMenuBase(parent, menuName, isDisplayInListByDefault)
{}

void HomeMenuFile::updateMenuDisplay()
{
    GameDataHolder* holder = tryGetGameDataHolder();

    if(!holder)
        return;
    
    bool isSaved = SaveDataAccessFunction::isDoneSave(holder);

    // Quick save file loader (Maybe add custom save archive support?)
    if(addMenu("Load (Incomplete)", false)) {
        SaveFileIdx targetIdx = selectSaveFile(holder, true);
        
        if(targetIdx != SaveFileIdx::NONE) {
            holder->requestSetPlayingFileId((int)targetIdx);
            
        }

        ImGui::EndMenu();
    }
    
    // Quick save
    if(ImGui::MenuItem("Save", NULL, false, isSaved))
        SaveDataAccessFunction::startSaveDataWrite(holder);

    // Write current save into another slot
    if(addMenu("Save As", isSaved)) {
        int curIdx = holder->getPlayingFileId();

        SaveFileIdx targetIdx = selectSaveFile(holder, false);
        
        // FIND A WAY TO GET THE CURRENT SAVE FILE'S INDEX FOR THE FIRST PARAM!!
        if(targetIdx != SaveFileIdx::NONE)
            SaveDataAccessFunction::startSaveDataCopyWithWindow(holder, curIdx, (int)targetIdx);

        ImGui::EndMenu();
    }

    // Delete a save file.
    if(addMenu("Delete", isSaved)) {
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
        sead::FormatFixedSafeString<0x10> buttonName("File %i", i + 1);

        if(!isAllowCurrentSave && i == holder->getPlayingFileId()) {
            ImGui::MenuItem(buttonName.cstr(), NULL, false, false);
            continue;
        }

        if(ImGui::MenuItem(buttonName.cstr()))
            sel = (SaveFileIdx)i;
    }

    return sel;
}