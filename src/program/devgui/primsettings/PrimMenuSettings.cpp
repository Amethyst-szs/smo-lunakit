#include "PrimMenuSettings.h"
#include "devgui/DevGuiManager.h"

PrimMenuSettings::PrimMenuSettings(DevGuiManager* parent)
{
    Logger::log("Starting primitive settings constructor\n");

    mParent = parent;

    // Max of 0x40 (64) settings, should never go beyond this but if you do for some reason, increase this number!
    mSettings.allocBuffer(0x40, parent->getHeap());

    // No category
    registerNewSetting(false, "Is Enabled", PrimMenuCat_NONE);
    
    // Player category
    registerNewSetting(false, "Player Axis", PrimMenuCat_PLAYER);
    registerNewSetting(false, "World Axis", PrimMenuCat_PLAYER);
    registerNewSetting(false, "Player Front", PrimMenuCat_PLAYER);
    registerNewSetting(false, "Cappy", PrimMenuCat_PLAYER);

    // Collision / Triangle category
    registerNewSetting(false, "Collision", PrimMenuCat_TRIANGLE);
    registerNewSetting(false, "Complex Colission", PrimMenuCat_TRIANGLE);

    // Area category
    registerNewSetting(false, "Areas", PrimMenuCat_AREA);
    registerNewSetting(false, "DeathArea", PrimMenuCat_AREA);
    registerNewSetting(false, "ChangeStageArea", PrimMenuCat_AREA);
    registerNewSetting(false, "WaterArea", PrimMenuCat_AREA);
    registerNewSetting(false, "2DMoveArea", PrimMenuCat_AREA);

    Logger::log("   Completed primitive settings constructor with %i items\n", mSettings.size());
}
void PrimMenuSettings::registerNewSetting(bool isEnabledByDefault, const char* settingName, PrimMenuCategories category)
{
    Logger::log("   Constructing %s in cat %i\n", settingName, category);
    PrimMenuEntry* newSet = new (mParent->getHeap()) PrimMenuEntry(isEnabledByDefault, settingName, category);
    mSettings.pushBack(newSet);
}

int PrimMenuSettings::getTotalSettingsInCat(PrimMenuCategories cat)
{
    int total = 0;

    for(int i = 0; i < mSettings.size(); i++) {
        if(mSettings.at(i)->getCategory() == cat)
            total++;
    }

    return total;
}

PrimMenuEntry* PrimMenuSettings::getSettingEntryInCat(int idx, PrimMenuCategories cat)
{
    int catIdx = 0;

    for(int i = 0; i < mSettings.size(); i++) {
        if(mSettings.at(i)->getCategory() != cat)
            continue;
            
        if(catIdx == idx)
            return mSettings.at(i);

        catIdx++;
    }

    return nullptr;
}