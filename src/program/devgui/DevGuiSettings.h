#pragma once

#include "heap/seadDisposer.h"

class DevGuiSettings {
    SEAD_SINGLETON_DISPOSER(DevGuiSettings);
    DevGuiSettings();
    ~DevGuiSettings();

public:
    // Gameplay Settings
    // Add autosave, hide hud, autosaving, and noclip here

    // Debug Settings
    bool mIsDisplayImGuiDemo = false;
};