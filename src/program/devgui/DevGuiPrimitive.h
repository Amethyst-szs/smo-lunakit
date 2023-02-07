#pragma once

#include "program/SequenceUtil.h"
#include "heap/seadDisposer.h"

struct PrimitivePlayerSettings {
    bool mDrawAxis = true;
    bool mDrawFront = true;
    bool mDrawHackCap = true;
};

struct PrimitiveTriangleSettings {
    bool mDrawTriangle = true;
    bool mDrawComplexTriangle = false;
};

struct PrimitiveAreaSettings {
    bool mDrawAreas = true;

    bool mDrawAreaDeath = false;
    bool mDrawAreaStage = true;
    bool mDrawAreaWater = true;
    bool mDrawArea2D = true;
};

class DevGuiPrimitive {
    SEAD_SINGLETON_DISPOSER(DevGuiPrimitive);
    DevGuiPrimitive();
    ~DevGuiPrimitive();

public:
    void draw(); // Take parameters for renderer (likely draw context, scene, and renderer?)
    void drawAreaGroup(const char* areaName);
    
    bool mIsDrawPrimitives = true;
    PrimitivePlayerSettings mSettingsPlayer;
    PrimitiveTriangleSettings mSettingsTriangle;
    PrimitiveAreaSettings mSettingsArea;
};