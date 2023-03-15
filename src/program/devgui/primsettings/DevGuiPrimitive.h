
/*
    THIS CLASS IS DEPRICATED

    This is being replaced by the PrimitiveQueue and HomeMenuPrims
    Please use those for any primitive renderering, this will be removed soon!
*/

#pragma once

#include "program/GetterUtil.h"

#include "al/collision/alCollisionUtil.h"
#include "al/scene/Scene.h"

#include "game/StageScene/StageScene.h"

#include "heap/seadDisposer.h"
#include <gfx/seadPrimitiveRenderer.h>


// All settings dedicated to player information
struct PrimitivePlayerSettings {
    bool mDrawWorldAxis = true;
    bool mDrawPlayerAxis = true;
    bool mDrawFront = true;
    bool mDrawHackCap = false;
};

// All settings dedicated to collision/colliders
struct PrimitiveTriangleSettings {
    bool mDrawTriangle = false;
    bool mDrawComplexTriangle = false;
};

// All settings dedicated to different areas around the map
struct PrimitiveAreaSettings {
    bool mDrawAreas = true;

    bool mDrawAreaStage = true;
    bool mDrawAreaDeath = false;
    bool mDrawAreaWater = false;
    bool mDrawArea2D = false;
};

// FUTURE FEATURE: Add support for HitSensor rendering in this menu

class DevGuiPrimitive {
public:
    DevGuiPrimitive() {};
    
    void draw(agl::DrawContext* drawContext); // Called during the drawMainHook

    // All settings related to what is being rendered
    bool mIsDrawPrimitives = true;
    PrimitivePlayerSettings mSettingsPlayer;
    PrimitiveTriangleSettings mSettingsTriangle;
    PrimitiveAreaSettings mSettingsArea;

private:
    // Draw functions for each category (same categories as above)
    void drawPlayerCategory();
    void drawColliderCategory();
    void drawAreaCategory();

    // Area rendering functions
    void drawAreaGroup(const char* areaName, sead::Color4f wire, sead::Color4f solid);

    // Triangle rendering functions
    void drawSingleTri(al::Triangle* tri);
    void drawTrianglesSimple();
    void drawTrianglesComplex();
};