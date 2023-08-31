#pragma once

#include "settings/SettingsHooks.h"
#include "windows/Graphics/GraphicsHooks.h"
#include "windows/StagePause/StagePauseHooks.h"

#include "windows/Graphics/WindowGBuffer.h"
#include "windows/Graphics/WindowPresets.h"

class DevGuiHooks {
    GBufferSet* mGBufferSettings = new GBufferSet();
    GraphicsPresetSet* mGraphicsPresetSettings = new GraphicsPresetSet();

public:
    GBufferSet* getGBufferSettings() { return mGBufferSettings; };
    GraphicsPresetSet* getGraphicsPresetSettings() { return mGraphicsPresetSettings; };

    static void exlInstallDevGuiHooks();
};