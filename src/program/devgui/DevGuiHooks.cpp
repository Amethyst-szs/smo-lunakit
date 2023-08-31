#include "DevGuiHooks.h"

void DevGuiHooks::exlInstallDevGuiHooks() {
    exlSetupSettingsHooks();
    exlSetupGraphicsHooks();
    exlSetupStageSceneHooks();
}