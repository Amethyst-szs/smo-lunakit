#include "PrimMenuSettings.h"
#include "devgui/DevGuiManager.h"

PrimMenuSettings::PrimMenuSettings(DevGuiManager* parent)
{
    Logger::log("Starting primitive settings constructor\n");

    mParent = parent;

    // Max of 0x40 (64) settings, should never go beyond this but if you do for some reason, increase this number!
    mSettings.allocBuffer(0x40, parent->getHeap());

    // No category
    registerNewSetting(false, "Is Enabled", PrimMenuCat_NONE, false);
    
    // Player category
    registerNewSetting(false, "Player Axis", PrimMenuCat_PLAYER, false);
    registerNewSetting(false, "World Axis", PrimMenuCat_PLAYER, false);
    registerNewSetting(false, "Player Front", PrimMenuCat_PLAYER, false);
    registerNewSetting(false, "Cappy Info", PrimMenuCat_PLAYER, false);

    // Collision / Triangle category
    registerNewSetting(false, "Collision", PrimMenuCat_TRIANGLE, false);
    registerNewSetting(false, "Complex Collision", PrimMenuCat_TRIANGLE, true);

    // Area category
    registerNewSetting(false, "Areas", PrimMenuCat_AREA, false);
    registerNewSetting(false, "DeathArea", PrimMenuCat_AREA, true);
    registerNewSetting(false, "ChangeStageArea", PrimMenuCat_AREA, true);
    registerNewSetting(false, "WaterArea", PrimMenuCat_AREA, true);
    registerNewSetting(false, "2DMoveArea", PrimMenuCat_AREA, true);

    Logger::log("   Completed primitive settings constructor with %i items\n", mSettings.size());
}
void PrimMenuSettings::registerNewSetting(bool isEnabledByDefault, const char* settingName, PrimMenuCategories category, bool dependency)
{
    Logger::log("   Constructing %s in cat %i\n", settingName, category);
    PrimMenuEntry* newSet = new (mParent->getHeap()) PrimMenuEntry(isEnabledByDefault, settingName, category, dependency);
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

PrimMenuEntry* PrimMenuSettings::getSettingEntryByName(const char* name)
{
    for(int i = 0; i < mSettings.size(); i++) {
        PrimMenuEntry* entry = mSettings.at(i);
        if(al::isEqualString(entry->getName(), name))
            return entry;
    }

    return nullptr;
}