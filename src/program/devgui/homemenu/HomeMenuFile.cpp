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
    
    if(ImGui::MenuItem("Save"))
        SaveDataAccessFunction::startSaveDataWriteSync(holder);

    if(addMenu("Save As")) {
        SaveFileIdx targetIdx = selectSaveFile();

        // FIND A WAY TO GET THE CURRENT SAVE FILE'S INDEX FOR THE FIRST PARAM!!
        if(targetIdx != SaveFileIdx::NONE)
            SaveDataAccessFunction::startSaveDataCopyWithWindow(holder, -1, (int)targetIdx);

        ImGui::EndMenu();
    }
}

SaveFileIdx HomeMenuFile::selectSaveFile()
{
    SaveFileIdx sel = SaveFileIdx::NONE;

    for(int i = 0; i < SaveFileIdx::MAX_SIZE; i++) {
        sead::FormatFixedSafeString<0x10> buttonName("File %i", i);
        if(ImGui::MenuItem(buttonName.cstr()))
            sel = (SaveFileIdx)i;
    }

    return sel;
}